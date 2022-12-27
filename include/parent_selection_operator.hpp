#ifndef PARENT_SELECTION_OPERATOR_HPP
#define PARENT_SELECTION_OPERATOR_HPP
#include <vector>
class ParentSelection{
    public:
        ParentSelection(int numberOfParents);
        ~ParentSelection();
        int getNumberOfParents();
        int* getParentsIndices();
        
    private:
        int numberOfParents;
        int* parentsIndices;
};

class ParentSelectionOperator{
    public:
        virtual void select(double* populationFitnesses, int** population, int populationSize, int offspringSize, std::vector<ParentSelection*>* out) = 0;
};
#endif // PARENT_SELECTION_OPERATOR_HPP