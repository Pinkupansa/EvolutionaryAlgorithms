#include "hill_climber.hpp"
#include <random>

HillClimber::HillClimber(int chromosomeSize, double mutationConstant)
{
    this->chromosomeSize = chromosomeSize;
    this->mutationRate = mutationConstant / chromosomeSize;
    currentIndividual = new int[chromosomeSize];
    currentOffspring = new int[chromosomeSize];
}

HillClimber::~HillClimber()
{
    delete[] currentIndividual;
    delete[] currentOffspring;
}

void HillClimber::initialize()
{
    for (int i = 0; i < chromosomeSize; i++)
    {
        currentIndividual[i] = rand() % 2;
    }
}

void HillClimber::mutate()
{
    for (int i = 0; i < chromosomeSize; i++)
    {
        if (rand() % 100 < mutationRate * 100)
        {
            currentOffspring[i] = !currentOffspring[i];
        }
    }
}

void HillClimber::reproduce(double *populationFitnesses)
{
    currentIndividualFitness = populationFitnesses[0];
    for (int i = 0; i < chromosomeSize; i++)
    {
        currentOffspring[i] = currentIndividual[i];
    }
}

void HillClimber::select(double *offspringFitnesses, std::vector<int> removedPopulation, std::vector<int> addedOffspring)
{
    if (offspringFitnesses[0] > currentIndividualFitness)
    {
        int *temp = currentIndividual;
        currentIndividual = currentOffspring;
        currentOffspring = temp;
        currentIndividualFitness = offspringFitnesses[0];
        removedPopulation.push_back(0);
        addedOffspring.push_back(0);
    }
}

int **HillClimber::getCurrentPopulation()
{
    int **population = new int *[1];
    population[0] = currentIndividual;
    return population;
}

int **HillClimber::getCurrentOffspring()
{
    int **offspring = new int *[1];
    offspring[0] = currentOffspring;
    return offspring;
}

int HillClimber::getChromosomeSize()
{
    return chromosomeSize;
}

int HillClimber::getPopulationSize()
{
    return 1;
}

int HillClimber::getOffspringSize()
{
    return 1;
}
