#include "parent_selection_operator.hpp"

ParentSelection::ParentSelection(int numberOfParents)
{
    this->numberOfParents = numberOfParents;
    this->parentsIndices = new int[numberOfParents];
}

int ParentSelection::getNumberOfParents()
{
    return this->numberOfParents;
}

int *ParentSelection::getParentsIndices()
{
    return this->parentsIndices;
}

ParentSelection::~ParentSelection()
{
    delete[] this->parentsIndices;
}

ParentSelection *ParentSelection::clone()
{
    ParentSelection *clone = new ParentSelection(this->numberOfParents);
    for (int i = 0; i < this->numberOfParents; i++)
    {
        clone->parentsIndices[i] = this->parentsIndices[i];
    }
    return clone;
}
