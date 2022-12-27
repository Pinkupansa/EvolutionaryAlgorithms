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
    SDL_Event ev;
    
    while (true)
    {
        evolutionInterface->step();
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                return;
            }
        }
    }
}
void ts_test(SDL_Window *window, SDL_Renderer *renderer){
    int chromosomeSize = 100;

    srand(1);

    //create chromosomeSize random cities
    int **cities = new int *[chromosomeSize];
    for (int i = 0; i < chromosomeSize; i++)
    {
        cities[i] = new int[2];
        cities[i][0] = rand() % 1000;
        cities[i][1] = rand() % 1000;
    }

    TravellingSalesman ts(chromosomeSize, cities);

    //Jump jump(chromosomeSize, 10);
    ExchangeMutation mutationOperator1;
    PartialShuffle mutationOperator2;
    MutationOperator *mutationOperators[2] = {&mutationOperator1, &mutationOperator2};
    double probabilities[2] = {1, 1};
    MutationChain mutationOperator(mutationOperators, probabilities, 2);
    
    UniformPermutationInitializer initializer;
    ElitistEA elitist(100, 100, chromosomeSize, &mutationOperator, &initializer);
    // HillClimber hillClimber(chromosomeSize, 1);
    EvolutionInterface evolutionInterface(&elitist, &ts, window, renderer);

    evolutionLoop(&evolutionInterface);

}

void onemax_test(SDL_Window *window, SDL_Renderer *renderer)
{
    int chromosomeSize = 1000;

    srand(1);

    OneMax oneMax(chromosomeSize);
    //Jump jump(chromosomeSize, 10);
    StandardBitMutation mutationOperator(0.02);
    UniformPseudoBooleanInitializer initializer;
    ElitistEA elitist(1000, 500, chromosomeSize, &mutationOperator, &initializer);
    // HillClimber hillClimber(chromosomeSize, 1);
    EvolutionInterface evolutionInterface(&elitist, &oneMax, window, renderer);

    evolutionLoop(&evolutionInterface);
}


int main(int argc, char **argv)
{
    // Create a SDL window
    SDL_Window *window = createWindow(1000, 1000, "Genetic Algorithms");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    onemax_test(window, renderer);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
