#ifndef K_TOURNAMENT_PARENT_SELECTION_HPP
#define K_TOURNAMENT_PARENT_SELECTION_HPP

#include "parent_selection_operator.hpp"

class KTournamentParentSelection : public ParentSelectionOperator{
    public:
        KTournamentParentSelection(int k, double doubleParentProbability);
        void select(double* populationFitnesses, int** population, int populationSize, int offspringSize, std::vector<ParentSelection*>* out);
    private:
        int k;
        double doubleParentProbability;
        int chooseParent(double* populationFitnesses, int** population, int populationSize);
};

#endif // K_TOURNAMENT_PARENT_SELECTION_HPP
