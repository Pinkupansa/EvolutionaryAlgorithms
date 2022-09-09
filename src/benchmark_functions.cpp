#include "benchmark_functions.hpp"
double oneMax(int* chromosome, int chromosomeSize) {
    double fitness = 0;
    for (int i = 0; i < chromosomeSize; i++) {
        fitness += chromosome[i];
    }
    return fitness;
}

double leadingOnes(int* chromosome, int chromosomeSize) {
    double fitness = 0;
    for (int i = 0; i < chromosomeSize; i++) {
        if (chromosome[i] == 1) {
            fitness++;
        } else {
            break;
        }
    }
    return fitness;
}

double jump(int* chromosome, int chromosomeSize, int jumpSize) {
    double oneMaxFitness = oneMax(chromosome, chromosomeSize);
    
    if(oneMaxFitness <= chromosomeSize-jumpSize || oneMaxFitness == chromosomeSize) {
        return oneMaxFitness;
    } else {
        return chromosomeSize - oneMaxFitness;
    }
}