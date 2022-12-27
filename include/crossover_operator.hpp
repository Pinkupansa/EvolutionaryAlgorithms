#ifndef CROSSOVER_OPERATOR_HPP
#define CROSSOVER_OPERATOR_HPP
#include "parent_selection_operator.hpp" // for ParentSelection
#include <vector>
class CrossoverOperator
{
    public:
        virtual void crossover(ParentSelection* parentSelection, int chromosomeSize, int** population, int* outOffspring) = 0;
};
#endif // CROSSOVER_OPERATOR_HPP