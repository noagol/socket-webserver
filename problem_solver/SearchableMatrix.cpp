#include "SearchableMatrix.h"

namespace problem_solver {

    /**
     * Constructs empty matrix
     */
    SearchableMatrix::SearchableMatrix() : matrix(), allocatedMemory() {
        goalState = new State<Position<int>>(Position<int>(0, 0), 0, nullptr);
        initialState = new State<Position<int>>(Position<int>(0, 0), 0, nullptr);
        allocatedMemory.push_back(goalState);
        allocatedMemory.push_back(initialState);
    }

    /**
     * Constructs searchable matrix object
     * @param m matrix
     */
    SearchableMatrix::SearchableMatrix(vector<vector<int>> *m) : matrix(*m), allocatedMemory() {
        goalState = new State<Position<int>>(Position<int>(m->at(0).size() - 1, m->size() - 1),
                                             m->at(m->size() - 1).at(m->at(0).size() - 1),
                                             nullptr);
        initialState = new State<Position<int>>(Position<int>(0, 0),
                                                m->at(0).at(0),
                                                nullptr);
        allocatedMemory.push_back(goalState);
        allocatedMemory.push_back(initialState);
        updateAverageWeight();
    }

    /**
     * Constructs searchable matrix object
     * @param m matrix
     * @param initialPos intial position
     * @param goalPos goal position
     */
    SearchableMatrix::SearchableMatrix(vector<vector<int>> *m, Position<int> &initialPos,
                                       Position<int> &goalPos) : matrix(*m),
                                                                 allocatedMemory() {

        if (m->size() == 0 || initialPos.getX() < 0 || initialPos.getY() < 0
            || goalPos.getX() >= m->at(0).size() || goalPos.getY() >= m->size()) {
            throw invalid_argument("Bad searchable matrix arguments given");
        }

        goalState = new State<Position<int>>(goalPos,
                                             m->at(goalPos.getY()).at(goalPos.getX()),
                                             nullptr);
        initialState = new State<Position<int>>(initialPos,
                                                m->at(initialPos.getY()).at(initialPos.getX()),
                                                nullptr);
        allocatedMemory.push_back(goalState);
        allocatedMemory.push_back(initialState);
        updateAverageWeight();
    }

    /**
     *
     * @return the matrix
     */
    vector<vector<int>> SearchableMatrix::getMatrix() const {
        return matrix;
    }

    /**
     *
     * @return the initial state
     */
    State<Position<int>> *SearchableMatrix::getInitialState() {
        return initialState;
    }

    /**
     *
     * @param state
     * @return estimate distance to goal
     */
    double SearchableMatrix::estimateDistanceToGoal(State<Position<int>> *state) {
        int x = abs(state->getState().getX() - goalState->getState().getX());
        int y = abs(state->getState().getY() - goalState->getState().getY());
        return (x + y) * (averageWeight / 2);
    }

    /**
     * Check if a state id the goal state
     * @param state to check
     * @return true if yhe state is the goal,
     * else return false
     * */
    bool SearchableMatrix::isGoalState(State<Position<int>> *state) {
        return state->getState().equals(goalState->getState());
    }

    /**
     *
     * @param current state
     * @return a vector of positions
     */
    vector<State<Position<int>> *> SearchableMatrix::getAllPossibleStates
            (State<Position<int>> *current) {
        Position<int> curr = current->getState();

        validatePosition(curr);

        // movement booleans
        bool canMoveUp = curr.getY() > 0;
        bool canMoveDown = curr.getY() < matrix.size() - 1;
        bool canMoveLeft = curr.getX() > 0;
        bool canMoveRight = curr.getX() < matrix.at(0).size() - 1;

        // Add to list all possible states
        vector<State<Position<int>> *> states;
        State<Position<int>> *state;
        if (canMoveUp && (matrix.at(curr.getY() - 1).at(curr.getX()) != -1)) {
            state = new State<Position<int>>(Position<int>(curr.getX(), curr.getY() - 1),
                                             matrix.at(curr.getY() - 1).at(curr.getX()), current);
            states.push_back(state);
            allocatedMemory.push_back(state);
        }

        if (canMoveDown && (matrix.at(curr.getY() + 1).at(curr.getX()) != -1)) {
            state = new State<Position<int>>(Position<int>(curr.getX(), curr.getY() + 1),
                                             matrix.at(curr.getY() + 1).at(curr.getX()), current);
            states.push_back(state);
            allocatedMemory.push_back(state);
        }

        if (canMoveLeft && (matrix.at(curr.getY()).at(curr.getX() - 1) != -1)) {
            state = new State<Position<int>>(Position<int>(curr.getX() - 1, curr.getY()),
                                             matrix.at(curr.getY()).at(curr.getX() - 1), current);
            states.push_back(state);
            allocatedMemory.push_back(state);
        }

        if (canMoveRight && (matrix.at(curr.getY()).at(curr.getX() + 1) != -1)) {
            state = new State<Position<int>>(Position<int>(curr.getX() + 1, curr.getY()),
                                             matrix.at(curr.getY()).at(curr.getX() + 1), current);
            states.push_back(state);
            allocatedMemory.push_back(state);
        }

        // Return possible states
        return states;
    }

    /**
     * Check if a current position isn't valid
     * @param curr validate position is in matrix
     */
    void SearchableMatrix::validatePosition(Position<int> curr) {
        if (curr.getX() >= matrix.at(0).size() || curr.getY() >= matrix.size()) {
            throw runtime_error("Position is out of bounds");
        }
    }

    /**
     * Prints object to stream
     * @param os stream
     * @param searchable object
     * @return os
     */
    ostream &operator<<(ostream &os, SearchableMatrix &searchable) {
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

        // Write initial and goal state
        Position<int> init = searchable.initialState->getState();
        Position<int> goal = searchable.goalState->getState();

        os << "^" << init << "|" << goal;

        return os;
    }

    /**
     * Loads object from stream
     * @param os stream
     * @param searchable matrix
     * @return os
     */
    istream &operator>>(istream &os, SearchableMatrix &searchable) {
        string input;
        os >> input;

        vector<string> rowsAndPositions = split(&input, '^');

        // Split
        vector<string> rows = split(&rowsAndPositions.at(0), '|');
        vector<string> positions = split(&rowsAndPositions.at(1), '|');

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

        // Set goal and initial states
        Position<int> initial;
        Position<int> goal;
        istringstream isInit{positions.at(0)};
        istringstream isGoal{positions.at(1)};
        isInit >> initial;
        isGoal >> goal;

        searchable.initialState = new State<Position<int>>(initial,
                                                           searchable.matrix.at(initial.getY()).at(initial.getX()),
                                                           nullptr);
        searchable.goalState = new State<Position<int>>(goal,
                                                        searchable.matrix.at(goal.getY()).at(goal.getX()),
                                                        nullptr);
        searchable.updateAverageWeight();

        // Add to allocated memory
        searchable.allocatedMemory.push_back(searchable.goalState);
        searchable.allocatedMemory.push_back(searchable.initialState);

        return os;
    }


    /**
     * free allocated memory
     */
    SearchableMatrix::~SearchableMatrix() {
        typename vector<State<Position<int>> *>::iterator it;
        for (it = allocatedMemory.begin(); it != allocatedMemory.end(); it++) {
            delete (*it);
        }
    }

    /**
     * Print object to stream
     * @param os stream
     */
    void SearchableMatrix::print(ostream &os) const {
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

    /**
     * Update the average weight
     */
    void SearchableMatrix::updateAverageWeight() {
        typename vector<vector<int>>::iterator it1;
        typename vector<int>::iterator it2;
        averageWeight = 0;
        int counter = 0;
        for (it1 = matrix.begin(); it1 != matrix.end(); it1++) {
            for (it2 = (*it1).begin(); it2 != (*it1).end(); it2++) {
                if (*it2 >= 0) {
                    averageWeight += *it2;
                    counter++;
                }
            }
        }

        averageWeight = averageWeight / counter;
    }
};
