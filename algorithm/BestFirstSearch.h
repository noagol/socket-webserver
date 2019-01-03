//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H
#define SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H

#include <queue>
#include <set>
#include "BaseSearcher.h"

namespace algorithms {
    template<class T>
    class BestFirstSearch : public BaseSearcher<T> {
    public:
        Solution<T> search(Searchable<T> searchable) override {
            priority_queue<State<T>> open;
            set<State<T>> openSet;
            open.push(searchable.getInitialState());
            openSet.insert(searchable.getInitialState());
            set<State<T>> closed;
            State<T> current;
            vector<State<T>> successors;
            typename vector<State<T>>::iterator it;

            do {
                // Get next element
                current = open.pop();
                openSet.erase(current);

                // Add to closed
                closed.insert(current);

                // Check if we reached the goal state
                if (searchable.isGoalState(current)) {
                    return getSolutionPath(current);
                }

                // Get next states
                successors = searchable.getAllPossibleStates(current);

                for (it = successors.begin(); it < successors.end(); it++) {
                    if (closed.find(it) == closed.end() || openSet.find(it) == openSet.end()) {
                        open.push(it);
                        openSet.insert(it);
                    }
                }
                closed.insert(current);
            } while (!open.empty());

            // No solution found
            return BaseSolution<T>();
        }

    };
}
#endif //SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H
