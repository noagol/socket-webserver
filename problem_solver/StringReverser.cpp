#include "StringReverser.h"

namespace problem_solver {

    /**
     * Reverse a string
     * @param problem string
     * @return reverse string
     */
    string *StringReverser::solve(string *problem) {
        string *solution = new string();
        *solution = *problem;
        reverse(solution->begin(), solution->end());
        return solution;
    }


}
