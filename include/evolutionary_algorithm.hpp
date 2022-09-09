#ifndef EVOLUTIONARY_ALGORITHM_HPP
#define EVOLUTIONARY_ALGORITHM_HPP

class EvolutionaryAlgorithm {
    public:
        virtual void initialize() = 0;
        virtual void reproduce() = 0;
        virtual void mutate() = 0;
        virtual void select(double* fitnesses) = 0;
        virtual int** getCurrentIndividuals() = 0;
        virtual int getPopulationSize() = 0;
        virtual int getChromosomeSize() = 0;
        
};
    
#endif // EVOLUTIONARY_ALGORITHM_HPP