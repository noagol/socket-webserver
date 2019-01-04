//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SEARCHERSOLVER_H
#define SERVER_SIDE_PROJECT_SEARCHERSOLVER_H

#include "Solver.h"
#include "../algorithm/Searcher.h"

using namespace algorithms;

namespace problem_solver {
    template<class StateType>
    class SearcherSolver : public Solver<Searchable<StateType>, Solution<StateType>> {
        Searcher<StateType> *searcher;
    public:
        SearcherSolver(Searcher<StateType> *s) : searcher(s) {}

        Solution<StateType> *solve(Searchable<StateType> *problem) override {
            return searcher->search(problem);
        }

        ~SearcherSolver() {
            delete (searcher);
        }
    };
}

#endif //SERVER_SIDE_PROJECT_SEARCHERSOLVER_H
