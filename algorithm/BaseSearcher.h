//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BASESEARCHER_H
#define SERVER_SIDE_PROJECT_BASESEARCHER_H

#include "Searcher.h"
#include "SearchSolution.h"

namespace algorithms {

    template<class T>
    class BaseSearcher : public Searcher<T> {
    public:
        BaseSearcher() {}

    };
}

#endif //SERVER_SIDE_PROJECT_BASESEARCHER_H
