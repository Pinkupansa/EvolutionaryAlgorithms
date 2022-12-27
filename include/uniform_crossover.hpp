#ifndef UNIFORM_CROSSOVER_HPP
#define UNIFORM_CROSSOVER_HPP

#include "crossover_operator.hpp"
#include <random>

class UniformCrossover : public CrossoverOperator
{
    public:
        void crossover(ParentSelection* parentSelection, int chromosomeSize, int** population, int* outOffspring);
};

#endif