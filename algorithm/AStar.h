//
// Created by EB on 05/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_ASTAR_H
#define SERVER_SIDE_PROJECT_ASTAR_H

#include "BaseSearcher.h"
#include <map>
#include <queue>
#include <Set.h>

namespace algorithms {
    template<class StateType>
    class AStar : public BaseSearcher<StateType> {

    public:
        /**
         * Implements A Star algorithm
         */
        AStar();

        /**
         * A class to hold vertex data
         */
        class Vertex;

        /**
         * Vertex comparator
         */
        struct CompareVertex;

        /**
        * Search using a star in a searchable object
        * @param searchable searchable object
        * @return a solution for shortest path in the searchable
        */
        SearchSolution<StateType> *search(Searchable<StateType> *searchable) override;
    };


}

#endif //SERVER_SIDE_PROJECT_ASTAR_H
