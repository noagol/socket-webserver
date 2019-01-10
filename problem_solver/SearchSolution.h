
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
        SearchSolution();

        SearchSolution(vector<State < StateType> *

        > p,
        int cost
        );

        void addState(State <StateType> *state);

        vector<State < StateType>*>

        getPath() const;

        int getTotalCost() const override;

        template<class V>
        friend ostream &operator<<(ostream &os, SearchSolution &solution);

        template<class V>
        friend istream &operator>>(istream &os, SearchSolution<V> &solution);

        ~SearchSolution();

    protected:
        void print(ostream &os) const override;

    };

    /**
     * Search solution object
     * @tparam StateType
     */
    template<class StateType>
    SearchSolution<StateType>::SearchSolution() : path(), totalCost(0), Solution<StateType>() {}

    /**
     * Search solution object
     * @tparam StateType
     */
    template<class StateType>
    SearchSolution<StateType>::SearchSolution(vector<State < StateType> *

    > p,
    int cost
    ) :

    path (p), totalCost(cost) {}

    /**
     * Add a state to path
     * @tparam StateType
     * @param state state to add
     */
    template<class StateType>
    void SearchSolution<StateType>::addState(State <StateType> *state) {
        path.push_back(state);
    }

    /**
     * Get path of solution
     * @tparam StateType
     */
    template<class StateType>
    vector<State < StateType>*>

    SearchSolution<StateType>::getPath() const {
        return path;
    }

    /**
     * Get the total cost
     * @tparam StateType
     * @return total cost
     */
    template<class StateType>
    int SearchSolution<StateType>::getTotalCost() const {
        return totalCost;
    }

    /**
     * Print solution to stream
     */
    template<class V>
    ostream &operator<<(ostream &os, SearchSolution<V> &solution) {
        vector<State<V> *> solPath = solution.getPath();

        if (solPath.size() == 0) {
            os << -1;
        } else {
            typename vector<State<V> *>::iterator it;
            for (it = solPath.begin(); it != (solPath.end() - 1); it++) {
                os << **it << "|";
            }
            // Write last item
            os << **it;
        }

        os << endl;

        return os;
    }

    /**
     * Get solution from input
     */
    template<class StateType>
    istream &operator>>(istream &os, SearchSolution<StateType> &solution) {
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

        // Update total cost
        solution.totalCost = totalCost;

        return os;
    }

    /**
     * free allocated memory
     * @tparam StateType
     */
    template<class StateType>
    SearchSolution<StateType>::~SearchSolution() {
        typename vector<State<StateType> *>::iterator it;
        for (it = path.begin(); it != path.end(); it++) {
            delete (*it);
        }
    }

    /**
     * Print to stream
     */
    template<class StateType>
    void SearchSolution<StateType>::print(ostream &os) const {
        vector<State<StateType> *> solPath = getPath();
        typename vector<State<StateType> *>
        ::iterator it;
        for (it = solPath.begin(); it != (solPath.end() - 1); it++) {
            os << **it << "|";
        }
        // Write last item
        os << **it;
    }
}
#endif //SERVER_SIDE_PROJECT_BASESOLUTION_H
