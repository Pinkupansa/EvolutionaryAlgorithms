#include <iostream>

#include "benchmark_functions.hpp"
#include "hill_climber.hpp"
#include "evolution_interface.hpp"
#include "elitist_ea.hpp"

int main(int argc, char **argv)
{
    int chromosomeSize = 100;

    srand(1);
    int weights[chromosomeSize];
    int values[chromosomeSize];

    for (int i = 0; i < chromosomeSize; i++)
    {
        weights[i] = rand() % 10;
        values[i] = rand() % 10;
    }

    int knapsackSize = 300;

    KnapSack knapSack(chromosomeSize, weights, values, knapsackSize);

    ElitistEA elitist(100, 50, chromosomeSize, 3);
    // HillClimber hillClimber(chromosomeSize, 1);
    EvolutionInterface evolutionInterface(&elitist, 10000, &knapSack);
    evolutionInterface.run();
}
