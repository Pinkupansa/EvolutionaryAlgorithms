#ifndef EVOLUTIONARY_ALGORITHM_HPP
#define EVOLUTIONARY_ALGORITHM_HPP

#include <vector>
#include "ea_log.hpp"
class EvolutionaryAlgorithm
{
public:
    virtual void initialize() = 0;
    virtual void reproduce() = 0;
    virtual void mutate() = 0;
    virtual void select(double *offspringFitnesses) = 0;
    virtual int **getCurrentPopulation() = 0;
    virtual int **getCurrentOffspring() = 0;
    virtual int getPopulationSize() = 0;
    virtual int getOffspringSize() = 0;
    virtual int getChromosomeSize() = 0;
    virtual void postInitialization(double *fitnesses) = 0;
    virtual double *getCurrentFitnesses() = 0;

    int fitnessStop = -1;
    int generationStop = -1;
    EALog *log;
};

#endif // EVOLUTIONARY_ALGORITHM_HPP