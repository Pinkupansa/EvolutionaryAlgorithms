#ifndef PARTIAL_SHUFFLE_HPP
#define PARTIAL_SHUFFLE_HPP

#include "mutation_operator.hpp"
#include "xoroshiro_generator.hpp"

class PartialShuffle : public MutationOperator
{
public:
    void mutate(int *chromosome, int chromosomeSize);

private:
    XoroshiroGenerator generator;
};
#endif // PARTIAL_SHUFFLE_HPP