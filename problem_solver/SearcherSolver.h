#ifndef SERVER_SIDE_PROJECT_SEARCHERSOLVER_H
#define SERVER_SIDE_PROJECT_SEARCHERSOLVER_H

#include "Solver.h"
#include "../algorithm/Searcher.h"
#include "SearchSolution.h"

using namespace algorithms;

namespace problem_solver {

    template<class StateType>
    class SearcherSolver : public Solver<Searchable<StateType>, SearchSolution<StateType>> {
        Searcher<StateType> *searcher;
    public:
        SearcherSolver(Searcher<StateType> *s);

        SearchSolution<StateType> *solve(Searchable<StateType> *problem) override;

        ~SearcherSolver();
    };

    template<class StateType>
    SearcherSolver<StateType>::SearcherSolver(Searcher<StateType> *s) : searcher(s) {}

    /**
     *
     * @param problem
     * @return
     */
    template<class StateType>
    SearchSolution<StateType> *SearcherSolver<StateType>::solve(Searchable<StateType> *problem) {
        return searcher->search(problem);
    }

    template<class StateType>
    SearcherSolver<StateType>::~SearcherSolver() {
        delete (searcher);
    }
}

#endif //SERVER_SIDE_PROJECT_SEARCHERSOLVER_H
