
#ifndef SERVER_SIDE_PROJECT_SEARCHABLEMATRIX_H
#define SERVER_SIDE_PROJECT_SEARCHABLEMATRIX_H

#include <vector>
#include <stdexcept>
#include <cmath>
#include "Searchable.h"
#include "../helpers/Position.h"

namespace problem_solver {
    class SearchableMatrix : public Searchable<Position<int>> {
        State<Position<int>> *goalState;
        State<Position<int>> *initialState;
        vector<vector<int>> matrix;
        vector<State<Position<int>> *> allocatedMemory;
        int averageWeight = 0;
    public:
        SearchableMatrix() ;

        SearchableMatrix(vector<vector<int>> *m) ;

        SearchableMatrix(vector<vector<int>> *m, Position<int> &initialPos,
                         Position<int> &goalPos) ;


        vector<vector<int>> getMatrix() const ;

        State<Position<int>> *getInitialState() override ;

        double estimateDistanceToGoal(State<Position<int>> *state) override;

        bool isGoalState(State<Position<int>> *state) override ;

        vector<State<Position<int>> *> getAllPossibleStates(State<Position<int>> *current) override ;

        void validatePosition(Position<int> curr);

        friend ostream &operator<<(ostream &os, SearchableMatrix &searchable) ;

        friend istream &operator>>(istream &os, SearchableMatrix &searchable) ;

        ~SearchableMatrix() ;

    protected:
        void print(ostream &os) const override ;

    private:
        void updateAverageWeight() ;
    };
}

#endif //SERVER_SIDE_PROJECT_SEARCHABLEMATRIX_H
