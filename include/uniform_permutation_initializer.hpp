#ifndef UNIFORM_PERMUTATION_INITIALIZER_HPP
#define UNIFORM_PERMUTATION_INITIALIZER_HPP

#include "initializer.hpp"
#include "xoroshiro_generator.hpp"

class UniformPermutationInitializer : public Initializer
{
public:
    void initialize(int **population, int populationSize, int chromosomeSize);

private:
    XoroshiroGenerator generator;
};

#endif // UNIFORM_PERMUTATION_INITIALIZER_HPP
