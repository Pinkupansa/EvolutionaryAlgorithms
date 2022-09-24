#include <iostream>
#include <SDL2/SDL.h>
#include "benchmark_functions.hpp"
#include "hill_climber.hpp"
#include "evolution_interface.hpp"
#include "elitist_ea.hpp"

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
int main(int argc, char **argv)
{
    // Create a SDL window
    SDL_Window *window = createWindow(1000, 1000, "Genetic Algorithms");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int chromosomeSize = 500;

    srand(1);
    int weights[chromosomeSize];
    int values[chromosomeSize];

    for (int i = 0; i < chromosomeSize; i++)
    {
        weights[i] = rand() % 10;
        values[i] = rand() % 10;
    }

    int knapsackSize = 80;

    // KnapSack knapSack(chromosomeSize, weights, values, knapsackSize);
    Jump jump(chromosomeSize, 10);
    ElitistEA elitist(1, 1, chromosomeSize, 10);
    // HillClimber hillClimber(chromosomeSize, 1);
    EvolutionInterface evolutionInterface(&elitist, &jump, window, renderer);

    evolutionLoop(&evolutionInterface);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
