//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SEARCHABLEMATRIX_H
#define SERVER_SIDE_PROJECT_SEARCHABLEMATRIX_H

#include <vector>
#include <stdexcept>
#include "Searchable.h"
#include "../helpers/Position.h"

namespace problem_solver {
    class SearchableMatrix : public Searchable<Position<int>> {
        Position<int> goalState;
        Position<int> initialState;
        vector<vector<int>> matrix;
    public:
        SearchableMatrix(vector<vector<int>> m) : matrix(m) {
            goalState = Position<int>(m.size() - 1, m.at(0).size() - 1);
            initialState = Position<int>(0, 0);
        }

        State<Position<int>> getInitialState() override {
            return State<Position<int>>(initialState, matrix.at(initialState.getY()).at(initialState.getX()));
        }

        bool isGoalState(State<Position<int>> state) override {
            return state.getState().equals(goalState);
        }

        vector<State<Position<int>>> getAllPossibleStates(State<Position<int>> current) override {
            Position<int> curr = current.getState();

            validatePosition(curr);

            bool canMoveUp = curr.getY() > 0;
            bool canMoveDown = curr.getY() < matrix.size() - 1;
            bool canMoveLeft = curr.getX() > 0;
            bool canMoveRight = curr.getX() < matrix.at(0).size() - 1;

            vector<State<Position<int>>> states;

            if (canMoveUp) {
                states.push_back(State<Position<int>>(curr, matrix.at(curr.getY() - 1).at(curr.getX()), current));
            }

            if (canMoveDown) {
                states.push_back(State<Position<int>>(curr, matrix.at(curr.getY() + 1).at(curr.getX()), current));
            }

            if (canMoveLeft) {
                states.push_back(State<Position<int>>(curr, matrix.at(curr.getY()).at(curr.getX() - 1), current));
            }

            if (canMoveRight) {
                states.push_back(State<Position<int>>(curr, matrix.at(curr.getY()).at(curr.getX() + 1), current));
            }

            if (canMoveUp && canMoveLeft) {
                states.push_back(State<Position<int>>(curr, matrix.at(curr.getY() - 1).at(curr.getX() - 1), current));
            }

            if (canMoveUp && canMoveRight) {
                states.push_back(State<Position<int>>(curr, matrix.at(curr.getY() - 1).at(curr.getX() + 1), current));
            }

            if (canMoveDown && canMoveLeft) {
                states.push_back(State<Position<int>>(curr, matrix.at(curr.getY() + 1).at(curr.getX() - 1), current));
            }

            if (canMoveDown && canMoveRight) {
                states.push_back(State<Position<int>>(curr, matrix.at(curr.getY() + 1).at(curr.getX() + 1), current));
            }

        }

        void validatePosition(Position<int> curr) {
            if (curr.getX() >= matrix.at(0).size() || curr.getY() >= matrix.size()) {
                throw runtime_error("Position is out of bounds");
            }
        }
    };
}

#endif //SERVER_SIDE_PROJECT_SEARCHABLEMATRIX_H
