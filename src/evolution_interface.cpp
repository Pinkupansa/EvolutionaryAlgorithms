#include "evolution_interface.hpp"
#include <random>
#include <SDL2_framerate.h>

EvolutionInterface::EvolutionInterface(EvolutionaryAlgorithm *algorithm, ProblemWrapper *problem, SDL_Window *window, SDL_Renderer *renderer)
{
    this->algorithm = algorithm;
    this->problem = problem;
    this->window = window;
    this->renderer = renderer;
    this->currentGeneration = 1;

    this->populationFitnesses = new double[algorithm->getPopulationSize()];
    this->offspringFitnesses = new double[algorithm->getPopulationSize()];

    this->bestIndividualIndex = 0;
    this->bestFitness = 0;

    TTF_Init();
    this->font = TTF_OpenFont("arial.ttf", 24);

    algorithm->initialize();
    srand(time(NULL));
    std::cout << "EA initialized" << std::endl;
    calculatePopulationFitnesses();
}

EvolutionInterface::~EvolutionInterface()
{
    TTF_CloseFont(font);
    delete[] populationFitnesses;
    delete[] offspringFitnesses;
}

void EvolutionInterface::step()
{
    std::cout << "Generation " << currentGeneration << std::endl;
    algorithm->reproduce(populationFitnesses);
    algorithm->mutate();
    calculateOffspringFitnesses();
    algorithm->select(offspringFitnesses);
    calculatePopulationFitnesses();

    printBestIndividual();
    currentGeneration++;

    if (currentGeneration % 1000 == 0)
    {
        // Write generation number on screen
        /*SDL_Color color = {255, 255, 255};
        char generationText[100];
        sprintf(generationText, "Generation: %d", currentGeneration);
        SDL_Surface *surface = TTF_RenderText_Solid(font, generationText, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect = {0, 0, 1000, 100};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);*/

        problem->visualize(getBestIndividual(), window, renderer);
    }
}

void EvolutionInterface::calculatePopulationFitnesses()
{
    bestFitness = 0;
    int **individuals = algorithm->getCurrentPopulation();
    for (int i = 0; i < algorithm->getPopulationSize(); i++)
    {

        populationFitnesses[i] = problem->evaluate(individuals[i]);
        if (populationFitnesses[i] > bestFitness)
        {
            bestFitness = populationFitnesses[i];
            bestIndividualIndex = i;
           
        }
    }
}

void EvolutionInterface::calculateOffspringFitnesses()
{
    int **individuals = algorithm->getCurrentOffspring();
    for (int i = 0; i < algorithm->getOffspringSize(); i++)
    {
        offspringFitnesses[i] = problem->evaluate(individuals[i]);
    }
}

int *EvolutionInterface::getBestIndividual()
{
    return algorithm->getCurrentPopulation()[bestIndividualIndex];
}

double EvolutionInterface::getBestFitness()
{
    return bestFitness;
}

void EvolutionInterface::printBestIndividual()
{
    int *bestIndividual = getBestIndividual();
    std::cout << "Best individual is : ";
    for (int i = 0; i < algorithm->getChromosomeSize(); i++)
    {

        std::cout << bestIndividual[i] << " ";
    }
    std::cout << "fitness : " << bestFitness << std::endl;
}