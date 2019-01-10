#include "AStar.h"

namespace algorithms {
    /**
     * Implements A Star algorithm
     */
    template<class StateType>
    AStar<StateType>::AStar() {}

    /**
     * A class to hold vertex data
     */
    template<class StateType>
    class AStar<StateType>::Vertex {
    public:
        State<StateType> *state;
        double total, dFromStart, estimatedToEnd;

        Vertex() {}

        /**
         * Construcs a vertex
         * @param s state pointer
         * @param t total value (d+e)
         * @param d distance from initial
         * @param e estimated distance to end
         */
        Vertex(State<StateType> *s, double t, double d, double e) : state(s), total(t), dFromStart(d),
                                                                    estimatedToEnd(e) {}

        /**
         * Compares two vertices by their state
         * @param right other vertex
         * @return true if left < right
         */
        bool operator<(const Vertex &right) const {
            return *(this->state) < *(right.state);
        }

        /**
         * Compares two vertecies by their state
         * @param right other vertex
         * @return true if left = right
         */
        bool operator==(const Vertex &right) const {
            return *(this->state) == *(right.state);
        }
    };

    /**
     * Vertex comparator
     */
    template<class StateType>
    struct AStar<StateType>::CompareVertex : public binary_function<Vertex, Vertex, bool> {
        bool operator()(const Vertex lhs, const Vertex rhs) const {
            return lhs.total > rhs.total;
        }
    };

    /**
    * Search using a star in a searchable object
    * @param searchable searchable object
    * @return a solution for shortest path in the searchable
    */
    template<class StateType>
    SearchSolution<StateType> *AStar<StateType>::search(Searchable<StateType> *searchable) {
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
                v.estimatedToEnd = searchable->estimateDistanceToGoal(*it);
                v.total = v.dFromStart + v.estimatedToEnd;

                // Search in open
                if (!open.exists(v.state->getState())) {
                    // Not in open and not in closed
                    open.insert(v.state->getState(), v);
                    Q.push(v);
                } else if (open.find(v.state->getState()).dFromStart > v.dFromStart) {
                    // The vertex is found in open with better values
                    open.insert(v.state->getState(), v);
                    Q.push(v);
                }
            }

        }

        // No solution found
        return nullptr;
    }
}