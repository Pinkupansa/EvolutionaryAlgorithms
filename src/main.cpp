#include <iostream>
#include <SDL2/SDL.h>
#include "benchmark_functions.hpp"
#include "hill_climber.hpp"
#include "evolution_interface.hpp"
#include "elitist_ea.hpp"
#include "standard_bit_mutation.hpp"
#include "uniform_pseudo_boolean_initializer.hpp"
#include "exchange_mutation.hpp"
#include "mutation_chain.hpp"
#include "partial_shuffle.hpp"
#include "uniform_permutation_initializer.hpp"
#include "travelling_salesman.hpp"
#include "crossover_operators.hpp"
#include "selection_operators.hpp"
#include "time.h"
#include "utilities.hpp"
// Function that creates a fully operational SDL2 window
SDL_Window *createWindow(int width, int height, const char *title)
{
    SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        }
    }
    // program should quit when we press the x button
    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

    return window;
}

void evolutionLoop(EvolutionInterface *evolutionInterface)
{
    // start clock
    clock_t start = clock();
    SDL_Event ev;
    while (true)
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                return;
            }
        }
        if (evolutionInterface->checkStopCondition())
        {
            std::cout << "Time elapsed: " << (clock() - start) / (double)CLOCKS_PER_SEC << std::endl;
            std::cout << "Time spent in copy" << ((ElitistEA *)(evolutionInterface->getAlgo()))->timeSpentInCopy / (double)CLOCKS_PER_SEC << std::endl;
            evolutionInterface->displayProgress();

            while (true)
            {
                while (SDL_PollEvent(&ev))
                {
                    if (ev.type == SDL_QUIT)
                    {
                        return;
                    }
                }
                SDL_Delay(0);
            }
        }
        evolutionInterface->step();

        SDL_Delay(0);
    }
}
void ts_test(SDL_Window *window, SDL_Renderer *renderer)
{
    int chromosomeSize = 100;

    srand(1);

    // create chromosomeSize random cities
    int **cities = new int *[chromosomeSize];
    for (int i = 0; i < chromosomeSize; i++)
    {
        cities[i] = new int[2];
        cities[i][0] = rand() % 1000;
        cities[i][1] = rand() % 1000;
    }

    TravellingSalesman ts(chromosomeSize, cities);

    // Jump jump(chromosomeSize, 10);
    ExchangeMutation mutationOperator1;
    PartialShuffle mutationOperator2;
    MutationOperator *mutationOperators[2] = {&mutationOperator1, &mutationOperator2};
    double probabilities[2] = {1, 1};
    MutationChain mutationOperator(mutationOperators, probabilities, 2);

    UniformPermutationInitializer initializer;
    ElitistEA elitist(100, 100, chromosomeSize, &mutationOperator, &initializer);
    // HillClimber hillClimber(chromosomeSize, 1);
    EvolutionInterface evolutionInterface(&elitist, &ts, window, renderer, 100);

    evolutionLoop(&evolutionInterface);
}

void onemax_test(SDL_Window *window, SDL_Renderer *renderer)
{
    int chromosomeSize = 10000;

    srand(time(NULL));

    OneMax oneMax(chromosomeSize);
    // Jump jump(chromosomeSize, 10);

    StandardBitMutation mutationOperator(1.618 / (double)chromosomeSize);

    UniformPseudoBooleanInitializer initializer;
    UniformCrossover crossoverOperator;
    FitnessProportionalParentSelection selectionOperator(0.7);
    ElitistEA elitist(2, 1, chromosomeSize, &mutationOperator, &initializer, &crossoverOperator, &selectionOperator);

    elitist.fitnessStop = chromosomeSize;
    elitist.generationStop = 200000;
    // HillClimber hillClimber(chromosomeSize, 1);
    EvolutionInterface evolutionInterface(&elitist, &oneMax, window, renderer, 0);

    evolutionLoop(&evolutionInterface);
}

void jump_test(SDL_Window *window, SDL_Renderer *renderer)
{
    int chromosomeSize = 1000;

    srand(1);

    Jump jump(chromosomeSize, 10);
    // Jump jump(chromosomeSize, 10);
    UniformCrossover crossoverOperator;
    KTournamentParentSelection selectionOperator(2, 0.75);
    StandardBitMutation mutationOperator(1.0 / (double)chromosomeSize);

    UniformPseudoBooleanInitializer initializer;
    ElitistEA elitist(1000, 500, chromosomeSize, &mutationOperator, &initializer, &crossoverOperator, &selectionOperator);
    // HillClimber hillClimber(chromosomeSize, 1);
    EvolutionInterface evolutionInterface(&elitist, &jump, window, renderer, 100);

    evolutionLoop(&evolutionInterface);
}

void leadingOnes_test(SDL_Window *window, SDL_Renderer *renderer)
{
    int chromosomeSize = 200;

    srand(time(NULL));

    LeadingOnes leadingOnes(chromosomeSize);
    // Jump jump(chromosomeSize, 10);
    UniformCrossover crossoverOperator;
    // KTournamentParentSelection selectionOperator(2, 0.25);
    // FitnessProportionalParentSelection selectionOperator(0.6);
    RandomParentSelection selectionOperator(0);
    StandardBitMutation mutationOperator(1.0 / (double)chromosomeSize);

    UniformPseudoBooleanInitializer initializer;
    ElitistEA elitist(3, 1, chromosomeSize, &mutationOperator, &initializer, &crossoverOperator, &selectionOperator);
    elitist.fitnessStop = chromosomeSize;
    elitist.generationStop = 100000;
    // HillClimber hillClimber(chromosomeSize, 1);
    EvolutionInterface evolutionInterface(&elitist, &leadingOnes, window, renderer, 0);

    evolutionLoop(&evolutionInterface);
}

int main(int argc, char **argv)
{

    // Create a SDL window
    SDL_Window *window = createWindow(1000, 1000, "Genetic Algorithms");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // jump_test(window, renderer);
    leadingOnes_test(window, renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
