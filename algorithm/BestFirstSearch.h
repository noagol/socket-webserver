//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H
#define SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H

#include <queue>
#include <set>
#include "BaseSearcher.h"

namespace algorithms {
    template<class StateType>
    class BestFirstSearch : public BaseSearcher<StateType> {
    public:
        Solution<StateType>* search(Searchable<StateType>* searchable) override {
            priority_queue <State<StateType>> open;
            set <State<StateType>> openSet;
            open.push(searchable->getInitialState());
            openSet.insert(searchable->getInitialState());
            set <State<StateType>> closed;
            State<StateType> current;
            vector<State<StateType>> successors;
            typename vector<State<StateType>>::iterator it;

            do {
                // Get next element
                current = open.pop();
                openSet.erase(current);

                // Add to closed
                closed.insert(current);

                // Check if we reached the goal state
                if (searchable->isGoalState(current)) {
                    return getSolutionPath(current);
                }

                // Get next states
                successors = searchable->getAllPossibleStates(current);

                for (it = successors.begin(); it < successors.end(); it++) {
                    if (closed.find(it) == closed.end() || openSet.find(it) == openSet.end()) {
                        open.push(it);
                        openSet.insert(it);
                    }
                }
                closed.insert(current);
            } while (!open.empty());

            // No solution found
            return nullptr;
        }

    };
}
#endif //SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H
