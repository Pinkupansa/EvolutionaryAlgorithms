#include "evolution_interface.hpp"
#include <random>
#include <SDL2_framerate.h>

#include <SDL2/SDL_ttf.h>

EvolutionInterface::EvolutionInterface(EvolutionaryAlgorithm *algorithm, int maxGenerations, ProblemWrapper *problem, SDL_Window *window, SDL_Renderer *renderer)
{
    this->algorithm = algorithm;
    this->maxGenerations = maxGenerations;
    this->problem = problem;
    this->window = window;
    this->renderer = renderer;
    populationFitnesses = new double[algorithm->getPopulationSize()];
    offspringFitnesses = new double[algorithm->getPopulationSize()];
}


EvolutionInterface::~EvolutionInterface()
{
    delete[] populationFitnesses;
    delete[] offspringFitnesses;
}

void EvolutionInterface::run()
{
    srand(time(NULL));
    algorithm->initialize();
    std::cout << "EA initialized" << std::endl;
    calculatePopulationFitnesses();
    //use default sdl font
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);

    for (int i = 0; i < maxGenerations; i++)
    {
        std::cout << "Generation " << i << std::endl;

        //Write generation number on screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //Write generation number on screen in white
        SDL_Surface *generationSurface = TTF_RenderText_Solid(font, ("Generation " + std::to_string(i)).c_str(), {255, 255, 255});

        

        // std::cout << "Pop fitness calculated" << std::endl;
        algorithm->reproduce(populationFitnesses);
        // std::cout << "Reproduce done" << std::endl;
        // print current offspring
        algorithm->mutate();
        // std::cout << "Mutation done" << std::endl;
        calculateOffspringFitnesses();
        // std::cout << "Offspring fitness calculated" << std::endl;
        algorithm->select(offspringFitnesses);
        calculatePopulationFitnesses();
        
        problem->visualize(getBestIndividual(), window, renderer);
        
        
        SDL_Delay(100);
        
        printBestIndividual();
        

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