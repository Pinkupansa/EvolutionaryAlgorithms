#ifndef EVOLUTION_INTERFACE_HPP
#define EVOLUTION_INTERFACE_HPP
#include <bits/stdc++.h>
#include "evolutionary_algorithm.hpp"
#include "problem_wrapper.hpp"
#include <SDL2/SDL_ttf.h>
#include "ga_visualizer.hpp"
#include "ea_log.hpp"
class EvolutionInterface
{

public:
    EvolutionInterface(EvolutionaryAlgorithm *algorithm, ProblemWrapper *function, SDL_Window *window, SDL_Renderer *renderer, int graphRefreshRate);
    ~EvolutionInterface();
    void step();
    int *getBestIndividual();
    double getBestFitness();
    bool checkStopCondition();
    void displayProgress();
    EvolutionaryAlgorithm *getAlgo();
    EALog getLog();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    EvolutionaryAlgorithm *algorithm;

    GAVisualizer visualizer;

    ProblemWrapper *problem;

    EALog log;

    double *populationFitnesses;
    double *offspringFitnesses;

    int bestIndividualIndex;
    int worstIndividualIndex;

    double bestFitness;
    double worstFitness;

    int currentGeneration;

    void calculateInitialPopulationFitnesses();
    void calculateOffspringFitnesses();
    void printBestIndividual();
    void refreshExtremeFitnesses();
    void fillLog();
    int graphRefreshRate;
    TTF_Font *font;
};

#endif // EVOLUTION_INTERFACE_HPP