//
// Created by EB on 05/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_ASTAR_H
#define SERVER_SIDE_PROJECT_ASTAR_H

#include "BaseSearcher.h"
#include <map>
#include <PointerSet.h>
#include <queue>

namespace algorithms {
    template<class StateType>
    class AStar : public BaseSearcher<StateType> {

    public:
        AStar() {}

        struct Vertex {
            State<StateType> *state;
            // f = g + h
            double total, dFromStart, estimatedToEnd;
        };

        // Comparator
        struct CompareVertex : public binary_function<Vertex, Vertex, bool> {
            bool operator()(const Vertex lhs, const Vertex rhs) const {
                return lhs.total > rhs.total;
            }
        };

        // Comparator
        struct EqualityVertex : public binary_function<Vertex, Vertex, bool> {
            bool operator()(const Vertex lhs, const Vertex rhs) const {
                return *lhs.state < *rhs.state;
            }
        };

        Solution<StateType> *search(Searchable<StateType> *searchable) override {
            // Priority queue by total value
            priority_queue<Vertex, vector<Vertex>, CompareVertex> Q;

            // Sets for handle visited nodes
            set<Vertex, EqualityVertex> open;
            set<Vertex, EqualityVertex> closed;

            // Get initial state
            State<StateType> *initialState = searchable->getInitialState();
            Vertex initial = {initialState, 0, 0, searchable->estimateDistanceToGoal(initialState)};
            open.insert(initial); // Add to open set
            Q.push(initial); // Add to priority queue

            // Current nodes
            Vertex u, v;
            vector<State<StateType> *> adj;
            typename vector<State<StateType> *>::iterator it;
            typename set<Vertex>::iterator w_it;

            while (!open.empty()) {
                // Get lowest total vertex
                u = Q.top();
                Q.pop();

                open.erase(u);

                // Get next states
                adj = searchable->getAllPossibleStates(u.state);
                for (it = adj.begin(); it != adj.end(); it++) {
                    // Set as vertex
                    v.state = *it;
                    v.dFromStart = u.dFromStart + v.state->getCost();
                    v.estimatedToEnd = searchable->estimateDistanceToGoal(*it);
                    v.total = v.dFromStart + v.estimatedToEnd;

                    if (searchable->isGoalState(*it)) {
                        // Reached goal state
                        return this->getSolutionPath(*it);
                    } else {
                        // Search in open
                        w_it = open.find(v);
                        if (w_it != open.end() && (*w_it).total < v.total) {
                            // Check if already in open with lower total
                            continue;
                        }

                        w_it = closed.find(v);
                        if (w_it != closed.end() && (*w_it).total < v.total) {
                            // Check if already in closed with lower total
                            continue;
                        } else {
                            open.insert(v);
                            Q.push(v);
                            if (w_it != closed.end()) {
                                closed.erase(*w_it);
                            }
                        }
                    }
                }

                // Add u to closed list
                closed.insert(u);
            }

            // No solution found
            return nullptr;
        }

    };


}

#endif //SERVER_SIDE_PROJECT_ASTAR_H
