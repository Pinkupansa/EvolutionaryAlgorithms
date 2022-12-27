#include "k_tournament_parent_selection.hpp"
#include <random>
#include <iostream>
KTournamentParentSelection::KTournamentParentSelection(int k, double doubleParentProbability)
{
    this->k = k;
    this->doubleParentProbability = doubleParentProbability;
}

int KTournamentParentSelection::chooseParent(double* populationFitnesses, int** population, int populationSize)
{
    int best = rand() % populationSize;
    for (int j = 1; j < k; j++)
    {
        int candidate = rand() % populationSize;
        if (populationFitnesses[candidate] > populationFitnesses[best])
        {
            best = candidate;
        }
    }
    return best;
}

void KTournamentParentSelection::select(double* populationFitnesses, int** population, int populationSize, int offspringSize, std::vector<ParentSelection*>* out)
{
    for (int i = 0; i < offspringSize; i++)
    {

        int parent = chooseParent(populationFitnesses, population, populationSize);
        double r = (double) rand() / RAND_MAX;

        if (r < doubleParentProbability)
        {
            int secondParent = chooseParent(populationFitnesses, population, populationSize);
            ParentSelection* parentSelection = new ParentSelection(2);
            parentSelection->getParentsIndices()[0] = parent;
            parentSelection->getParentsIndices()[1] = secondParent;
            out->push_back(parentSelection);
        }
        else{
            ParentSelection* parentSelection = new ParentSelection(1);
            parentSelection->getParentsIndices()[0] = parent;
            out->push_back(parentSelection);
        }
    }
}

