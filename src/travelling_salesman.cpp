#include "travelling_salesman.hpp"


TravellingSalesman::TravellingSalesman(int numberOfCities, int **citiesCoordinates)
{
    this->numberOfCities = numberOfCities;
    this->citiesCoordinates = citiesCoordinates;
    //create graph
    graph = UndirectedWeightedGraph(numberOfCities);
    //add edges
    //weight map
    boost::property_map<UndirectedWeightedGraph, boost::edge_weight_t>::type weightmap = boost::get(boost::edge_weight, graph);
    this->maxDist = 0;
    for (int i = 0; i < numberOfCities; i++)
    {
        for (int j = i + 1; j < numberOfCities; j++)
        {
            int x1 = citiesCoordinates[i][0];
            int y1 = citiesCoordinates[i][1];
            int x2 = citiesCoordinates[j][0];
            int y2 = citiesCoordinates[j][1];
            int distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
            boost::add_edge(i, j, graph);
            weightmap[boost::edge(i, j, graph).first] = distance;
            if(distance > maxDist)
            {
                maxDist = distance;
            }
        }
    }
}

double TravellingSalesman::evaluate(int *chromosome)
{
    double totalDistance = 0;
    for (int i = 0; i < numberOfCities - 1; i++)
    {
        int city1 = chromosome[i];
        int city2 = chromosome[i + 1];
        totalDistance += boost::get(boost::edge_weight, graph, boost::edge(city1, city2, graph).first);
    }
    totalDistance += boost::get(boost::edge_weight, graph, boost::edge(chromosome[numberOfCities - 1], chromosome[0], graph).first);
    return numberOfCities*maxDist-totalDistance;
}

void TravellingSalesman::visualize(int *chromosome, SDL_Window *window, SDL_Renderer *renderer)
{
    //clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    //draw 10 px wide points for cities
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < numberOfCities; i++)
    {
        int x = citiesCoordinates[i][0];
        int y = citiesCoordinates[i][1];
        SDL_Rect rect = {x - 5, y - 5, 10, 10};
        SDL_RenderFillRect(renderer, &rect);
    }
    
    //draw lines
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < numberOfCities - 1; i++)
    {
        int city1 = chromosome[i];
        int city2 = chromosome[i + 1];
        
        SDL_RenderDrawLine(renderer, citiesCoordinates[city1][0], citiesCoordinates[city1][1], citiesCoordinates[city2][0], citiesCoordinates[city2][1]);
    }
    //draw last line
    int city1 = chromosome[numberOfCities - 1];
    int city2 = chromosome[0];
    SDL_RenderDrawLine(renderer, citiesCoordinates[city1][0], citiesCoordinates[city1][1], citiesCoordinates[city2][0], citiesCoordinates[city2][1]);
    //update screen
    SDL_RenderPresent(renderer);
}