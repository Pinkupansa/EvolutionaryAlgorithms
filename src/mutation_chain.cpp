#include "mutation_chain.hpp"
#include <random>

MutationChain::MutationChain(MutationOperator** mutationOperators, double* probabilities, int numberOfMutationOperators)
{
    this->mutationOperators = mutationOperators;
    this->numberOfMutationOperators = numberOfMutationOperators;
    this->probabilities = probabilities;
}

void MutationChain::mutate(int *chromosome, int chromosomeSize)
{
    for (int i = 0; i < numberOfMutationOperators; i++)
    {
        if (rand() % 1000 < probabilities[i] * 1000)
        {
            mutationOperators[i]->mutate(chromosome, chromosomeSize);
        }
    }
}
