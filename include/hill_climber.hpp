#ifndef HILL_CLIMBER_HPP
#define HILL_CLIMBER_HPP

#include "evolutionary_algorithm.hpp"

class HillClimber : public EvolutionaryAlgorithm
{
public:
    HillClimber(int chromosomeSize, double mutationConstant);
    ~HillClimber();
    void initialize();
    void reproduce(double *populationFitnesses);
    void mutate();
    void select(double *offspringFitnesses, std::vector<int> removedPopulation, std::vector<int> addedOffspring);
    int **getCurrentPopulation();
    int **getCurrentOffspring();
    int getChromosomeSize();
    int getPopulationSize();
    int getOffspringSize();
    void postInitialization(double *fitnesses);

private:
    int chromosomeSize;
    double mutationRate;
    int *currentIndividual;
    int *currentOffspring;
    double currentIndividualFitness;
};

#endif // HILL_CLIMBER_HPP