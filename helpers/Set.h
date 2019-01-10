//
// Created by EB on 06/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_SET_H
#define SERVER_SIDE_PROJECT_SET_H


#include <unordered_map>

using namespace std;

template<class Key, class Value>
class Set {
    unordered_map<Key, Value> set;
public:
    Set() : set() {}

    void insert(Key key, Value value) {
        set.insert(pair<Key, Value>(key, value));
    }

    bool exists(Key key) {
        return (bool) set.count(key);
    }

    Value& find(Key key) {
        return set.at(key);
    }

    void remove(Key key) {
        set.erase(key);
    }

    bool empty() {
        return set.empty();
    }
};


#endif //SERVER_SIDE_PROJECT_SET_H
