#include "k_tournament_monoparent_selection.hpp"
#include <random>
#include <iostream>
KTournamentMonoParentSelection::KTournamentMonoParentSelection(int k)
{
    this->k = k;
}

void KTournamentMonoParentSelection::select(double* populationFitnesses, int** population, int populationSize, int offspringSize, std::vector<ParentSelection*>* out)
{
    for (int i = 0; i < offspringSize; i++)
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
        ParentSelection* parentSelection = new ParentSelection(1);
        parentSelection->getParentsIndices()[0] = best;
        out->push_back(parentSelection);
        //print length of out
    }
}

