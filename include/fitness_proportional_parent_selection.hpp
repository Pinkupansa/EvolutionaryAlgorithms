#ifndef FITNESS_PROPORTIONAL_PARENT_SELECTION_HPP
#define FITNESS_PROPORTIONAL_PARENT_SELECTION_HPP

#include <algorithm>
#include <random>
#include <vector>

#include "parent_selection_operator.hpp"

class FitnessProportionalParentSelection : public ParentSelectionOperator
{
public:
    FitnessProportionalParentSelection(double doubleParentProbability);
    void select(double *populationFitnesses, int **population, int populationSize, int offspringSize, ParentSelection **out);

private:
    double doubleParentProbability;
};

#endif // FITNESS_PROPORTIONAL_PARENT_SELECTION_HPP