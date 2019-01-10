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

        /**
        * Search using DFS in a searchable object
        * @param searchable searchable object
        * @return a solution for shortest path in the searchable
        */
        SearchSolution<StateType> *search(Searchable<StateType> *searchable) override {
            stack<State<StateType> *> S;
            Set<StateType, int> d;
            Set<StateType, StateType> pi;

            Set<StateType, State<StateType> *> visited;

            this->counter = 0;

            // Get the initial vertex
            State<StateType> *initial = searchable->getInitialState();
            d.insert(initial->getState(), 0);

            // Add to Queue
            S.push(initial);

            // Initialization
            State<StateType> *u, *v;
            vector<State<StateType> *> adj;
            vector<State<StateType> *> goalStates;
            typename vector<State<StateType> *>::iterator it;
            typename map<State<StateType> *, int>::iterator d_it;

            // Run until Q is empty
            while (!S.empty()) {
                // Pop vertex
                u = S.top();
                S.pop();

                this->counter++;

                if (!visited.exists(u->getState())) {
                    // Set as visited
                    visited.insert(u->getState(), u);
                    // Get all adjacent
                    adj = searchable->getAllPossibleStates(u);

                    // For each v in adj
                    for (it = adj.begin(); it != adj.end(); it++) {
                        v = *it;
                        this->counter++;

                        // Has not been visited
                        if (!d.exists(v->getState()) || d.find(v->getState()) > d.find(u->getState()) + v->getCost()) {
                            d.insert(v->getState(), d.find(u->getState()) + 1);
                            pi.insert(v->getState(), u->getState());
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
            State<StateType> *shortestGoalState = visited.find(goalStates.at(0)->getState());

            for (it = goalStates.begin() + 1; it != goalStates.end(); it++) {
                if (d.find((*it)->getState()) < d.find(shortestGoalState->getState())) {
                    shortestGoalState = visited.find((*it)->getState());
                }
            }

            StateType parent;
            State<StateType> *parentState, *currentState = shortestGoalState;

            while (pi.exists(currentState->getState())) {
                parent = pi.find(currentState->getState());
                parentState = visited.find(parent);
                currentState->setParent(parentState);
                currentState = parentState;
            }

            return this->getSolutionPath(shortestGoalState);
        }
    };
}
#endif //SERVER_SIDE_PROJECT_DFS_H
