#include "uniform_crossover.hpp"

void UniformCrossover::crossover(ParentSelection *parentSelection, int chromosomeSize, int **population, int *outOffspring)
{
    int *parent1 = population[parentSelection->getParentsIndices()[0]];
    int *parent2 = population[parentSelection->getParentsIndices()[1]];

    std::vector<int> differentIndices;
    for (int i = 0; i < chromosomeSize; i++)
    {
        if (parent1[i] != parent2[i])
        {
            differentIndices.push_back(i);
        }
    }
    int differentIndicesSize = differentIndices.size();
    int numberOfParent2Bits = generator.binomial(differentIndicesSize, 0.5);
    int numberOfParent1Bits = differentIndicesSize - numberOfParent2Bits;

    if (numberOfParent2Bits < numberOfParent1Bits)
    {
        for (int i = 0; i < chromosomeSize; i++)
        {
            outOffspring[i] = parent1[i];
        }
        for (int i = 0; i < numberOfParent2Bits; i++)
        {
            int index = differentIndices[generator.uniformInt(0, differentIndicesSize - 1)];
            outOffspring[index] = parent2[index];
        }
    }
    else
    {
        for (int i = 0; i < chromosomeSize; i++)
        {
            outOffspring[i] = parent2[i];
        }
        for (int i = 0; i < numberOfParent1Bits; i++)
        {
            int index = differentIndices[generator.uniformInt(0, differentIndicesSize - 1)];
            outOffspring[index] = parent1[index];
        }
    }
}