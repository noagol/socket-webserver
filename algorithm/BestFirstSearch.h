//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H
#define SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H

#include <set>
#include <queue>
#include "BaseSearcher.h"
#include <algorithm>
#include "../helpers/PointerSet.h"

using namespace std;

namespace algorithms {
    template<class StateType>
    class BestFirstSearch : public BaseSearcher<StateType> {
    public:
        BestFirstSearch() : BaseSearcher<StateType>() {}

        Solution<StateType> *search(Searchable<StateType> *searchable) override {
            priority_queue<State<StateType> *> open;
            PointerSet<State<StateType>> openSet;
            open.push(searchable->getInitialState());
            openSet.add(searchable->getInitialState());
            PointerSet<State<StateType>> closed;
            State<StateType> *current;
            vector<State<StateType> *> successors;
            typename vector<State<StateType> *>::iterator it;

            do {
                // Get next element
                current = open.top();
                open.pop();

                openSet.remove(current);

                // Add to closed
                closed.add(current);

                // Check if we reached the goal state
                if (searchable->isGoalState(current)) {
                    return getSolutionPath(current);
                }

                // Get next states
                successors = searchable->getAllPossibleStates(current);

                for (it = successors.begin(); it < successors.end(); it++) {
                    if (!closed.exists(*it) || !openSet.exists(*it)) {
                        open.push(*it);
                        openSet.add(*it);
                    }
                }
                closed.add(current);
            } while (!open.empty());

            // No solution found
            return nullptr;
        }

        // TODO: MOVE ONE LEVEL UP
        Solution<StateType> *getSolutionPath(State<StateType> *state) {
            vector<State<StateType>> path;
            int cost = 0;

            path.push_back(*state);

            while (state->getParent() != nullptr) {
                state = state->getParent();
                path.push_back(*state); // TODO: May want to copy all pointers to other place on heap
                cost += state->getCost();
            }

            reverse(path.begin(), path.end());

            return new BaseSolution<StateType>(path, cost);
        }

    };
}
#endif //SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H
