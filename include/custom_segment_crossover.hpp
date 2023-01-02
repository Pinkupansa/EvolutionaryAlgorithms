#ifndef CUSTOM_SEGMENT_CROSSOVER_HPP
#define CUSTOM_SEGMENT_CROSSOVER_HPP

#include "crossover_operator.hpp"

class CustomSegmentCrossover : public CrossoverOperator
{
public:
    CustomSegmentCrossover(int *segmentSizes);
    void crossover(ParentSelection *parentSelection, int chromosomeSize, int **population, int *outOffspring);

private:
    int *segmentSizes;
    int segmentCount;
};

#endif // CUSTOM_SEGMENT_CROSSOVER_HPP