//
// Created by noa on 03/01/2019.
//

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
        vector<State<StateType>> path;
        int totalCost;
    public:

//        Solution(string &input) {
//            vector<string> spl = split(&input, '|');
//            int totalCost = 0;
//            int i;
//            for (i = 0; i < spl.size(); i++) {
//                totalCost += stoi(spl.at(i));
//                addState(State<T>(T(1, 1)));
//            }
//        }

        SearchSolution() : path(), totalCost(0), Solution<StateType>() {}

        SearchSolution(vector<State<StateType>> p, int cost) : path(p), totalCost(cost) {}

        void addState(State<StateType> state) {
            path.push_back(state);
        }

        virtual vector<State<StateType> > getPath() override {
            return path;
        }

        int getTotalCost() override {
            return totalCost;
        }

        friend ostream &operator<<(ostream &os, Solution<StateType> &solution) {
            vector<State<StateType>> solPath = solution.getPath();
            typename vector<State<StateType>>::iterator it;
            for (it = solPath.begin(); it != solPath.end(); it++) {
                os << (*it).getCost() << "|";
            }
            os << endl;

            return os;
        }

    };
}
#endif //SERVER_SIDE_PROJECT_BASESOLUTION_H
