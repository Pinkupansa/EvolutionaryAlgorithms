#include "fitness_proportional_parent_selection.hpp"
#include <algorithm>
#include <random>
#include <vector>

FitnessProportionalParentSelection::FitnessProportionalParentSelection(double doubleParentProbability)
{
    this->doubleParentProbability = doubleParentProbability;
}

void FitnessProportionalParentSelection::select(double *populationFitnesses, int **population, int populationSize, int offspringSize, std::vector<ParentSelection *> *out)
{
    double totalFitness = 0;
    for (int i = 0; i < populationSize; i++)
    {
        totalFitness += populationFitnesses[i];
    }
    std::vector<double> cumulativeFitnesses;
    cumulativeFitnesses.push_back(populationFitnesses[0] / totalFitness);
    for (int i = 1; i < populationSize; i++)
    {
        cumulativeFitnesses.push_back(cumulativeFitnesses[i - 1] + populationFitnesses[i] / totalFitness);
    }
    for (int i = 0; i < offspringSize; i++)
    {
        double random = rand() / double(RAND_MAX);
        int parentIndex = std::lower_bound(cumulativeFitnesses.begin(), cumulativeFitnesses.end(), random) - cumulativeFitnesses.begin();

        if (rand() / double(RAND_MAX) < doubleParentProbability)
        {

            random = rand() / double(RAND_MAX);
            int secondParentIndex = std::lower_bound(cumulativeFitnesses.begin(), cumulativeFitnesses.end(), random) - cumulativeFitnesses.begin();
            ParentSelection *parentSelection = new ParentSelection(2);
            parentSelection->getParentsIndices()[0] = parentIndex;
            parentSelection->getParentsIndices()[1] = secondParentIndex;
            out->push_back(parentSelection);
        }
        else
        {
            ParentSelection *parentSelection = new ParentSelection(1);
            parentSelection->getParentsIndices()[0] = parentIndex;
            out->push_back(parentSelection);
        }
    }
}
