#ifndef EVOLUTION_INTERFACE_HPP
#define EVOLUTION_INTERFACE_HPP
#include <bits/stdc++.h> 
#include "evolutionary_algorithm.hpp"

class EvolutionInterface{

    public:
        EvolutionInterface(EvolutionaryAlgorithm* algorithm, int maxGenerations, double(*fitnessFunction)(int*, int));
        ~EvolutionInterface();
        void run();
        int* getBestIndividual();
        double getBestFitness();
        
    private:
        EvolutionaryAlgorithm* algorithm;

        double(*fitnessFunction)(int*, int);
        double* fitnesses;

        int maxGenerations;
        
        int bestIndividualIndex;
        double bestFitness;

        void recalculateFitnesses();
        void printBestIndividual();
};


#endif //EVOLUTION_INTERFACE_HPP