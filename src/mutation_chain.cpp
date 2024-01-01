#include "mutation_chain.hpp"

MutationChain::MutationChain(MutationOperator **mutationOperators, double *probabilities, int numberOfMutationOperators)
{
    this->mutationOperators = mutationOperators;
    this->numberOfMutationOperators = numberOfMutationOperators;
    this->probabilities = probabilities;
}

void MutationChain::mutate(int *chromosome, int chromosomeSize)
{
    for (int i = 0; i < numberOfMutationOperators; i++)
    {
        if (generator.uniformDouble(0, 1) < probabilities[i])
        {
            mutationOperators[i]->mutate(chromosome, chromosomeSize);
        }
    }
}
