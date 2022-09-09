#include "evolution_interface.hpp"
#include <random>

EvolutionInterface::EvolutionInterface(EvolutionaryAlgorithm* algorithm, int maxGenerations, double(*fitnessFunction)(int*, int)){
    this->algorithm = algorithm;
    this->maxGenerations = maxGenerations;
    this->fitnessFunction = fitnessFunction;
    fitnesses = new double[algorithm->getPopulationSize()];
}

EvolutionInterface::~EvolutionInterface(){
    delete[] fitnesses;
}

void EvolutionInterface::run(){
    srand(time(NULL));
    algorithm->initialize();
    recalculateFitnesses();
    for (int i = 0; i < maxGenerations; i++) {
        algorithm->reproduce();
        algorithm->mutate();
        recalculateFitnesses();
        algorithm->select(fitnesses);
        printBestIndividual();
    }


}

void EvolutionInterface::recalculateFitnesses(){
    bestFitness = 0;
    int** individuals = algorithm->getCurrentIndividuals();
    for (int i = 0; i < algorithm->getPopulationSize(); i++) {

        fitnesses[i] = fitnessFunction(individuals[i], algorithm->getChromosomeSize());
        if (fitnesses[i] > bestFitness) {
            bestFitness = fitnesses[i];
            bestIndividualIndex = i;
        }
    }
}

int* EvolutionInterface::getBestIndividual(){
    return algorithm->getCurrentIndividuals()[bestIndividualIndex];
}

double EvolutionInterface::getBestFitness(){
    return bestFitness;
}

void EvolutionInterface::printBestIndividual(){
    int* bestIndividual = getBestIndividual();
    for (int i = 0; i < algorithm->getChromosomeSize(); i++) {
        std::cout << bestIndividual[i];
    }
    std::cout << " fitness: " << getBestFitness() << std::endl;
}