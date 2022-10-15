#include "exchange_mutation.hpp"
#include <random>

void ExchangeMutation::mutate(int *chromosome, int chromosomeSize)
{
    int i = rand() % chromosomeSize;
    int j = rand() % chromosomeSize;

    int temp = chromosome[i];
    chromosome[i] = chromosome[j];
    chromosome[j] = temp;
}