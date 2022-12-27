#include "partial_shuffle.hpp"
#include <random>

void PartialShuffle::mutate(int *chromosome, int chromosomeSize)
{
    int i = rand() % chromosomeSize;
    int j = rand() % chromosomeSize;

    if (i > j)
    {
        int temp = i;
        i = j;
        j = temp;
    }

    // Shuffle the subarray
    for (int k = i; k < j; k++)
    {
        int l = rand() % (j - k + 1) + k;
        int temp = chromosome[k];
        chromosome[k] = chromosome[l];
        chromosome[l] = temp;
    }

}