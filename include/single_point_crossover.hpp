#ifndef SINGLE_POINT_CROSSOVER_HPP
#define SINGLE_POINT_CROSSOVER_HPP

#include "crossover_operator.hpp"

class SinglePointCrossover : public CrossoverOperator
{
    public:
        void crossover(ParentSelection* parentSelection, int chromosomeSize, int** population, int* outOffspring);
};

#endif


