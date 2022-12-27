#include "single_point_crossover.hpp"
#include <random>

void SinglePointCrossover::crossover(ParentSelection* parentSelection, int chromosomeSize, int** population, int* outOffspring)
{
    if(parentSelection->getNumberOfParents() < 2)
    {
        throw "Parent selection operator must have a population size of at least 2";
    }

    int* parent1 = population[parentSelection->getParentsIndices()[0]];
    int* parent2 = population[parentSelection->getParentsIndices()[1]];
    int crossoverPoint = rand() % chromosomeSize;
    for (int i = 0; i < crossoverPoint; i++)
    {
        outOffspring[i] = parent1[i];
    }
    for (int i = crossoverPoint; i < chromosomeSize; i++)
    {
        outOffspring[i] = parent2[i];
    }

}