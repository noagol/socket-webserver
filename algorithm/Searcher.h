//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_ALGORITHM_H
#define SERVER_SIDE_PROJECT_ALGORITHM_H

#include "../problem_solver/SearchSolution.h"
#include "../problem_solver/Solution.h"
#include "../problem_solver/Searchable.h"

using namespace problem_solver;

namespace algorithms {
    template<class T>
    class Searcher {
    public:
        /**
        * Search using a search algorithm in a searchable object
        * @param searchable searchable object
        * @return a solution for shortest path in the searchable
        */
        virtual SearchSolution<T> *search(Searchable<T> *searchable) = 0;

        /**
         * Get count of verticies visited in the algorithms last run
         * @return the count
         */
        virtual int getCount() = 0;
    };
}

#endif //SERVER_SIDE_PROJECT_ALGORITHM_H
