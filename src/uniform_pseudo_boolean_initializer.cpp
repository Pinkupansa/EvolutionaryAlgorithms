#include "uniform_pseudo_boolean_initializer.hpp"

void UniformPseudoBooleanInitializer::initialize(int **population, int populationSize, int chromosomeSize)
{
    for (int i = 0; i < populationSize; i++)
    {
        for (int j = 0; j < chromosomeSize; j++)
        {
            population[i][j] = generator.uniformInt(0, 1);
        }
    }
}