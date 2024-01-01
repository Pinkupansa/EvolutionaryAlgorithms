#ifndef EXCHANGE_MUTATION_HPP
#define EXCHANGE_MUTATION_HPP

#include "mutation_operator.hpp"
#include "xoroshiro_generator.hpp"
class ExchangeMutation : public MutationOperator
{
public:
    void mutate(int *chromosome, int chromosomeSize);

private:
    XoroshiroGenerator generator;
};

#endif // EXCHANGE_MUTATION_HPP