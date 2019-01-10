
#ifndef SERVER_SIDE_PROJECT_BASESOLUTION_H
#define SERVER_SIDE_PROJECT_BASESOLUTION_H


#include "State.h"
#include "Solution.h"

namespace problem_solver {
    /**
     * Search solution to handle search problems
     * @tparam DataType int or double etc.
     */
    template<class StateType>
    class SearchSolution : public Solution<StateType> {
        vector<State < StateType> *>
        path;
        int totalCost;
    public:
        SearchSolution() : path(), totalCost(0), Solution<StateType>() {}

        SearchSolution(vector<State < StateType> *> p, int cost) :

        path (p), totalCost(cost) {}

        void addState(State <StateType> *state) {
            path.push_back(state);
        }

        virtual vector<State < StateType> *>

        getPath() const override {
            return path;
        }

        int getTotalCost() const override {
            return totalCost;
        }

        template<class V>
        friend ostream &operator<<(ostream &os, SearchSolution &solution) {
            vector<State<V>> solPath = solution.getPath();

            if (solPath.size() == 0) {
                os << -1;
            } else {
                typename vector<State<V>>::iterator it;
                for (it = solPath.begin(); it != (solPath.end() - 1); it++) {
                    os << *it << "|";
                }
                // Write last item
                os << *it;
            }

            os << endl;

            return os;
        }

        template<class V>
        friend istream &operator>>(istream &os, SearchSolution<V> &solution) {
            string input;
            os >> input;

            // Split
            vector<string> items = split(&input, '|');
            vector<string> item;

            State<StateType> *parent = nullptr;
            State<StateType> *state;
            int cost, totalCost = 0;
            StateType type;
            int i;

            // Write rows
            for (i = 0; i < items.size(); i++) {
                item = split(&items.at(i), '/');

                istringstream costStream{item.at(0)};
                costStream >> cost;
                totalCost += cost;


                istringstream stateStream{item.at(1)};
                stateStream >> type;

                state = new State<StateType>(type, cost, parent);
                solution.path.push_back(state);
                parent = state;
            }

            solution.totalCost = totalCost;

            return os;
        }

        ~SearchSolution() {
            typename vector<State<StateType> *>::iterator it;
            for (it = path.begin(); it != path.end(); it++) {
                delete (*it);
            }
        }

    protected:
        void print(ostream &os) const override {
            vector<State<StateType> *> solPath = getPath();
            typename vector<State<StateType> *>::iterator it;
            for (it = solPath.begin(); it != (solPath.end() - 1); it++) {
                os << **it << "|";
            }
            // Write last item
            os << **it;
        }

    };
}
#endif //SERVER_SIDE_PROJECT_BASESOLUTION_H
