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

void OneMax::visualize(int *chromosome, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < chromosomeSize; i++)
    {
        if (chromosome[i] == 1)
        {
            SDL_RenderDrawPoint(renderer, i, 0);
        }
    }
    SDL_RenderPresent(renderer);

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

void LeadingOnes::visualize(int *chromosome, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < chromosomeSize; i++)
    {
        if (chromosome[i] == 1)
        {
            SDL_RenderDrawPoint(renderer, i, 0);
        }
    }
    SDL_RenderPresent(renderer);

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

void Jump::visualize(int *chromosome, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < chromosomeSize; i++)
    {
        if (chromosome[i] == 1)
        {
            SDL_RenderDrawPoint(renderer, i, 0);
        }
    }
    SDL_RenderPresent(renderer);
    return;
}

KnapSack::KnapSack(int chromosomeSize, int *weights, int *values, int knapsackSize)
{
    this->chromosomeSize = chromosomeSize;
    this->weights = weights;
    this->values = values;
    this->knapsackSize = knapsackSize;

    this->r = new int[chromosomeSize];
    this->g = new int[chromosomeSize];
    this->b = new int[chromosomeSize];

    for (int i = 0; i < chromosomeSize; i++)
    {
        r[i] = rand() % 256;
        g[i] = rand() % 256;
        b[i] = rand() % 256;
    }
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

void KnapSack::visualize(int *chromosome, SDL_Window *window, SDL_Renderer *renderer)
{
    int scale = 5;
    //Show the chromosome on the screen : 0 = black, 1 = white
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    //Draw a square of area equal to the backpack size
    SDL_Rect rect;
    rect.x = 0;
    //rect.y should be the center of the screen
    rect.y = 0;
    rect.w = knapsackSize*scale;
    rect.h = 10*scale;
    SDL_RenderFillRect(renderer, &rect);

    //Draw the items that are not taken on the side of the backpack
    for (int i = 0; i < chromosomeSize; i++)
    {
        if (chromosome[i] == 0)
        {
            SDL_Rect rect;
            rect.x = knapsackSize * scale;
            rect.y = i * 10 * scale;
            rect.w = weights[i] * scale;
            rect.h = 10 * scale;
            //the color should be (r[i], g[i], b[i])
            SDL_SetRenderDrawColor(renderer, r[i], g[i], b[i], 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    //Draw the items that are taken in the backpack
    int sumX = 0;
    for (int i = 0; i < chromosomeSize; i++)
    {
        if (chromosome[i] == 1)
        {
            SDL_Rect rect;
            rect.x = sumX * scale;
            rect.y = 0  * scale;
            rect.w = weights[i] * scale;
            rect.h = 10 * scale;

            //the color should be (r[i], g[i], b[i])
            SDL_SetRenderDrawColor(renderer, r[i], g[i], b[i], 255);
            SDL_RenderFillRect(renderer, &rect);

            sumX += weights[i];
        }
    }

    SDL_RenderPresent(renderer);

    return;
}