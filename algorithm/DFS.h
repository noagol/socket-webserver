//
// Created by EB on 05/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_DFS_H
#define SERVER_SIDE_PROJECT_DFS_H

#include <set>
#include <stack>
#include "BaseSearcher.h"
#include <algorithm>
#include "../helpers/PointerSet.h"
#include <map>

using namespace std;

namespace algorithms {
    template<class StateType>
    class DFS : public BaseSearcher<StateType> {
    public:
        DFS() : BaseSearcher<StateType>() {}

        Solution<StateType> *search(Searchable<StateType> *searchable) override {
            stack<State<StateType> *> Q;
            map<State<StateType> *, int> d;
            PointerSet<State<StateType>> visited;

            // Get the initial vertex
            State<StateType> *initial = searchable->getInitialState();
            d[initial] = 0;

            // Add to Queue
            Q.push(initial);

            // Initialization
            State<StateType> *u, *v;
            vector<State<StateType> *> adj;
            vector<State<StateType> *> goalStates;
            typename vector<State<StateType> *>::iterator it;

            // Run until Q is empty
            while (!Q.empty()) {
                // Pop vertex
                u = Q.top();
                Q.pop();
                if (!visited.exists(u)) {
                    // Set as visited
                    visited.add(u);
                    // Get all adjacent
                    adj = searchable->getAllPossibleStates(u);

                    // For each v in adj
                    for (it = adj.begin(); it != adj.end(); it++) {
                        v = *it;

                        // Has not been visited
                        d[v] = d[u] + 1;
                        Q.push(v);

                        if (searchable->isGoalState(v)) {
                            goalStates.push_back(v);
                        }

                    }
                }
            }

            if (goalStates.size() == 0) {
                return nullptr;
            }

            // Get minimal path to goal state
            State<StateType> *shortestGoalState = goalStates.at(0);

            for (it = goalStates.begin() + 1; it != goalStates.end(); it++) {
                if (d[*it] < d[shortestGoalState]) {
                    shortestGoalState = *it;
                }
            }

            return this->getSolutionPath(shortestGoalState);
        }
    };
}
#endif //SERVER_SIDE_PROJECT_DFS_H
