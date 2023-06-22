
#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <vector>
#include <algorithm>
#include <random>
// include dictionaries
inline void binary_insert_sort_selection(int populationSize, double *populationFitnesses,
                                         int offspringSize, double *offspringFitnesses, int *ranking)
{
    // assumes that the population is sorted by fitness
    for (int i = 0; i < populationSize + offspringSize; i++)
    {
        ranking[i] = i;
    }

    std::vector<int> interspaces[populationSize + 1];
    // interspaces[i] contain the indices of the individuals in the population that are worse than the i-th offspring
    // but better than the (i-1)-th offspring

    for (int i = 0; i < offspringSize; i++)
    {
        if (offspringFitnesses[i] > populationFitnesses[populationSize - 1])
        {
            interspaces[populationSize].push_back(i + populationSize);
            continue;
        }
        // binary search to find the interspace of the i-th offspring
        int left = 0;
        int right = populationSize - 1;
        int middle = (left + right) / 2;
        while (left < right)
        {
            if (offspringFitnesses[i] < populationFitnesses[middle])
            {
                right = middle;
            }
            else
            {
                left = middle + 1;
            }
            middle = (left + right) / 2;
        }
        interspaces[middle].push_back(i + populationSize);
    }

    // sort all interspaces by merge sort on fitness
    for (int i = 0; i < populationSize + 1; i++)
    {
        if (interspaces[i].size() > 1)
        {
            std::sort(interspaces[i].begin(), interspaces[i].end(), [offspringFitnesses](int a, int b)
                      { return offspringFitnesses[a] < offspringFitnesses[b]; });
        }
    }

    int currentRank = 0;
    for (int i = 0; i < populationSize + 1; i++)
    {
        for (int j = 0; j < interspaces[i].size(); j++)
        {
            ranking[currentRank] = interspaces[i][j];
            currentRank++;
        }
        if (i < populationSize)
        {
            ranking[currentRank] = i;
            currentRank++;
        }
    }
}

#endif