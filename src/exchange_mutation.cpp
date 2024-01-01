#include "exchange_mutation.hpp"

void ExchangeMutation::mutate(int *chromosome, int chromosomeSize)
{
    int i = generator.uniformInt(0, chromosomeSize - 1);
    int j = generator.uniformInt(0, chromosomeSize - 1);

    int temp = chromosome[i];
    chromosome[i] = chromosome[j];
    chromosome[j] = temp;
}