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
        State<Position<int>> *goalState;
        State<Position<int>> *initialState;
        vector<vector<int>> matrix;
        vector<State<Position<int>> *> allocatedMemory;
    public:
        SearchableMatrix(vector<vector<int>> m) : matrix(m), allocatedMemory() {
            goalState = new State<Position<int>>(Position<int>(m.size() - 1, m.at(0).size() - 1),
                                                 m.at(m.size() - 1).at(m.at(0).size() - 1),
                                                 nullptr);
            initialState = new State<Position<int>>(Position<int>(0, 0),
                                                    m.at(0).at(0),
                                                    nullptr);
            allocatedMemory.push_back(goalState);
            allocatedMemory.push_back(initialState);
        }

        State<Position<int>> *getInitialState() override {
            return initialState;
        }

        bool isGoalState(State<Position<int>> *state) override {
            return state->getState().equals(goalState->getState());
        }

        vector<State<Position<int>> *> getAllPossibleStates(State<Position<int>> *current) override {
            Position<int> curr = current->getState();

            validatePosition(curr);

            bool canMoveUp = curr.getY() > 0;
            bool canMoveDown = curr.getY() < matrix.size() - 1;
            bool canMoveLeft = curr.getX() > 0;
            bool canMoveRight = curr.getX() < matrix.at(0).size() - 1;

            vector<State<Position<int>> *> states;
            State<Position<int>> *state;
//            if (canMoveUp) {
//                state = new State<Position<int>>(curr, matrix.at(curr.getY() - 1).at(curr.getX()), current);
//                states.push_back(state);
//                allocatedMemory.push_back(state);
//            }

            if (canMoveDown) {
                state = new State<Position<int>>(Position<int>(curr.getY() + 1, curr.getX()),
                                                 matrix.at(curr.getY() + 1).at(curr.getX()), current);
                states.push_back(state);
                allocatedMemory.push_back(state);
            }

//            if (canMoveLeft) {
//                state = new State<Position<int>>(curr, matrix.at(curr.getY()).at(curr.getX() - 1), current);
//                states.push_back(state);
//                allocatedMemory.push_back(state);
//            }

            if (canMoveRight) {
                state = new State<Position<int>>(Position<int>(curr.getY(), curr.getX() + 1),
                                                 matrix.at(curr.getY()).at(curr.getX() + 1), current);
                states.push_back(state);
                allocatedMemory.push_back(state);
            }

//            if (canMoveUp && canMoveLeft) {
//                state = new State<Position<int>>(curr, matrix.at(curr.getY() - 1).at(curr.getX() - 1), current);
//                states.push_back(state);
//                allocatedMemory.push_back(state);
//            }

//            if (canMoveUp && canMoveRight) {
//                state = new State<Position<int>>(curr, matrix.at(curr.getY() - 1).at(curr.getX() + 1), current);
//                states.push_back(state);
//                allocatedMemory.push_back(state);
//            }

//            if (canMoveDown && canMoveLeft) {
//                state = new State<Position<int>>(curr, matrix.at(curr.getY() + 1).at(curr.getX() - 1), current);
//                states.push_back(state);
//                allocatedMemory.push_back(state);
//            }

            if (canMoveDown && canMoveRight) {
                state = new State<Position<int>>(Position<int>(curr.getY() + 1, curr.getX() + 1),
                                                 matrix.at(curr.getY() + 1).at(curr.getX() + 1), current);
                states.push_back(state);
                allocatedMemory.push_back(state);
            }

            return states;
        }

        void validatePosition(Position<int> curr) {
            if (curr.getX() >= matrix.at(0).size() || curr.getY() >= matrix.size()) {
                throw runtime_error("Position is out of bounds");
            }
        }

        ~SearchableMatrix() {
            typename vector<State<Position<int>> *>::iterator it;
            for (it = allocatedMemory.begin(); it != allocatedMemory.end(); it++) {
                delete (*it);
            }
        }
    };
}

#endif //SERVER_SIDE_PROJECT_SEARCHABLEMATRIX_H
