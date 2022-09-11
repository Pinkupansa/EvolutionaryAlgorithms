#ifndef PROBLEM_WRAPPER_HPP
#define PROBLEM_WRAPPER_HPP

class ProblemWrapper{
    public:
        virtual double evaluate(int* chromosome) = 0;
        virtual void visualize(int* chromosome) = 0;
};
#endif // ProblemWrapper