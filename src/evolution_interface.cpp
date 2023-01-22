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
    std::cout << "Initializing population fitnesses" << std::endl;
    this->populationFitnesses = new double[algorithm->getPopulationSize()];

    std::cout << "Initializing offspring fitnesses" << std::endl;
    this->offspringFitnesses = new double[algorithm->getPopulationSize()];

    this->bestIndividualIndex = 0;
    this->worstIndividualIndex = 0;
    this->bestFitness = 0;
    this->worstFitness = 10000000;

    TTF_Init();
    this->font = TTF_OpenFont("arial.ttf", 24);

    std::cout << "Initializing EA" << std::endl;
    algorithm->initialize();
    srand(time(NULL));
    std::cout << "EA initialized" << std::endl;
    calculateInitialPopulationFitnesses();
    printBestIndividual();
    problem->visualize(getBestIndividual(), window, renderer);
    visualizer.refresh(bestFitness, worstFitness);
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
    worstFitness = 10000000;
    for (int i = 0; i < algorithm->getPopulationSize(); i++)
    {
        if (populationFitnesses[i] < worstFitness)
        {
            worstFitness = populationFitnesses[i];
            worstIndividualIndex = i;
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

    printBestIndividual();
    currentGeneration++;

    if (currentGeneration % graphRefreshRate == 0)
    {
        problem->visualize(getBestIndividual(), window, renderer);
        visualizer.refresh(bestFitness, worstFitness);
    }
}

void EvolutionInterface::calculateInitialPopulationFitnesses()
{
    bestFitness = 0;
    worstFitness = 1000000000;
    int **individuals = algorithm->getCurrentPopulation();
    for (int i = 0; i < algorithm->getPopulationSize(); i++)
    {

        populationFitnesses[i] = problem->evaluate(individuals[i]);
        if (populationFitnesses[i] > bestFitness)
        {
            bestFitness = populationFitnesses[i];
            bestIndividualIndex = i;
        }
        if (populationFitnesses[i] < worstFitness)
        {
            worstFitness = populationFitnesses[i];
            worstIndividualIndex = i;
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