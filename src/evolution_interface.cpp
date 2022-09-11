#include "evolution_interface.hpp"
#include <random>

EvolutionInterface::EvolutionInterface(EvolutionaryAlgorithm* algorithm, int maxGenerations, FunctionWrapper* fitnessFunction) {
    this->algorithm = algorithm;
    this->maxGenerations = maxGenerations;
    this->fitnessFunction = fitnessFunction;
    populationFitnesses = new double[algorithm->getPopulationSize()];
    offspringFitnesses = new double[algorithm->getOffspringSize()];

}

EvolutionInterface::~EvolutionInterface(){
    delete[] populationFitnesses;
    delete[] offspringFitnesses;
}

void EvolutionInterface::run(){
    srand(time(NULL));
    algorithm->initialize();
    std::cout << "EA initialized" << std::endl;
    calculatePopulationFitnesses();
    for (int i = 0; i < maxGenerations; i++) {
        std::cout <<"Generation " << i << std::endl;
        
        //std::cout << "Pop fitness calculated" << std::endl;
        algorithm->reproduce(populationFitnesses);
        //std::cout << "Reproduce done" << std::endl;
        //print current offspring
        algorithm->mutate();
        //std::cout << "Mutation done" << std::endl;
        calculateOffspringFitnesses();
        //std::cout << "Offspring fitness calculated" << std::endl;
        algorithm->select(offspringFitnesses);
        calculatePopulationFitnesses();
        
        printBestIndividual();
    }


}

void EvolutionInterface::calculatePopulationFitnesses(){
    bestFitness = 0;
    int** individuals = algorithm->getCurrentPopulation();
    for (int i = 0; i < algorithm->getPopulationSize(); i++) {

        populationFitnesses[i] = fitnessFunction->evaluate(individuals[i]);
        if (populationFitnesses[i] > bestFitness) {
            bestFitness = populationFitnesses[i];
            bestIndividualIndex = i;
        }
    }
}

void EvolutionInterface::calculateOffspringFitnesses(){
    int** individuals = algorithm->getCurrentOffspring();
    for (int i = 0; i < algorithm->getOffspringSize(); i++) {
        offspringFitnesses[i] = fitnessFunction->evaluate(individuals[i]);
    }
}

int* EvolutionInterface::getBestIndividual(){
    return algorithm->getCurrentPopulation()[bestIndividualIndex];
}

double EvolutionInterface::getBestFitness(){
    return bestFitness;
}

void EvolutionInterface::printBestIndividual(){
    int* bestIndividual = getBestIndividual();
    std::cout << "Best individual is : ";
    for (int i = 0; i < algorithm->getChromosomeSize(); i++) {

        std::cout << bestIndividual[i] << " ";
    }
    std::cout << "fitness : " << bestFitness << std::endl;
}