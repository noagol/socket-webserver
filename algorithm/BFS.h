//
// Created by EB on 04/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_BFS_H
#define SERVER_SIDE_PROJECT_BFS_H

#include <set>
#include <queue>
#include "BaseSearcher.h"
#include <algorithm>
#include "../helpers/PointerSet.h"
#include <map>
#include <Vertex.h>

using namespace std;

namespace algorithms {
    template<class StateType>
    class BestFirstSearch : public BaseSearcher<StateType> {
    public:
        BestFirstSearch() : BaseSearcher<StateType>() {}

        Solution<StateType> *search(Searchable<StateType> *searchable) override {
            queue<State<StateType> *> Q;
            map<State<StateType> *, int> d;

            Vertex<State<StateType>> initial = searchable->getInitialState();
            Q.push(initial);
            d[initial.getPtr()] = 0;
            initial.setColor(GRAY);

            Vertex<State<StateType>> u, v;

            vector<State<StateType> *> adj;
            typename vector<State<StateType> *>::iterator it;

            while (!Q.empty()) {
                u = Q.front();
                Q.pop();

                adj = searchable->getAllPossibleStates(u.getPtr());

                for (it = adj.begin(); it != adj.end(); it++) {
//                    v = Vertex()
                }
            }


        }

    };
};
#endif //SERVER_SIDE_PROJECT_BFS_H
