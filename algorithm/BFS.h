//
// Created by EB on 04/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BFS_H
#define SERVER_SIDE_PROJECT_BFS_H

#include <set>
#include <queue>
#include "BaseSearcher.h"
#include <algorithm>
#include "../helpers/Set.h"
#include <map>

using namespace std;

namespace algorithms {
    template<class StateType>
    class BFS : public BaseSearcher<StateType> {
    public:
        BFS();

        /**
        * Search using BFS in a searchable object
        * @param searchable searchable object
        * @return a solution for shortest path in the searchable
        */
        SearchSolution<StateType> *search(Searchable<StateType> *searchable) override;
    };

    template<class StateType>
    BFS<StateType>::BFS() : BaseSearcher<StateType>() {}

    /**
    * Search using BFS in a searchable object
    * @param searchable searchable object
    * @return a solution for shortest path in the searchable
    */
    template<class StateType>
    SearchSolution<StateType> *BFS<StateType>::search(Searchable<StateType> *searchable) {
        // Vertices opened counter
        this->counter = 0;

        // Queue
        queue<State<StateType> *> Q;

        // Sets
        Set<StateType, int> d;
        Set<StateType, StateType> pi;
        Set<StateType, State<StateType> *> visited;

        // Get the initial vertex
        State<StateType> *initial = searchable->getInitialState();
        d.insert(initial->getState(), 0);

        // Add to Queue
        Q.push(initial);

        // Initialization
        State<StateType> *u, *v;
        vector<State<StateType> *> adj;
        vector<State<StateType> *> goalStates;
        typename vector<State<StateType> *>::iterator it;
        typename map<State<StateType> *, int>::iterator d_it;

        // Run until Q is empty
        while (!Q.empty()) {
            // Pop vertex
            u = Q.front();
            Q.pop();

            // Inc counter
            this->counter++;

            if (!visited.exists(u->getState())) {
                // Set as visited
                visited.insert(u->getState(), u);
                // Get all adjacent
                adj = searchable->getAllPossibleStates(u);

                // For each v in adj
                for (it = adj.begin(); it != adj.end(); it++) {
                    v = *it;

                    // Inc counter
                    this->counter++;

                    // Has not been visited
                    if (!d.exists(v->getState()) || d.find(v->getState()) > d.find(u->getState()) + 1) {
                        d.insert(v->getState(), d.find(u->getState()) + 1);
                        pi.insert(v->getState(), u->getState());
                    };

                    // Add to queue
                    Q.push(v);

                    // If we reached a goal state
                    if (searchable->isGoalState(v)) {
                        goalStates.push_back(v);
                    }
                }
            }
        }

        // No goal state reached
        if (goalStates.size() == 0) {
            return nullptr;
        }

        // Get minimal path to goal state
        State<StateType> *shortestGoalState = visited.find(goalStates.at(0)->getState());

        // Find shortest path to goal
        for (it = goalStates.begin() + 1; it != goalStates.end(); it++) {
            if (d.find((*it)->getState()) < d.find(shortestGoalState->getState())) {
                shortestGoalState = visited.find((*it)->getState());
            }
        }


        // Retrieve solution path
        StateType parent;
        State<StateType> *parentState, *currentState = shortestGoalState;

        while (pi.exists(currentState->getState())) {
            parent = pi.find(currentState->getState());
            parentState = visited.find(parent);
            currentState->setParent(parentState);
            currentState = parentState;
        }

        return this->getSolutionPath(shortestGoalState);
    };
}
#endif //SERVER_SIDE_PROJECT_BFS_H
