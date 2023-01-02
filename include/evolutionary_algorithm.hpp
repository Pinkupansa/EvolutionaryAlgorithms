#ifndef EVOLUTIONARY_ALGORITHM_HPP
#define EVOLUTIONARY_ALGORITHM_HPP

#include <vector>
class EvolutionaryAlgorithm
{
public:
    virtual void initialize() = 0;
    virtual void reproduce(double *populationFitnesses) = 0;
    virtual void mutate() = 0;
    virtual void select(double *offspringFitnesses, std::vector<int> *removedPopulation, std::vector<int> *addedOffspring) = 0;
    virtual int **getCurrentPopulation() = 0;
    virtual int **getCurrentOffspring() = 0;
    virtual int getPopulationSize() = 0;
    virtual int getOffspringSize() = 0;
    virtual int getChromosomeSize() = 0;
};

#endif // EVOLUTIONARY_ALGORITHM_HPP