//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BASESEARCHER_H
#define SERVER_SIDE_PROJECT_BASESEARCHER_H

#include "Searcher.h"
#include "../problem_solver/SearchSolution.h"

namespace algorithms {

    template<class StateType>
    class BaseSearcher : public Searcher<StateType> {
    protected:
        int counter;
    public:
        BaseSearcher();

        SearchSolution<StateType> *getSolutionPath(State<StateType> *state);

        int getCount() override;
    };
}

#endif //SERVER_SIDE_PROJECT_BASESEARCHER_H
