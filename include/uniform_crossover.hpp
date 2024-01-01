#ifndef UNIFORM_CROSSOVER_HPP
#define UNIFORM_CROSSOVER_HPP

#include "crossover_operator.hpp"
#include "xoroshiro_generator.hpp"
class UniformCrossover : public CrossoverOperator
{
public:
    void crossover(ParentSelection *parentSelection, int chromosomeSize, int **population, int *outOffspring);

private:
    XoroshiroGenerator generator;
};

#endif