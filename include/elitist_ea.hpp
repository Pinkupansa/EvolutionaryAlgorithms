#ifndef ELITIST_EA_HPP
#define ELITIST_EA_HPP
#include "evolutionary_algorithm.hpp"
#include "mutation_operator.hpp"
#include "initializer.hpp"
class ElitistEA : public EvolutionaryAlgorithm{
    public:
        ElitistEA(int populationSize, int offspringSize, int chromosomeSize, MutationOperator* mutationOperator, Initializer* initializer);
        ~ElitistEA();
        void reproduce(double* populationFitnesses);
        void mutate();
        void select(double* offspringFitnesses);
        void initialize();
        int** getCurrentPopulation();
        int** getCurrentOffspring();
        int getPopulationSize();
        int getChromosomeSize();
        int getOffspringSize();

    private:
        int populationSize;
        int offspringSize;
        int chromosomeSize;
        MutationOperator* mutationOperator;
        Initializer* initializer;
        int** population;
        int** offspring;
        double* populationFitnesses;
        
};

#endif //ELITIST_EA_HPP