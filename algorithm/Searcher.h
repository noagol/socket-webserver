//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_ALGORITHM_H
#define SERVER_SIDE_PROJECT_ALGORITHM_H

#include <SearchSolution.h>
#include "../problem_solver/Solution.h"
#include "../problem_solver/Searchable.h"

using namespace problem_solver;

namespace algorithms {
    template<class T>
    class Searcher {
    public:
        virtual SearchSolution<T> *search(Searchable<T> *searchable) = 0;

        virtual int getCount() = 0;
    };
}

#endif //SERVER_SIDE_PROJECT_ALGORITHM_H
