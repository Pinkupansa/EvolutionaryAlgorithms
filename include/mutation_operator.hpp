#ifndef MUTATION_OPERATOR_HPP
#define MUTATION_OPERATOR_HPP

class MutationOperator
{
    public:
        virtual void mutate(int *chromosome, int chromosomeSize) = 0;
};
#endif // MUTATION_OPERATOR_HPP