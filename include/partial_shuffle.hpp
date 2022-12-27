#ifndef PARTIAL_SHUFFLE_HPP
#define PARTIAL_SHUFFLE_HPP

#include "mutation_operator.hpp"

class PartialShuffle : public MutationOperator
{
    public:
        void mutate(int *chromosome, int chromosomeSize);
    
};
#endif // PARTIAL_SHUFFLE_HPP