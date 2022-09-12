#ifndef BENCHMARK_FUNCTIONS_HPP
#define BENCHMARK_FUNCTIONS_HPP
#include "problem_wrapper.hpp"

class OneMax : public ProblemWrapper{
    public:
        OneMax(int chromosomeSize);
        ~OneMax();
        double evaluate(int* chromosome);
        void visualize(int* chromosome, SDL_Window* window, SDL_Renderer* renderer);
    private:
        int chromosomeSize;
};

class LeadingOnes : public ProblemWrapper{
    public:
        LeadingOnes(int chromosomeSize);
        ~LeadingOnes();
        double evaluate(int* chromosome);
        void visualize(int* chromosome, SDL_Window* window, SDL_Renderer* renderer);
    private:
        int chromosomeSize;
};

class Jump : public ProblemWrapper{
    public:
        Jump(int chromosomeSize, int jumpSize);
        ~Jump();
        double evaluate(int* chromosome);
        void visualize(int* chromosome, SDL_Window* window, SDL_Renderer* renderer);
    private:
        int chromosomeSize;
        int jumpSize;
};

class KnapSack : public ProblemWrapper{
    public:
        KnapSack(int chromosomeSize, int* weights, int* values, int knapsackSize);
        ~KnapSack();
        double evaluate(int* chromosome);
        void visualize(int* chromosome, SDL_Window* window, SDL_Renderer* renderer);
    private:
        int chromosomeSize;
        int* weights;
        int* values;
        int knapsackSize;
        //objects colors for visualization
        int* r;
        int* g;
        int* b;
        
};

#endif // BENCHMARK_FUNCTIONS_HPP