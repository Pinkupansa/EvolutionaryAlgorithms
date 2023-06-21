#ifndef EA_LOG_HPP
#define EA_LOG_HPP

#include <iostream>
#include <vector>
#include "parent_selection_operator.hpp"

class EALog
{
public:
    std::vector<double> bestFitnesses = std::vector<double>();
    std::vector<double> worstFitnesses = std::vector<double>();
    std::vector<ParentSelection **> parentSelections = std::vector<ParentSelection **>();
    std::vector<int> offspringSizes = std::vector<int>();
    std::vector<int> populationSizes = std::vector<int>();
    ~EALog()
    {
        for (int i = 0; i < parentSelections.size(); i++)
        {
            for (int j = 0; j < offspringSizes[i]; j++)
            {
                delete parentSelections[i][j];
            }
        }
    }
    void addGeneration(double bestFitness, double worstFitness, int populationSize, int offspringSize, ParentSelection **parentSelection)
    {
        bestFitnesses.push_back(bestFitness);
        worstFitnesses.push_back(worstFitness);
        offspringSizes.push_back(offspringSize);
        populationSizes.push_back(populationSize);

        ParentSelection **parentSelectionArray = new ParentSelection *[offspringSize];
        for (int i = 0; i < offspringSize; i++)
        {
            parentSelectionArray[i] = parentSelection[i]->clone();
        }
        parentSelections.push_back(parentSelectionArray);
    }
};

#endif // EA_LOG_HPP
