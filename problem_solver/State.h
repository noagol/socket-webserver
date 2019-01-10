
#ifndef SERVER_SIDE_PROJECT_STATE_H
#define SERVER_SIDE_PROJECT_STATE_H

#include <iostream>
#include "../helpers/StringHelpers.h"

using namespace std;

namespace problem_solver {
    template<class T>
    class State {
        T state;
        int cost;
        State<T> *parent;
    public:
        State();

        State(T currState, int moveCost, State<T> *lastState);

        T getState();

        void setParent(State<T> *state);

        int getCost() const;

        State<T> *getParent();

        bool operator<(const State &right);

        bool operator==(State &right);

        template<class V>
        friend ostream &operator<<(ostream &os, State<V> &st);

        template<class V>
        friend istream &operator>>(istream &os, State<V> &st);
    };

    // Comparator
    template<class T>
    struct CompareState : public binary_function<State<T> *, State<T> *, bool> {
        bool operator()(const State<T> *lhs, const State<T> *rhs) const {
            return lhs->getCost() > rhs->getCost();
        }
    };

    template<class T>
    struct StateComparator : public binary_function<State<T>, State<T>, bool> {
        bool operator()(const State<T> &lhs, const State<T> &rhs) const {
            return lhs.getState() < rhs.getState();
        }
    };

    template<class T>
    State<T>::State() {}

    template<class T>
    State<T>::State(T currState, int moveCost, State<T> *lastState) :
            state(currState),
            cost(moveCost),
            parent(lastState) {}

    template<class T>
    T State<T>::getState() {
        return state;
    }

    template<class T>
    void State<T>::setParent(State<T> *state) {
        parent = state;
    }

    template<class T>
    int State<T>::getCost() const {
        return cost;
    }

    template<class T>
    State<T> *State<T>::getParent() {
        return parent;
    }

    template<class T>
    bool State<T>::operator<(const State &right) {
        return this->state < right.state;
    }

    template<class T>
    bool State<T>::operator==(State &right) {
        return state == right.getState();
    }

    template<class T>
    ostream &operator<<(ostream &os, State<T> &st) {
        os << st.cost << "/" << st.state;
        return os;
    }

    template<class T>
    istream &operator>>(istream &os, State<T> &st) {
        string input;
        os >> input;

        // Split
        vector<string> spl = split(&input,
                                   '/');

        // Turn to streams
        istringstream c{spl.at(0)};
        istringstream s{spl.at(1)};

        // Write to object
        c >> st.cost;
        s >> st.state;

        return os;
    }
}


#endif //SERVER_SIDE_PROJECT_STATE_H
