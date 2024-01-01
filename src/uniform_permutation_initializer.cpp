#include "uniform_permutation_initializer.hpp"
void UniformPermutationInitializer::initialize(int **population, int populationSize, int chromosomeSize)
{
    for (int i = 0; i < populationSize; i++)
    {
        for (int j = 0; j < chromosomeSize; j++)
        {
            population[i][j] = j;
        }
        for (int j = 0; j < chromosomeSize; j++)
        {
            int k = generator.uniformInt(0, chromosomeSize - 1);
            int temp = population[i][j];
            population[i][j] = population[i][k];
            population[i][k] = temp;
        }
    }
}