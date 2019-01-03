//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BASESEARCHER_H
#define SERVER_SIDE_PROJECT_BASESEARCHER_H

#include "Searcher.h"
#include "../problem_solver/BaseSolution.h"

namespace algorithms {

    template<class T>
    class BaseSearcher : public Searcher<T> {
    public:
        BaseSearcher() {}

    protected:
        Solution<T>* getSolutionPath(State<T> state) {
            vector<State<T>> path;
            int cost = 0;

            path.push_back(state);

            while (state.doesHaveParent()) {
                state = state.getParent();
                path.push_back(state);
                cost += state.getCost();
            }

            reverse(path.begin(), path.end());

            return new BaseSolution<T>(path, cost);
        }
    };
}

#endif //SERVER_SIDE_PROJECT_BASESEARCHER_H
