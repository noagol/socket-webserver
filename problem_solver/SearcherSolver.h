//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SEARCHERSOLVER_H
#define SERVER_SIDE_PROJECT_SEARCHERSOLVER_H

#include "Solver.h"
#include "../algorithm/Searcher.h"

using namespace algorithms;

namespace problem_solver {
    template<class SearchableType,class StateType>
    class SearcherSolver : public Solver<Searchable<SearchableType>,Solution<StateType>> {
        Searcher<SearchableType> *searcher;
    public:
        SearcherSolver(Searcher<SearchableType> *s) : searcher(s) {}

        Solution<StateType> solve(Searchable<SearchableType> problem) override {
            return searcher->search(problem);
        }
    };
}

#endif //SERVER_SIDE_PROJECT_SEARCHERSOLVER_H
