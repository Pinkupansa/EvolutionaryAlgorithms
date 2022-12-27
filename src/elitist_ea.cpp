#include "elitist_ea.hpp"
#include <algorithm>
#include <iostream>
#include "k_tournament_monoparent_selection.hpp"
#include <vector>
void copy(int *array, int *target, int size)
{
    for (int i = 0; i < size; i++)
    {
        target[i] = array[i];
    }
}

ElitistEA::ElitistEA(int populationSize, int offspringSize, int chromosomeSize, MutationOperator* mutationOperator, Initializer* initializer)
{
    this->populationSize = populationSize;
    this->offspringSize = offspringSize;
    this->chromosomeSize = chromosomeSize;
    this->population = new int *[populationSize];
    this->offspring = new int *[offspringSize];
    this->populationFitnesses = new double[populationSize];
    this->mutationOperator = mutationOperator;
    this->initializer = initializer;

    for (int i = 0; i < populationSize; i++)
    {
        this->population[i] = new int[chromosomeSize];
    }

    for (int i = 0; i < offspringSize; i++)
    {
        this->offspring[i] = new int[chromosomeSize];
    }

    this->parentSelectionOperator = new KTournamentMonoParentSelection(5);
}

ElitistEA::~ElitistEA()
{
    for (int i = 0; i < populationSize; i++)
    {
        delete[] population[i];
        delete[] offspring[i];
    }
    delete[] population;
    delete[] offspring;
    delete[] populationFitnesses;
}

void ElitistEA::initialize()
{
    initializer->initialize(population, populationSize, chromosomeSize);
}

void ElitistEA::reproduce(double *newPopulationFitnesses)
{
    for (int i = 0; i < populationSize; i++)
    {
        populationFitnesses[i] = newPopulationFitnesses[i];
    }

    int k = 5;

    // k tournament selection
    std::vector<ParentSelection*> parentSelections;
    
    parentSelectionOperator->select(populationFitnesses, population, populationSize, offspringSize, &parentSelections);

    for (int i = 0; i < offspringSize; i++)
    {
        copy(population[parentSelections[i]->getParentsIndices()[0]], offspring[i], chromosomeSize);
    }

    for (int i = 0; i < offspringSize; i++)
    {
        delete parentSelections[i];
    }
    
}

void ElitistEA::mutate()
{
    for (int i = 0; i < offspringSize; i++)
    {
        mutationOperator->mutate(offspring[i], chromosomeSize);
    }
}

void ElitistEA::select(double *offspringFitnesses)
{

    std::pair<double, int> popFitnessWithIndex[populationSize];
    for (int i = 0; i < populationSize; i++)
    {
        popFitnessWithIndex[i] = std::make_pair(populationFitnesses[i], i);
    }

    bool (*comparisonFunction)(std::pair<double, int>, std::pair<double, int>) = [](std::pair<double, int> a, std::pair<double, int> b)
    {
        return a.first < b.first;
    };
    //sorts only the worst offspringSize individuals the population in ascending order of fitness 
    std::partial_sort(popFitnessWithIndex, popFitnessWithIndex + offspringSize, popFitnessWithIndex + populationSize, comparisonFunction);

    std::pair<double, int> looserBracketWithIndex[2 * offspringSize]; //mixed bad population and offspring

    for (int i = 0; i < offspringSize; i++)
    {
        // Worst individuals of the population
        looserBracketWithIndex[i] = popFitnessWithIndex[i];
    }

    for (int i = offspringSize; i < 2 * offspringSize; i++)
    {
        // Worst individuals of the offspring
        looserBracketWithIndex[i] = std::make_pair(offspringFitnesses[i - offspringSize], i - offspringSize + populationSize);
    }
    std::cout << std::endl;

    //sorts only the worst offspringSize individuals the population in ascending order of fitness
    std::partial_sort(looserBracketWithIndex, looserBracketWithIndex + offspringSize, looserBracketWithIndex + 2 * offspringSize, comparisonFunction);

    //the first half of the looserBracketWithIndex array contains individuals that will be replaced by the second half of the array
    for (int i = 0; i < offspringSize; i++)
    {
        int replacedIndex = looserBracketWithIndex[i].second;
        int replacingIndex = looserBracketWithIndex[i + offspringSize].second;
        if (replacedIndex < populationSize)
        {
            if (replacingIndex < populationSize)
            {
                copy(population[replacingIndex], population[replacedIndex], chromosomeSize);
                populationFitnesses[replacedIndex] = populationFitnesses[replacingIndex];
            }
            else
            {
                copy(offspring[replacingIndex - populationSize], population[replacedIndex], chromosomeSize);
                populationFitnesses[replacedIndex] = offspringFitnesses[replacingIndex - populationSize];
            }
        }
    }
    
}

int **ElitistEA::getCurrentPopulation()
{
    return population;
}

int ElitistEA::getPopulationSize()
{
    return populationSize;
}

int ElitistEA::getChromosomeSize()
{
    return chromosomeSize;
}

int **ElitistEA::getCurrentOffspring()
{
    return offspring;
}

int ElitistEA::getOffspringSize()
{
    return offspringSize;
}
