//
// Created by noa on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SEARCHABLEMATRIX_H
#define SERVER_SIDE_PROJECT_SEARCHABLEMATRIX_H

#include <vector>
#include <stdexcept>
#include <cmath>
#include "Searchable.h"
#include "../helpers/Position.h"

namespace problem_solver {
    class SearchableMatrix : public Searchable<Position<int>> {
        State <Position<int>> *goalState;
        State <Position<int>> *initialState;
        vector<vector<int>> matrix;
        vector<State < Position<int>> *>
        allocatedMemory;
    public:
        SearchableMatrix() : matrix(), allocatedMemory() {
            goalState = new State<Position<int>>(Position<int>(0, 0),
                                                 0,
                                                 nullptr);
            initialState = new State<Position<int>>(Position<int>(0, 0),
                                                    0,
                                                    nullptr);
            allocatedMemory.push_back(goalState);
            allocatedMemory.push_back(initialState);
        }

        SearchableMatrix(vector<vector<int>> m) : matrix(m), allocatedMemory() {
            goalState = new State<Position<int>>(Position<int>(m.at(0).size() - 1, m.size() - 1),
                                                 m.at(m.size() - 1).at(m.at(0).size() - 1),
                                                 nullptr);
            initialState = new State<Position<int>>(Position<int>(0, 0),
                                                    m.at(0).at(0),
                                                    nullptr);
            allocatedMemory.push_back(goalState);
            allocatedMemory.push_back(initialState);
        }

        vector<vector<int>> getMatrix() const {
            return matrix;
        }

        State <Position<int>> *getInitialState() override {
            return initialState;
        }

        double estimateDistanceToGoal(State <Position<int>> *state) override {
            double x = abs((state->getState().getX() - goalState->getState().getX()) * 2);
            double y = abs((state->getState().getY() - goalState->getState().getY()) * 2);
            return sqrt(x + y);
        }

        bool isGoalState(State <Position<int>> *state) override {
            return state->getState().equals(goalState->getState());
        }

        vector<State < Position<int>> *>
        getAllPossibleStates(State<Position<int>>
        *current) override {
            Position<int> curr = current->getState();

            validatePosition(curr);

            bool canMoveUp = curr.getY() > 0;
            bool canMoveDown = curr.getY() < matrix.size() - 1;
            bool canMoveLeft = curr.getX() > 0;
            bool canMoveRight = curr.getX() < matrix.at(0).size() - 1;

            vector<State < Position<int>> *> states;
            State < Position<int>> *state;
            if (canMoveUp) {
                state = new State <Position<int>>(Position<int>(curr.getX(), curr.getY() - 1),
                        matrix.at(curr.getY() - 1).at(curr.getX()), current);
                states.push_back(state);
                allocatedMemory.push_back(state);
            }

            if (canMoveDown) {
                state = new State <Position<int>>(Position<int>(curr.getX(), curr.getY() + 1),
                                                  matrix.at(curr.getY() + 1).at(curr.getX()), current);
                states.push_back(state);
                allocatedMemory.push_back(state);
            }

            if (canMoveLeft) {
                state = new State <Position<int>>(Position<int>(curr.getX() - 1, curr.getY()),
                        matrix.at(curr.getY()).at(curr.getX() - 1), current);
                states.push_back(state);
                allocatedMemory.push_back(state);
            }

            if (canMoveRight) {
                state = new State <Position<int>>(Position<int>(curr.getX() + 1, curr.getY()),
                                                  matrix.at(curr.getY()).at(curr.getX() + 1), current);
                states.push_back(state);
                allocatedMemory.push_back(state);
            }

            if (canMoveUp && canMoveLeft) {
                state = new State <Position<int>>(Position<int>(curr.getX() - 1, curr.getY() - 1),
                        matrix.at(curr.getY() - 1).at(curr.getX() - 1), current);
                states.push_back(state);
                allocatedMemory.push_back(state);
            }

            if (canMoveUp && canMoveRight) {
                state = new State <Position<int>>(Position<int>( curr.getX() + 1, curr.getY() - 1),
                        matrix.at(curr.getY() - 1).at(curr.getX() + 1), current);
                states.push_back(state);
                allocatedMemory.push_back(state);
            }

            if (canMoveDown && canMoveLeft) {
                state = new State <Position<int>>(Position<int>(curr.getX() - 1, curr.getY() + 1),
                        matrix.at(curr.getY() + 1).at(curr.getX() - 1), current);
                states.push_back(state);
                allocatedMemory.push_back(state);
            }

            if (canMoveDown && canMoveRight) {
                state = new State <Position<int>>(Position<int>(curr.getX() + 1, curr.getY() + 1),
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

        friend ostream &operator<<(ostream &os, SearchableMatrix &searchable) {
            typename vector<vector<int>>::iterator it1;
            typename vector<int>::iterator it2;

            // Write rows
            for (it1 = searchable.matrix.begin(); it1 != searchable.matrix.end() - 1; it1++) {
                for (it2 = (*it1).begin(); it2 != ((*it1).end() - 1); it2++) {
                    os << *it2 << ",";
                }
                os << *it2 << "|";
            }

            // Write last row
            for (it2 = (*it1).begin(); it2 != ((*it1).end() - 1); it2++) {
                os << *it2 << ",";
            }
            os << *it2;

            return os;
        }

        friend istream &operator>>(istream &os, SearchableMatrix &searchable) {
            string input;
            os >> input;

            // Split
            vector<string> rows = split(&input, '|');
            vector<string> row;
            string rowStr;

            int i, j;

            // Write rows
            for (i = 0; i < rows.size(); i++) {
                row = split(&rows.at(i), ',');
                searchable.matrix.push_back(vector<int>());

                for (j = 0; j < row.size(); j++) {
                    searchable.matrix.at(i).push_back(stoi(row.at(j)));
                }
            }

            searchable.goalState = new State<Position<int>>(
                    Position<int>(searchable.matrix.at(0).size() - 1, searchable.matrix.size() - 1),
                    searchable.matrix.at(searchable.matrix.size() - 1).at(searchable.matrix.at(0).size() - 1),
                    nullptr);
            searchable.initialState = new State<Position<int>>(Position<int>(0, 0),
                                                               searchable.matrix.at(0).at(0),
                                                               nullptr);
            searchable.allocatedMemory.push_back(searchable.goalState);
            searchable.allocatedMemory.push_back(searchable.initialState);

            return os;
        }


        ~SearchableMatrix() {
            typename vector<State<Position<int>> *>::iterator it;
            for (it = allocatedMemory.begin(); it != allocatedMemory.end(); it++) {
                delete (*it);
            }
        }

    protected:
        void print(ostream &os) const override {
            typename vector<vector<int>>::iterator it1;
            typename vector<int>::iterator it2;

            vector<vector<int>> m = getMatrix();

            // Write rows
            for (it1 = m.begin(); it1 != m.end() - 1; it1++) {
                for (it2 = (*it1).begin(); it2 != ((*it1).end() - 1); it2++) {
                    os << *it2 << ",";
                }
                os << *it2 << "|";
            }

            // Write last row
            for (it2 = (*it1).begin(); it2 != ((*it1).end() - 1); it2++) {
                os << *it2 << ",";
            }
            os << *it2;
        }

    };
}

#endif //SERVER_SIDE_PROJECT_SEARCHABLEMATRIX_H
