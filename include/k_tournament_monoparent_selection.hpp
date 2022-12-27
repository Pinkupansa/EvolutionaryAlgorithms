#ifndef K_TOURNAMENT_PARENT_SELECTION_HPP
#define K_TOURNAMENT_PARENT_SELECTION_HPP

#include "parent_selection_operator.hpp"

class KTournamentMonoParentSelection : public ParentSelectionOperator{
    public:
        KTournamentMonoParentSelection(int k);
        void select(double* populationFitnesses, int** population, int populationSize, int offspringSize, std::vector<ParentSelection*>* out);
    private:
        int k;
};

#endif // K_TOURNAMENT_PARENT_SELECTION_HPP
