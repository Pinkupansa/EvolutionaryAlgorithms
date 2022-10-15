#ifndef UNIFORM_PSEUDO_BOOLEAN_INITIALIZER_HPP
#define UNIFORM_PSEUDO_BOOLEAN_INITIALIZER_HPP
#include "initializer.hpp"


class UniformPseudoBooleanInitializer : public Initializer
{
    public:
        void initialize(int **population, int populationSize, int chromosomeSize);
        
};

#endif // UNIFORM_PSEUDO_BOOLEAN_INITIALIZER_HPP