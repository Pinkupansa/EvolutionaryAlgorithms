#include "random_parent_selection.hpp"
#include <random>

RandomParentSelection::RandomParentSelection(double doubleParentProbability)
{
    this->doubleParentProbability = doubleParentProbability;
}

int RandomParentSelection::chooseParent(double *populationFitnesses, int **population, int populationSize)
{
    return generator.uniformInt(0, populationSize - 1);
}

void RandomParentSelection::select(double *populationFitnesses, int **population, int populationSize, int offspringSize, ParentSelection **out)
{
    for (int i = 0; i < offspringSize; i++)
    {

        int parent = chooseParent(populationFitnesses, population, populationSize);
        double r = generator.uniformDouble(0, 1);

        if (r < doubleParentProbability)
        {
            int secondParent = chooseParent(populationFitnesses, population, populationSize);
            ParentSelection *parentSelection = new ParentSelection(2);
            parentSelection->getParentsIndices()[0] = parent;
            parentSelection->getParentsIndices()[1] = secondParent;
            out[i] = parentSelection;
        }
        else
        {
            ParentSelection *parentSelection = new ParentSelection(1);
            parentSelection->getParentsIndices()[0] = parent;
            out[i] = parentSelection;
        }
    }
}