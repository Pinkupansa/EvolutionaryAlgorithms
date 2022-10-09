#ifndef EXCHANGE_MUTATION_HPP
#define EXCHANGE_MUTATION_HPP

#include "mutation_operator.hpp"

class ExchangeMutation : public MutationOperator
{
    public:
        void mutate(int *chromosome, int chromosomeSize);
};

#endif // EXCHANGE_MUTATION_HPP