//
// Created by EB on 05/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_DFS_H
#define SERVER_SIDE_PROJECT_DFS_H

#include "../helpers/Set.h"
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
            stack<State<StateType> *> S;
            Set<StateType, int> d;
            Set<StateType, State<StateType> *> pi;

            PointerSet<State<StateType>> visited;

            // Get the initial vertex
            State<StateType> *initial = searchable->getInitialState();
            d.insert(initial->getState(), 0);
            pi.insert(initial->getState(), initial);

            // Add to Queue
            S.push(initial);

            // Initialization
            State<StateType> *u, *v;
            vector<State<StateType> *> adj;
            vector<State<StateType> *> goalStates;
            typename vector<State<StateType> *>::iterator it;
            typename map<State<StateType>*, int>::iterator d_it;

            // Run until Q is empty
            while (!S.empty()) {
                // Pop vertex
                u = S.top();
                S.pop();
                if (!visited.exists(u)) {
                    // Set as visited
                    visited.add(u);
                    // Get all adjacent
                    adj = searchable->getAllPossibleStates(u);

                    // For each v in adj
                    for (it = adj.begin(); it != adj.end(); it++) {
                        v = *it;

                        // Has not been visited
                        if (!d.exists(v->getState()) || d.find(v->getState()) > d.find(u->getState()) + v->getCost()) {
                            d.insert(v->getState(), d.find(u->getState()) + v->getCost());
                            pi.insert(v->getState(), v);
                        };

                        S.push(v);

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
            State<StateType> *shortestGoalState = pi.find(goalStates.at(0)->getState());

            for (it = goalStates.begin() + 1; it != goalStates.end(); it++) {
                if (d.find((*it)->getState()) < d.find(shortestGoalState->getState())) {
                    shortestGoalState = pi.find((*it)->getState());
                }
            }

            return this->getSolutionPath(shortestGoalState);
        }
    };
}
#endif //SERVER_SIDE_PROJECT_DFS_H
