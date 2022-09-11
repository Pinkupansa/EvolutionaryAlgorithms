#ifndef EVOLUTION_INTERFACE_HPP
#define EVOLUTION_INTERFACE_HPP
#include <bits/stdc++.h>
#include "evolutionary_algorithm.hpp"
#include "problem_wrapper.hpp"

class EvolutionInterface
{

public:
    EvolutionInterface(EvolutionaryAlgorithm *algorithm, int maxGenerations, ProblemWrapper *function);
    ~EvolutionInterface();
    void run();
    int *getBestIndividual();
    double getBestFitness();

private:
    EvolutionaryAlgorithm *algorithm;

    ProblemWrapper *problem;
    double *populationFitnesses;
    double *offspringFitnesses;

    int maxGenerations;

    int bestIndividualIndex;
    double bestFitness;

    void calculatePopulationFitnesses();
    void calculateOffspringFitnesses();
    void printBestIndividual();
};

#endif // EVOLUTION_INTERFACE_HPP