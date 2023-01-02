#include "evolution_interface.hpp"
#include <random>
#include <SDL2_framerate.h>

EvolutionInterface::EvolutionInterface(EvolutionaryAlgorithm *algorithm, ProblemWrapper *problem, SDL_Window *window, SDL_Renderer *renderer, int graphRefreshRate)
{
    this->algorithm = algorithm;
    this->problem = problem;
    this->window = window;
    this->renderer = renderer;
    this->currentGeneration = 1;

    this->populationFitnesses = new double[algorithm->getPopulationSize()];
    this->offspringFitnesses = new double[algorithm->getPopulationSize()];

    this->bestIndividualIndex = 0;
    this->bestFitness = 0;

    TTF_Init();
    this->font = TTF_OpenFont("arial.ttf", 24);

    algorithm->initialize();
    srand(time(NULL));
    std::cout << "EA initialized" << std::endl;
    calculateInitialPopulationFitnesses();
    this->graphRefreshRate = graphRefreshRate;
}

EvolutionInterface::~EvolutionInterface()
{
    TTF_CloseFont(font);
    delete[] populationFitnesses;
    delete[] offspringFitnesses;
}
void EvolutionInterface::recalculatePopulationFitnesses(std::vector<int> &removedPopulation, std::vector<int> &addedOffspring)
{
    for (int i = 0; i < removedPopulation.size(); i++)
    {
        populationFitnesses[removedPopulation[i]] = offspringFitnesses[addedOffspring[i]];
        if (populationFitnesses[removedPopulation[i]] > bestFitness)
        {
            bestFitness = populationFitnesses[removedPopulation[i]];
            bestIndividualIndex = removedPopulation[i];
        }
    }
}

void EvolutionInterface::step()
{
    std::cout << "Generation " << currentGeneration << std::endl;
    algorithm->reproduce(populationFitnesses);
    algorithm->mutate();
    calculateOffspringFitnesses();
    std::vector<int> removedPopulation;
    std::vector<int> addedOffspring;
    algorithm->select(offspringFitnesses, &removedPopulation, &addedOffspring);
    // print removedPopulation
    /*for (int i = 0; i < removedPopulation.size(); i++)
    {
        std::cout << removedPopulation[i] << " ";
    }
    std::cout << std::endl;
    // print addedOffspring
    for (int i = 0; i < addedOffspring.size(); i++)
    {
        std::cout << addedOffspring[i] << " ";
    }*/
    recalculatePopulationFitnesses(removedPopulation, addedOffspring);

    // calculateInitialPopulationFitnesses();

    printBestIndividual();
    currentGeneration++;

    if (currentGeneration % 1000 == 0)
    {

        problem->visualize(getBestIndividual(), window, renderer);
    }
    if (currentGeneration % graphRefreshRate == 0)
    {
        visualizer.refresh(bestFitness);
    }
}

void EvolutionInterface::calculateInitialPopulationFitnesses()
{
    bestFitness = 0;
    int **individuals = algorithm->getCurrentPopulation();
    for (int i = 0; i < algorithm->getPopulationSize(); i++)
    {

        populationFitnesses[i] = problem->evaluate(individuals[i]);
        if (populationFitnesses[i] > bestFitness)
        {
            bestFitness = populationFitnesses[i];
            bestIndividualIndex = i;
        }
    }
}

void EvolutionInterface::calculateOffspringFitnesses()
{
    int **individuals = algorithm->getCurrentOffspring();
    for (int i = 0; i < algorithm->getOffspringSize(); i++)
    {
        offspringFitnesses[i] = problem->evaluate(individuals[i]);
    }
}

int *EvolutionInterface::getBestIndividual()
{
    return algorithm->getCurrentPopulation()[bestIndividualIndex];
}

double EvolutionInterface::getBestFitness()
{
    return bestFitness;
}

void EvolutionInterface::printBestIndividual()
{
    int *bestIndividual = getBestIndividual();
    std::cout << "Best individual is : ";
    for (int i = 0; i < algorithm->getChromosomeSize(); i++)
    {

        std::cout << bestIndividual[i] << " ";
    }
    std::cout << "fitness : " << bestFitness << std::endl;
}