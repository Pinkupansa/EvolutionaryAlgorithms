#ifndef UNIFORM_PSEUDO_BOOLEAN_INITIALIZER_HPP
#define UNIFORM_PSEUDO_BOOLEAN_INITIALIZER_HPP
#include "initializer.hpp"
#include "xoroshiro_generator.hpp"

class UniformPseudoBooleanInitializer : public Initializer
{
public:
    void initialize(int **population, int populationSize, int chromosomeSize);

private:
    XoroshiroGenerator generator;
};

#endif // UNIFORM_PSEUDO_BOOLEAN_INITIALIZER_HPP