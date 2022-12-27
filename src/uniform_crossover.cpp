#include "uniform_crossover.hpp"

void UniformCrossover::crossover(ParentSelection* parentSelection, int chromosomeSize, int** population, int* outOffspring)
{
    int* parent1 = population[parentSelection->getParentsIndices()[0]];
    int* parent2 = population[parentSelection->getParentsIndices()[1]];

    for (int i = 0; i < chromosomeSize; i++)
    {
        if (rand() % 2 == 0)
        {
            outOffspring[i] = parent1[i];
        }
        else
        {
            outOffspring[i] = parent2[i];
        }
    }
}