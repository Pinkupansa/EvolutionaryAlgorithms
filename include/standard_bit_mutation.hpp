#ifndef STANDARD_BIT_MUTATION_HPP
#define STANDARD_BIT_MUTATION_HPP

#include "mutation_operator.hpp"

class StandardBitMutation : public MutationOperator
{
    public:
        StandardBitMutation(double mutationRate);
        void mutate(int *chromosome, int chromosomeSize);
    private:
        double mutationRate;
};

#endif // STANDARD_BIT_MUTATION_HPP