//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_STATE_H
#define SERVER_SIDE_PROJECT_STATE_H

namespace problem_solver {
    template<class T>
    class State {
        T state;
        int cost;
        State<T> parent;
        bool hasParent;
    public:
        State() {}

        State(T currState, int moveCost) :
                state(currState),
                cost(moveCost),
                hasParent(false) {}

        State(T currState, int moveCost, State<T> lastState) :
                state(currState),
                cost(moveCost),
                parent(lastState),
                hasParent(true) {}

        T getState() {
            return state;
        }

        int getCost() {
            return cost;
        }

        State<T> getParent() {
            return parent;
        }

        bool doesHaveParent() {
            return hasParent;
        }

        bool operator<(const State &right) {
            return this->getCost() < right.getCost();
        }

        bool operator==(const State &right) {
            return this->getState() == right.getState();
        }
    };
}

#endif //SERVER_SIDE_PROJECT_STATE_H
