//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H
#define SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H

#include <set>
#include <queue>
#include "BaseSearcher.h"
#include <algorithm>
#include <Set.h>
#include "../helpers/PointerSet.h"

using namespace std;

namespace algorithms {
    template<class StateType>
    class BestFirstSearch : public BaseSearcher<StateType> {
    public:
        BestFirstSearch();

        class Vertex;

        struct CompareVertex;

        /**
        * Search using best first search in a searchable object
        * @param searchable searchable object
        * @return a solution for shortest path in the searchable
        */
        SearchSolution<StateType> *search(Searchable<StateType> *searchable) override;
    };
}
#endif //SERVER_SIDE_PROJECT_BESTFIRSTSEARCH_H
