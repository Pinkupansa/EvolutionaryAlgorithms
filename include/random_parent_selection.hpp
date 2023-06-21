#ifndef RANDOM_PARENT_SELECTION_HPP
#define RANDOM_PARENT_SELECTION_HPP

#include "parent_selection_operator.hpp"

class RandomParentSelection : public ParentSelectionOperator
{
public:
    RandomParentSelection(double doubleParentProbability);
    void select(double *populationFitnesses, int **population, int populationSize, int offspringSize, ParentSelection **out);

private:
    double doubleParentProbability;
    int chooseParent(double *populationFitnesses, int **population, int populationSize);
};

#endif // RANDOM_PARENT_SELECTION_HPP