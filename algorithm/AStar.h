//
// Created by EB on 05/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_ASTAR_H
#define SERVER_SIDE_PROJECT_ASTAR_H

#include "BaseSearcher.h"
#include <map>
#include <queue>
#include <Set.h>

namespace algorithms {
    template<class StateType>
    class AStar : public BaseSearcher<StateType> {

    public:
        AStar() {}

        class Vertex {
        public:
            State<StateType> *state;
            // f = g + h
            double total, dFromStart, estimatedToEnd;

            Vertex() {}

            Vertex(State<StateType> *s, double t, double d, double e) : state(s), total(t), dFromStart(d),
                                                                        estimatedToEnd(e) {}

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
                return lhs.total > rhs.total;
            }
        };

//         //Comparator
//        struct EqualityVertex : public binary_function<Vertex, Vertex, bool> {
//            bool operator()(const Vertex lhs, const Vertex rhs) const {
//                return *(lhs.state) < *(rhs.state);
//            }
//        };

        Solution<StateType> *search(Searchable<StateType> *searchable) override {
            // Priority queue by total value
            priority_queue<Vertex, vector<Vertex>, CompareVertex> Q;

            // Sets for handle visited nodes
            Set<StateType, Vertex> open;
            Set<StateType, Vertex> closed;

            // Get initial state
            State<StateType> *initialState = searchable->getInitialState();
            Vertex initial = Vertex(initialState, 0, 0, searchable->estimateDistanceToGoal(initialState));
            open.insert(initial.state->getState(), initial); // Add to open set
            Q.push(initial); // Add to priority queue

            // Current nodes
            Vertex u, v;
            vector<State<StateType> *> adj;
            typename vector<State<StateType> *>::iterator it;

            while (!open.empty()) {
                // Get lowest total vertex
                u = Q.top();
                Q.pop();

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
                    if (closed.exists((*it)->getState())) {
                        continue;
                    }

                    // Set as vertex
                    v.state = *it;
                    v.dFromStart = u.dFromStart + v.state->getCost();
                    v.estimatedToEnd = searchable->estimateDistanceToGoal(*it);
                    v.total = v.dFromStart + v.estimatedToEnd;

                    // Search in open
                    if (!open.exists(v.state->getState())) {
                        // Not in open and not in closed
                        open.insert(v.state->getState(), v);
                        Q.push(v);
                    }

                    else if (open.find(v.state->getState()).dFromStart > v.dFromStart) {
                         //The vertex is found in open with better values
                        open.insert(v.state->getState(), v);
                    }
                }

            }

            // No solution found
            return nullptr;
        }

    };


}

#endif //SERVER_SIDE_PROJECT_ASTAR_H
