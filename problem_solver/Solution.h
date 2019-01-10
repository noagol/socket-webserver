//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SOLUTION_H
#define SERVER_SIDE_PROJECT_SOLUTION_H

#include <list>
#include "State.h"
#include "string"
#include "ostream"
#include "vector"
#include "../helpers/StringHelpers.h"

using namespace std;

namespace problem_solver {
    template<class T>
    class Solution {
    public:
        virtual vector<State<T>*> getPath() const = 0;

        virtual int getTotalCost() const = 0;

        template<class V>
        friend ostream &operator<<(ostream &os, const Solution<V> &solution) {
            solution.print(os); // delegate the work to a polymorphic member function.
            return os;
        }

        virtual ~Solution() {}

    protected:
        virtual void print(ostream &o) const = 0;
    };

    template<class V>
    ostream &operator<<(ostream &os, const Solution<V> &solution) {
        solution.print(os); // delegate the work to a polymorphic member function.
        return os;
    }
}

#endif //SERVER_SIDE_PROJECT_SOLUTION_H
