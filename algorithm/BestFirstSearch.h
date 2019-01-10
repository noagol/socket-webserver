//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H
#define SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H

#include <set>
#include <queue>
#include "BaseSearcher.h"
#include <algorithm>
#include <Set.h>
#include "../helpers/PointerSet.h"

using namespace std;

namespace algorithms {
    template<class StateType>
    class BestFirstSearch : public BaseSearcher<StateType> {
    public:
        BestFirstSearch() : BaseSearcher<StateType>() {}

        class Vertex {
        public:
            State<StateType> *state;
            // f = g + h
            double dFromStart;

            Vertex() {}

            Vertex(State<StateType> *s, double d) : state(s), dFromStart(d){}

            bool operator<(const Vertex &right) const {
                return *(this->state) < *(right.state);
            }

            bool operator==(const Vertex &right) const {
                return *(this->state) == *(right.state);
            }
        };

        // Comparator
        struct CompareVertex : public binary_function<Vertex, Vertex, bool> {
            bool operator()(const Vertex lhs, const Vertex rhs) const {
                return lhs.dFromStart > rhs.dFromStart;
            }
        };


        SearchSolution<StateType> *search(Searchable<StateType> *searchable) override {
            // Priority queue by total value
            priority_queue<Vertex, vector<Vertex>, CompareVertex> Q;

            // Sets for handle visited nodes
            Set<StateType, Vertex> open;
            Set<StateType, Vertex> closed;

            // Get initial state
            State<StateType> *initialState = searchable->getInitialState();
            Vertex initial = Vertex(initialState, 0);
            open.insert(initial.state->getState(), initial); // Add to open set
            Q.push(initial); // Add to priority queue

            // Current nodes
            Vertex u, v;
            vector<State<StateType> *> adj;
            typename vector<State<StateType> *>::iterator it;
            this->counter = 0;

            while (!open.empty()) {
                // Get lowest total vertex
                u = Q.top();
                Q.pop();
                this->counter++;

                if (closed.exists(u.state->getState())) {
                    continue;
                }

                if (searchable->isGoalState(u.state)) {
                    // Reached goal state
                    return this->getSolutionPath(u.state);
                }

                // Remove from open and add to closed
                open.remove(u.state->getState());
                closed.insert(u.state->getState(), u);

                // Get next states
                adj = searchable->getAllPossibleStates(u.state);
                for (it = adj.begin(); it != adj.end(); it++) {
                    this->counter++;

                    if (closed.exists((*it)->getState())) {
                        continue;
                    }

                    // Set as vertex
                    v.state = *it;
                    v.dFromStart = u.dFromStart + v.state->getCost();

                    // Search in open
                    if (!open.exists(v.state->getState())) {
                        // Not in open and not in closed
                        open.insert(v.state->getState(), v);
                        Q.push(v);
                    } else if (open.find(v.state->getState()).dFromStart > v.dFromStart) {
                        //The vertex is found in open with better values
                        open.insert(v.state->getState(), v);
                        Q.push(v);
                    }
                }

            }

            // No solution found
            return nullptr;
        }


//        SearchSolution<StateType> *search(Searchable<StateType> *searchable) override {
//            // Priority queue
//            priority_queue<State<StateType> *, vector<State<StateType> *>, CompareState<StateType>> open;
//            // Open and closed sets
//            PointerSet<State<StateType>> openSet;
//            PointerSet<State<StateType>> closed;
//
//            // Add the initial state to open
//            open.push(searchable->getInitialState());
//            openSet.add(searchable->getInitialState());
//
//            // Initializations
//            State<StateType> *current;
//            vector<State<StateType> *> successors;
//            typename vector<State<StateType> *>::iterator it;
//
//            // Handled vertices
//            this->counter = 0;
//
//            do {
//                // Get next element
//                current = open.top();
//                open.pop();
//                openSet.remove(current);
//
//                // Inc counter
//                this->counter++;
//
//                // Add to closed
//                closed.add(current);
//
//                // Check if we reached the goal state
//                if (searchable->isGoalState(current)) {
//                    return this->getSolutionPath(current);
//                }
//
//                // Get next states
//                successors = searchable->getAllPossibleStates(current);
//
//                // Iterate through the successors
//                for (it = successors.begin(); it < successors.end(); it++) {
//                    // Inc counter for each successor
//                    this->counter++;
//
//                    // Check if in open or closed
//                    if (!closed.exists(*it) && !openSet.exists(*it)) {
//                        open.push(*it);
//                        openSet.add(*it);
//                    }
//                }
//                closed.add(current);
//            } while (!open.empty());
//
//            // No solution found
//            return nullptr;
//        }
    };
}
#endif //SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H
