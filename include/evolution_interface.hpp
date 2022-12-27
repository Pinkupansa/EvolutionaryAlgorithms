#ifndef EVOLUTION_INTERFACE_HPP
#define EVOLUTION_INTERFACE_HPP
#include <bits/stdc++.h>
#include "evolutionary_algorithm.hpp"
#include "problem_wrapper.hpp"
#include <SDL2/SDL_ttf.h>
#include "ga_visualizer.hpp"
class EvolutionInterface
{

public:
    EvolutionInterface(EvolutionaryAlgorithm *algorithm, ProblemWrapper *function, SDL_Window *window, SDL_Renderer *renderer);
    ~EvolutionInterface();
    void step();
    int *getBestIndividual();
    double getBestFitness();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    EvolutionaryAlgorithm *algorithm;

    GAVisualizer visualizer;

    ProblemWrapper *problem;
    double *populationFitnesses;
    double *offspringFitnesses;

    int bestIndividualIndex;
    double bestFitness;

    int currentGeneration;

    void calculatePopulationFitnesses();
    void calculateOffspringFitnesses();
    void printBestIndividual();

    TTF_Font *font;
};

#endif // EVOLUTION_INTERFACE_HPP