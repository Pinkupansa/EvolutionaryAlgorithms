#ifndef INITIALIZER_HPP
#define INITIALIZER_HPP

class Initializer
{
    public:
        virtual void initialize(int **population, int populationSize, int chromosomeSize) = 0;
};

#endif // INITIALIZER_HPP