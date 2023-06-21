#include "elitist_ea.hpp"
#include <algorithm>
#include <iostream>
#include "k_tournament_parent_selection.hpp"
#include "fitness_proportional_parent_selection.hpp"
#include "uniform_crossover.hpp"
#include <vector>
#include "utilities.hpp"
void copy(int *array, int *target, int size)
{
    for (int i = 0; i < size; i++)
    {
        target[i] = array[i];
    }
}

ElitistEA::ElitistEA(int populationSize, int offspringSize, int chromosomeSize, MutationOperator *mutationOperator, Initializer *initializer)
{
    this->populationSize = populationSize;
    this->offspringSize = offspringSize;
    this->chromosomeSize = chromosomeSize;
    this->population = new int *[populationSize];
    this->offspring = new int *[offspringSize];
    this->populationFitnesses = new double[populationSize];
    this->mutationOperator = mutationOperator;
    this->initializer = initializer;
    this->crossoverOperator = new UniformCrossover();
    this->parentSelectionOperator = new FitnessProportionalParentSelection(0);

    for (int i = 0; i < populationSize; i++)
    {
        this->population[i] = new int[chromosomeSize];
    }

    for (int i = 0; i < offspringSize; i++)
    {
        this->offspring[i] = new int[chromosomeSize];
    }
}

ElitistEA::ElitistEA(int populationSize, int offspringSize, int chromosomeSize, MutationOperator *mutationOperator, Initializer *initializer, CrossoverOperator *crossoverOperator, ParentSelectionOperator *parentSelectionOperator)
{
    this->populationSize = populationSize;
    this->offspringSize = offspringSize;
    this->chromosomeSize = chromosomeSize;
    this->population = new int *[populationSize];
    this->offspring = new int *[offspringSize];
    this->populationFitnesses = new double[populationSize];
    this->mutationOperator = mutationOperator;
    this->initializer = initializer;
    this->crossoverOperator = crossoverOperator;
    this->parentSelectionOperator = parentSelectionOperator;

    for (int i = 0; i < populationSize; i++)
    {
        this->population[i] = new int[chromosomeSize];
    }

    for (int i = 0; i < offspringSize; i++)
    {
        this->offspring[i] = new int[chromosomeSize];
    }

    this->parentSelectionOperator = parentSelectionOperator;
    this->crossoverOperator = crossoverOperator;
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

    if (mutationOperator != NULL)
    {
        delete mutationOperator;
    }

    if (initializer != NULL)
    {
        delete initializer;
    }
}

void ElitistEA::initialize()
{
    initializer->initialize(population, populationSize, chromosomeSize);
}

void ElitistEA::reproduce()
{
    ParentSelection *parentSelections[offspringSize];

    parentSelectionOperator->select(populationFitnesses, population, populationSize, offspringSize, parentSelections);

    for (int i = 0; i < offspringSize; i++)
    {
        if (parentSelections[i]->getNumberOfParents() < 2)
        {
            copy(population[parentSelections[i]->getParentsIndices()[0]], offspring[i], chromosomeSize);
        }
        else
        {
            crossoverOperator->crossover(parentSelections[i], chromosomeSize, population, offspring[i]);
        }
    }
    log->addGeneration(populationFitnesses[populationSize - 1], populationFitnesses[0], populationSize, offspringSize, parentSelections);
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
    int ranking[populationSize + offspringSize];
    binary_insert_sort_selection(populationSize, populationFitnesses, offspringSize, offspringFitnesses, ranking);
    int newPopulation[populationSize][chromosomeSize];
    double newPopulationFitnesses[populationSize];
    for (int i = offspringSize; i < populationSize + offspringSize; i++)
    {
        if (ranking[i] < populationSize)
        {
            copy(population[ranking[i]], newPopulation[i - offspringSize], chromosomeSize);
            newPopulationFitnesses[i - offspringSize] = populationFitnesses[ranking[i]];
        }
        else
        {
            copy(offspring[ranking[i] - populationSize], newPopulation[i - offspringSize], chromosomeSize);
            newPopulationFitnesses[i - offspringSize] = offspringFitnesses[ranking[i] - populationSize];
        }
    }

    for (int i = 0; i < populationSize; i++)
    {
        copy(newPopulation[i], population[i], chromosomeSize);
    }

    for (int i = 0; i < populationSize; i++)
    {
        populationFitnesses[i] = newPopulationFitnesses[i];
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

void ElitistEA::postInitialization(double *fitnesses)
{
    // sort the population in ascending order of fitness
    std::pair<double, int> popFitnessWithIndex[populationSize];
    for (int i = 0; i < populationSize; i++)
    {
        popFitnessWithIndex[i] = std::make_pair(fitnesses[i], i);
    }

    bool (*comparisonFunction)(std::pair<double, int>, std::pair<double, int>) = [](std::pair<double, int> a, std::pair<double, int> b)
    {
        return a.first < b.first;
    };

    std::sort(popFitnessWithIndex, popFitnessWithIndex + populationSize, comparisonFunction);

    for (int i = 0; i < populationSize; i++)
    {
        copy(population[popFitnessWithIndex[i].second], population[i], chromosomeSize);
    }

    for (int i = 0; i < populationSize; i++)
    {
        populationFitnesses[i] = fitnesses[i];
    }
}

double *ElitistEA::getCurrentFitnesses()
{
    return populationFitnesses;
}