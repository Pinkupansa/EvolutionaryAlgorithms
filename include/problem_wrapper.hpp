#ifndef PROBLEM_WRAPPER_HPP
#define PROBLEM_WRAPPER_HPP
#include <SDL2/SDL.h>
class ProblemWrapper{
    public:
        virtual double evaluate(int* chromosome) = 0;
        virtual void visualize(int* chromosome, SDL_Window* window, SDL_Renderer* renderer) = 0;
};
#endif // ProblemWrapper