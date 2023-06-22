#include "evolution_interface.hpp"
#include <random>
#include <SDL2_framerate.h>
#define VERBOSE 0
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
    this->worstIndividualIndex = 0;
    this->bestFitness = 0;
    this->worstFitness = 10000000;

    TTF_Init();
    this->font = TTF_OpenFont("arial.ttf", 24);

    std::cout << "Initializing EA" << std::endl;
    algorithm->log = &log;
    algorithm->initialize();
    srand(time(NULL));
    std::cout << "EA initialized" << std::endl;
    calculateInitialPopulationFitnesses();
    algorithm->postInitialization(populationFitnesses);
    refreshExtremeFitnesses();
    printBestIndividual();
    problem->visualize(getBestIndividual(), window, renderer);
    // visualizer.refresh(bestFitness, worstFitness);
    this->graphRefreshRate = graphRefreshRate;
}

EvolutionInterface::~EvolutionInterface()
{
    TTF_CloseFont(font);
    delete[] populationFitnesses;
    delete[] offspringFitnesses;
}

void EvolutionInterface::step()
{
    // std::cout << "Generation " << currentGeneration << "\r";
    algorithm->reproduce();
    algorithm->mutate();
    calculateOffspringFitnesses();
    algorithm->select(offspringFitnesses);
    refreshExtremeFitnesses();

#if VERBOSE
    printBestIndividual();
#endif
    currentGeneration++;

    if (graphRefreshRate > 0 && currentGeneration % graphRefreshRate == 0)
    {
        problem->visualize(getBestIndividual(), window, renderer);
        visualizer.refresh(bestFitness, worstFitness);
    }
}

void EvolutionInterface::refreshExtremeFitnesses()
{
    bestIndividualIndex = algorithm->getPopulationSize() - 1;
    worstIndividualIndex = 0;
    bestFitness = algorithm->getCurrentFitnesses()[algorithm->getPopulationSize() - 1];
    worstFitness = algorithm->getCurrentFitnesses()[0];
}

void EvolutionInterface::calculateInitialPopulationFitnesses()
{
    int **individuals = algorithm->getCurrentPopulation();
    for (int i = 0; i < algorithm->getPopulationSize(); i++)
    {
        populationFitnesses[i] = problem->evaluate(individuals[i]);
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

void EvolutionInterface::displayProgress()
{
    visualizer.displayLog(log);
}

bool EvolutionInterface::checkStopCondition()
{
    return (algorithm->generationStop > -1 && currentGeneration >= algorithm->generationStop) || (algorithm->fitnessStop > -1 && bestFitness >= algorithm->fitnessStop);
}

EvolutionaryAlgorithm *EvolutionInterface::getAlgo()
{
    return algorithm;
}