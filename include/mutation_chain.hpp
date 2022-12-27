#ifndef MUTATION_CHAIN_HPP
#define MUTATION_CHAIN_HPP

#include "mutation_operator.hpp"

class MutationChain : public MutationOperator
{
    public:
        MutationChain(MutationOperator** mutationOperators, double* probabilities, int numberOfMutationOperators);
        void mutate(int *chromosome, int chromosomeSize);
    private:
        MutationOperator** mutationOperators;
        int numberOfMutationOperators;
        double* probabilities;
};

#endif // MUTATION_CHAIN_HPP