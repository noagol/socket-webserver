//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BASESOLUTION_H
#define SERVER_SIDE_PROJECT_BASESOLUTION_H


#include "State.h"
#include "Solution.h"

namespace problem_solver {
    template<class T>
    class BaseSolution : public Solution<T> {
        list<State<T>> path;
        int totalCost;
    public:
        BaseSolution() : path(), totalCost(0), Solution<T>() {}

        BaseSolution(list<State<T>> p, int cost) : path(p), totalCost(cost) {}

        void addState(State<T> state) {
            path.push_back(state);
        }

        virtual list<State<T>> getPath() override {
            return path;
        }

        int getTotalCost() override {
            return totalCost;
        }

    };
}
#endif //SERVER_SIDE_PROJECT_BASESOLUTION_H
