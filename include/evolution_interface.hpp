#ifndef EVOLUTION_INTERFACE_HPP
#define EVOLUTION_INTERFACE_HPP
#include <bits/stdc++.h>
#include "evolutionary_algorithm.hpp"
#include "problem_wrapper.hpp"
class EvolutionInterface
{

public:
    EvolutionInterface(EvolutionaryAlgorithm *algorithm, int maxGenerations, ProblemWrapper *function, SDL_Window *window, SDL_Renderer *renderer);
    ~EvolutionInterface();
    void run();
    int *getBestIndividual();
    double getBestFitness();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    
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