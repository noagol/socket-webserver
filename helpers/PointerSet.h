//
// Created by EB on 03/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_POINTERSSET_H
#define SERVER_SIDE_PROJECT_POINTERSSET_H

#include "set"

using namespace std;

template<class T>
class PointerSet {
    set<T *> s;
public:
    void add(T *t) {
        s.insert(t);
    }

    bool exists(T *item) {
        typename set<T *>::iterator it;
        for (it = s.begin(); it != s.end(); it++) {
            if (**it == *item) {
                return true;
            }
        }

        return false;
    }

    void remove(T *item) {
        s.erase(item);
    }

};

#endif //SERVER_SIDE_PROJECT_POINTERSSET_H
