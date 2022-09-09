#include "hill_climber.hpp"
#include <random>

HillClimber::HillClimber(int chromosomeSize, double mutationConstant){
    this->chromosomeSize = chromosomeSize;
    this->mutationRate = mutationConstant/chromosomeSize;
    currentIndividual = new int[chromosomeSize];
    currentOffspring = new int[chromosomeSize];
} 

HillClimber::~HillClimber() {
    delete[] currentIndividual;
    delete[] currentOffspring;
}

void HillClimber::initialize() {
    for (int i = 0; i < chromosomeSize; i++) {
        currentIndividual[i] = rand() % 2;
    }
}

void HillClimber::mutate() {
    for (int i = 0; i < chromosomeSize; i++) {
        if (rand() % 100 < mutationRate * 100) {
            currentOffspring[i] = !currentOffspring[i];
        }
    }
}

void HillClimber::reproduce() {
    for (int i = 0; i < chromosomeSize; i++) {
        currentOffspring[i] = currentIndividual[i];
    }
}

void HillClimber::select(double* fitnesses) {
    if (fitnesses[1] > fitnesses[0]) {
        int* temp = currentIndividual;
        currentIndividual = currentOffspring;
        currentOffspring = temp;
    }
}

int** HillClimber::getCurrentIndividuals() {
    int** individuals = new int*[2];
    individuals[0] = currentIndividual;
    individuals[1] = currentOffspring;
    return individuals;
}

int HillClimber::getChromosomeSize() {
    return chromosomeSize;
}

int HillClimber::getPopulationSize() {
    return 2;
}


