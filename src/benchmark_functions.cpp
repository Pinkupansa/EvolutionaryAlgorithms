#include "benchmark_functions.hpp"

OneMax::OneMax(int chromosomeSize)
{
    this->chromosomeSize = chromosomeSize;
}

OneMax::~OneMax()
{
}

double OneMax::evaluate(int *chromosome)
{
    double fitness = 0;
    for (int i = 0; i < chromosomeSize; i++)
    {
        fitness += chromosome[i];
    }
    return fitness;
}

void OneMax::visualize(int *chromosome)
{
    return;
}

LeadingOnes::LeadingOnes(int chromosomeSize)
{
    this->chromosomeSize = chromosomeSize;
}

LeadingOnes::~LeadingOnes()
{
}

double LeadingOnes::evaluate(int *chromosome)
{
    double fitness = 0;
    for (int i = 0; i < chromosomeSize; i++)
    {
        if (chromosome[i] == 1)
        {
            fitness++;
        }
        else
        {
            break;
        }
    }
    return fitness;
}

void LeadingOnes::visualize(int *chromosome)
{
    return;
}

Jump::Jump(int chromosomeSize, int jumpSize)
{
    this->chromosomeSize = chromosomeSize;
    this->jumpSize = jumpSize;
}

Jump::~Jump()
{
}

double Jump::evaluate(int *chromosome)
{
    double oneMaxFitness = 0;
    for (int i = 0; i < chromosomeSize; i++)
    {
        oneMaxFitness += chromosome[i];
    }
    if (oneMaxFitness == chromosomeSize || oneMaxFitness <= chromosomeSize - jumpSize)
    {
        return oneMaxFitness;
    }
    else
    {
        return chromosomeSize - oneMaxFitness;
    }
}

void Jump::visualize(int *chromosome)
{
    return;
}

KnapSack::KnapSack(int chromosomeSize, int *weights, int *values, int knapsackSize)
{
    this->chromosomeSize = chromosomeSize;
    this->weights = weights;
    this->values = values;
    this->knapsackSize = knapsackSize;
}

KnapSack::~KnapSack()
{
}

double KnapSack::evaluate(int *chromosome)
{
    double fitness = 0;
    int weight = 0;
    for (int i = 0; i < chromosomeSize; i++)
    {
        if (chromosome[i] == 1)
        {
            fitness += values[i];
            weight += weights[i];
        }
    }
    if (weight > knapsackSize)
    {
        return knapsackSize - weight;
    }
    else
    {
        return fitness;
    }
}

void KnapSack::visualize(int *chromosome)
{
    return;
}