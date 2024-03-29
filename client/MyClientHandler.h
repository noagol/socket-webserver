#ifndef SERVER_SIDE_PROJECT_MYCLIENTHANDLER_H
#define SERVER_SIDE_PROJECT_MYCLIENTHANDLER_H

#include "BaseClientHandler.h"
#include "../problem_solver/Solver.h"
#include "../cache/FileCacheManager.h"
#include <sys/socket.h>
#include "../problem_solver/SearchableMatrix.h"
#include "../helpers/StringHelpers.h"
#include "../problem_solver/SearchSolution.h"


using namespace problem_solver;
using namespace std;

namespace client_side {
    class MyClientHandler : public BaseClientHandler {
        Solver<Searchable<Position<int>>, SearchSolution<Position<int>>> *solver;
        FileCacheManager<SearchSolution<Position<int>>> cacheManager;
    public:
        MyClientHandler(Solver<Searchable<Position<int>>, SearchSolution<Position<int>>> *s);

        void handleClient(int inputSocket) override;

        Position<int> readPosition(string& position);

        string getPathMovements(SearchSolution<Position<int>> *solution);

        ~MyClientHandler();

    };
}

#endif //SERVER_SIDE_PROJECT_MYCLIENTHANDLER_H
