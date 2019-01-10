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


    /**
     * Base class for searchers
     * @tparam StateType type of the state to search within
     */
    template<class StateType>
    BaseSearcher<StateType>::BaseSearcher() {}

    /**
     * Get solution object from a given goal state
     * @tparam StateType type of the state to search within
     * @param state last state
     * @return solution object
     */
    template<class StateType>
    SearchSolution<StateType> *BaseSearcher<StateType>::getSolutionPath(State<StateType> *state) {
        vector<State<StateType> *> path;
        int cost = 0;

        State<StateType> *copiedState = new State<StateType>;
        *copiedState = *state;
        path.push_back(copiedState);
        cost += copiedState->getCost();


        // Run through the path
        do {
            // Get parent
            state = copiedState->getParent();
            // Allocate new memory
            copiedState = new State<StateType>;
            // Copy parent
            *copiedState = *state;
            // Add parent to array
            path.push_back(copiedState);
            // Add the cost to the total
            cost += copiedState->getCost();
        } while (copiedState->getParent() != nullptr);

        // Reverse the path
        reverse(path.begin(), path.end());

        return new SearchSolution<StateType>(path, cost);
    }

    /**
     * Count of vertices the searcher read
     * @tparam StateType type of the state to search within
     * @return the count
     */
    template<class StateType>
    int BaseSearcher<StateType>::getCount() {
        return counter;
    }
}

#endif //SERVER_SIDE_PROJECT_BASESEARCHER_H
