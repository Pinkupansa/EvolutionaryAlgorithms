#ifndef BENCHMARK_FUNCTIONS_HPP
#define BENCHMARK_FUNCTIONS_HPP
#include "function_wrapper.hpp"

class OneMax : public FunctionWrapper{
    public:
        OneMax(int chromosomeSize);
        ~OneMax();
        double evaluate(int* chromosome);
    private:
        int chromosomeSize;
};

class LeadingOnes : public FunctionWrapper{
    public:
        LeadingOnes(int chromosomeSize);
        ~LeadingOnes();
        double evaluate(int* chromosome);
    private:
        int chromosomeSize;
};

class Jump : public FunctionWrapper{
    public:
        Jump(int chromosomeSize, int jumpSize);
        ~Jump();
        double evaluate(int* chromosome);
    private:
        int chromosomeSize;
        int jumpSize;
};

class KnapSack : public FunctionWrapper{
    public:
        KnapSack(int chromosomeSize, int* weights, int* values, int knapsackSize);
        ~KnapSack();
        double evaluate(int* chromosome);
    private:
        int chromosomeSize;
        int* weights;
        int* values;
        int knapsackSize;
};

#endif // BENCHMARK_FUNCTIONS_HPP