//
// Created by EB on 04/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_CACHE_H
#define SERVER_SIDE_PROJECT_CACHE_H

#include <string>

using namespace std;

template<class Solution>
class CacheManager {
public:
    virtual void add(string &problem, Solution *solution) = 0;

    virtual Solution *find(string &problemStr) = 0;

    virtual ~CacheManager() {}
};


#endif //SERVER_SIDE_PROJECT_CACHE_H
