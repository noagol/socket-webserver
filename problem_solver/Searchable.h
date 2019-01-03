//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SEARCH_H
#define SERVER_SIDE_PROJECT_SEARCH_H

#include <vector>
#include "State.h"

using namespace std;

namespace problem_solver {
    template<class T>
    class Searchable {
    public:
        virtual State <T>* getInitialState() = 0;

        virtual bool isGoalState(State <T>* state) = 0;

        virtual vector<State<T>*> getAllPossibleStates(State<T>* state) = 0;
    };
}
#endif //SERVER_SIDE_PROJECT_SEARCH_H
