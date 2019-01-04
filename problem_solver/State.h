//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_STATE_H
#define SERVER_SIDE_PROJECT_STATE_H

#include <iostream>

using namespace std;

namespace problem_solver {
    template<class T>
    class State {
        T state;
        int cost;
        State<T> *parent;
    public:
        State() {}

        State(T currState, int moveCost, State<T> *lastState) :
                state(currState),
                cost(moveCost),
                parent(lastState) {}

        T getState() {
            return state;
        }

        int getCost() const{
            return cost;
        }

        State<T> *getParent() {
            return parent;
        }

        bool operator<(const State &right) {
            return this->getCost() < right.getCost();
        }

        bool operator==(State &right) {
            return state == right.getState();
        }
    };

    template<class T>
    struct CompareState : public binary_function<State<T> *, State<T> *, bool> {
        bool operator()(const State<T> *lhs, const State<T> *rhs) const {
            return lhs->getCost() > rhs->getCost();
        }
    };
}


#endif //SERVER_SIDE_PROJECT_STATE_H
