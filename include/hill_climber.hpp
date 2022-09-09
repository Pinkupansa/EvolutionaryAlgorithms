#ifndef HILL_CLIMBER_HPP
#define HILL_CLIMBER_HPP

#include "evolutionary_algorithm.hpp"

class HillClimber : public EvolutionaryAlgorithm {
    public:
        HillClimber(int chromosomeSize, double mutationRate);
        ~HillClimber();
        void initialize();
        void reproduce();
        void mutate();
        void select(double* fitnesses);
        int** getCurrentIndividuals();
        int getChromosomeSize();
        int getPopulationSize();
        
    private:
        int chromosomeSize;
        double mutationRate;
        int* currentIndividual;
        int* currentOffspring;
};

#endif // HILL_CLIMBER_HPP