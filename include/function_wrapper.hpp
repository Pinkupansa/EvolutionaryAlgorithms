#ifndef FUNCTION_WRAPPER_HPP
#define FUNCTION_WRAPPER_HPP

class FunctionWrapper{
    public:
        virtual double evaluate(int* chromosome) = 0;
};
#endif // FUNCTION_WRAPPER_HPP