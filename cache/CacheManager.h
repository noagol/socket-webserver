//
// Created by EB on 04/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_CACHEMANAGER_H
#define SERVER_SIDE_PROJECT_CACHEMANAGER_H

#include <string>
#include <map>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <StringHelpers.h>

using namespace std;

/**
 * A database to hold data of an object
 * @tparam T a given object
 */
template<class Problem, class Solution>
class CacheManager {
protected:
    map<string, Solution *> dbOld;
    map<string, Solution *> dbNew;
    string filename;
public:
    CacheManager(string file_path);

    virtual void add(Problem *p, Solution *s);

    virtual void save();

    virtual Solution *find(Problem *problem);

    virtual ~CacheManager();
};


template<class Problem, class Solution>
CacheManager<Problem, Solution>::CacheManager(string file_path) : filename(file_path) {}

template<class Problem, class Solution>
void CacheManager<Problem, Solution>::add(Problem *p, Solution *s) {
    ostringstream problem;
    problem << p;

    dbNew[problem.str()] = s;
}

template<class Problem, class Solution>
void CacheManager<Problem, Solution>::save() {
    // Open file
    ofstream outfile;
    outfile.open(filename, ios::app);

    if (!outfile.is_open()) {
        throw runtime_error("Unable to open file");
    }

    for (auto const &x : dbNew) {
        outfile << *x.second;
    }

    outfile.close();
}

template<class Problem, class Solution>
Solution *CacheManager<Problem, Solution>::find(Problem *problem) {
    ostringstream p;
    p << problem;
    string problemStr = p.str();

    // Check in the maps
    if (dbNew.find(problemStr) != dbNew.end()) {
        return dbNew[problemStr];
    } else if (dbOld.find(problemStr) != dbOld.end()) {
        return dbOld[problemStr];
    }

    // Not found on map
    // Open file
    ifstream infile(filename);
    if (!infile.good()) {
        return nullptr;
    }
    if (!infile.is_open()) {
        throw runtime_error("Unable to open file");
    }

    // Load from file until we find the customer
    string line;
    vector<string> spl;
    Solution *solution;

    while (getline(infile, line)) {
        // Read a line and split it
        spl = split(&line, '\t');
        if (dbOld.find(spl.at(0)) == dbOld.end()) {
            // Not in map
            // add it
            solution >> spl.at(1);
            dbOld[problemStr] = solution;
            if (spl.at(0) == problemStr) {
                // We found the solution from the file
                infile.close();
                return solution;
            }
        } else if (spl.at(0) == problemStr) {
            // Found on database
            infile.close();
            return dbOld[spl.at(0)];
        }
    }

    infile.close();
    // Customer no found
    return nullptr;
}


template<class Problem, class Solution>
CacheManager<Problem, Solution>::~CacheManager() {
    for (auto &x : dbOld) {
        delete (x.second);
    }
    for (auto const &x : dbNew) {
        delete (x.second);
    }
}

#endif //SERVER_SIDE_PROJECT_CACHEMANAGER_H
