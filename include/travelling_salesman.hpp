#ifndef TRAVELLING_SALESMAN_HPP
#define TRAVELLING_SALESMAN_HPP
#include "problem_wrapper.hpp"
//import boost graph library
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
typedef boost::adjacency_list<boost::vecS, 
                              boost::vecS, 
                              boost::undirectedS, 
                              boost::no_property, 
                              boost::property<boost::edge_weight_t, double>> 
UndirectedWeightedGraph;

class TravellingSalesman : public ProblemWrapper
{

    public:
        TravellingSalesman(int numberOfCities, int **citiesCoordinates);
        double evaluate(int *chromosome);
        void visualize(int *chromosome, SDL_Window *window, SDL_Renderer *renderer);
    private:
        UndirectedWeightedGraph graph;
        int numberOfCities;
        int **citiesCoordinates;
        double maxDist;
        
};

#endif // TravellingSalesman