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
#include "../helpers/StringHelpers.h"
#include "CacheManager.h"
#include <mutex>

using namespace std;

/**
 * A database to hold data of an object
 * @tparam T a given object
 */
template<class Solution>
class FileCacheManager : public CacheManager<Solution> {
protected:
    map<string, Solution *> dbOld;
    map<string, Solution *> dbNew;
    string filename;
    mutex lock;
public:
    FileCacheManager(string file_path);

    virtual void add(string &problem, Solution *solution);

    virtual void save();

    virtual Solution *find(string &problemStr);

    virtual ~FileCacheManager();
};


template<class Solution>
FileCacheManager<Solution>::FileCacheManager(string file_path) : filename(file_path) {}

template<class Solution>
void FileCacheManager<Solution>::add(string &problem, Solution *solution) {
    lock_guard<mutex> l(lock);
    dbNew[problem] = solution;
}

template<class Solution>
void FileCacheManager<Solution>::save() {
    // Open file
    ofstream outfile;
    outfile.open(filename, ios::app);

    if (!outfile.is_open()) {
        throw runtime_error("Unable to open file");
    }

    for (auto const &x : dbNew) {
        outfile << x.first << '\t' << *x.second << endl;
    }

    outfile.close();
}

template<class Solution>
Solution *FileCacheManager<Solution>::find(string &problemStr) {
    lock_guard<mutex> l(lock);
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
        if (line.empty()) {
            continue;
        }
        // Read a line and split it
        spl = split(&line, '\t');
        if (dbOld.find(spl.at(0)) == dbOld.end()) {
            // Not in map
            // add it
            istringstream is{spl.at(1)};
            solution = new Solution();
            is >> *solution;
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


template<class Solution>
FileCacheManager<Solution>::~FileCacheManager() {
    save();

    for (auto &x : dbOld) {
        delete (x.second);
    }
    for (auto const &x : dbNew) {
        delete (x.second);
    }
}

#endif //SERVER_SIDE_PROJECT_CACHEMANAGER_H
