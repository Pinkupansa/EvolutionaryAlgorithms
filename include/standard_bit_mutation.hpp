#ifndef STANDARD_BIT_MUTATION_HPP
#define STANDARD_BIT_MUTATION_HPP

#include "mutation_operator.hpp"
#include <random>
class StandardBitMutation : public MutationOperator
{
public:
    StandardBitMutation(double mutationRate);
    void mutate(int *chromosome, int chromosomeSize);

private:
    double mutationRate;
    // urng is a uniform random number generator
    std::default_random_engine urng;
};

#endif // STANDARD_BIT_MUTATION_HPP