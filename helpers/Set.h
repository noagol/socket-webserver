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
    Set();

    void insert(Key key, Value value);

    bool exists(Key key);

    Value &find(Key key);

    void remove(Key key);

    bool empty();
};

/**
 * @tparam Key key to sort with
 * @tparam Value value to store
 */
template<class Key, class Value>
Set<Key, Value>::Set() : set() {}

/**
 * Insert to set
 * @tparam Key key to sort with
 * @tparam Value value to store
 */
template<class Key, class Value>
void Set<Key, Value>::insert(Key key, Value value) {
    set.insert(pair<Key, Value>(key, value));
}

/**
 * Check if exists in set
 * @tparam Key key to sort with
 * @tparam Value value to store
 */
template<class Key, class Value>
bool Set<Key, Value>::exists(Key key) {
    return (bool) set.count(key);
}

/**
 * Check if exists in set
 * @tparam Key key to sort with
 * @tparam Value value to store
 */
template<class Key, class Value>
Value &Set<Key, Value>::find(Key key) {
    return set.at(key);
}

/**
 * Remove from set
 * @tparam Key key to sort with
 * @tparam Value value to store
 */
template<class Key, class Value>
void Set<Key, Value>::remove(Key key) {
    set.erase(key);
}

/**
 * Check if set is empty
 * @tparam Key key to sort with
 * @tparam Value value to store
 */
template<class Key, class Value>
bool Set<Key, Value>::empty() {
    return set.empty();
}

#endif //SERVER_SIDE_PROJECT_SET_H
