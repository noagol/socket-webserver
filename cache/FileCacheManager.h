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
    map<string, Solution *> db;
    string filename;
    mutex lock;
public:
    FileCacheManager(string file_path);

    virtual void add(string &problem, Solution *solution);

    virtual void addToFile(string &problem, Solution *solution);

    virtual Solution *find(string &problemStr);

    virtual ~FileCacheManager();

private:
    void loadFromFile();
};


/**
 * Cache manager that saves to file
 * @tparam Solution solution type
 * @param file_path path to cache file
 */
template<class Solution>
FileCacheManager<Solution>::FileCacheManager(string file_path) : filename(file_path) {
    loadFromFile();
}

/**
 * Add problem and solution to cache
 * @tparam Solution solution type
 * @param problem key string
 * @param solution solution pointer
 */
template<class Solution>
void FileCacheManager<Solution>::add(string &problem, Solution *solution) {
    lock_guard<mutex> l(lock);
    db[problem] = solution;
    addToFile(problem, solution);
}

/**
 * Save new entry to file
 * @tparam Solution type
 */
template<class Solution>
void FileCacheManager<Solution>::addToFile(string &problem, Solution *solution) {
    // Open file
    ofstream outfile;
    outfile.open(filename, ios::app);

    // Check if file is opened well
    if (!outfile.is_open()) {
        throw runtime_error("Unable to open file");
    }

    // Write to file each entry
    outfile << problem << '\t' << *solution;

    // Close file
    outfile.close();
}

/**
 * Find a solution by a problem
 * @tparam Solution type
 * @param problemStr problem represented in a string
 * @return solution pointer. null if there is no solution in cache
 */
template<class Solution>
Solution *FileCacheManager<Solution>::find(string &problemStr) {
    lock_guard<mutex> l(lock);
    // Check in the maps
    if (db.find(problemStr) != db.end()) {
        return db[problemStr];
    } else {
        return nullptr;
    }
}

/**
 * Load from cache file
 * @tparam Solution
 */
template<class Solution>
void FileCacheManager<Solution>::loadFromFile() {
    // Not found on map
    // Open file
    ifstream infile(filename);
    if (!infile.good()) {
        return;
    }

    if (!infile.is_open()) {
        throw runtime_error("Unable to open file");
    }

    // Load from file until we find the customer
    string line;
    vector<string> spl;
    Solution *solution;

    // Read each line
    while (getline(infile, line)) {
        if (line.empty()) {
            continue;
        }
        // Read a line and split it
        spl = split(&line, '\t');
        // Not in map
        // add it
        istringstream is{spl.at(1)};
        solution = new Solution();
        is >> *solution;
        db[spl.at(0)] = solution;
    }

    // Close file
    infile.close();
}


/**
 * Save and free alocated memory
 * @tparam Solution type
 */
template<class Solution>
FileCacheManager<Solution>::~FileCacheManager() {
    for (auto &x : db) {
        delete (x.second);
    }
}

#endif //SERVER_SIDE_PROJECT_CACHEMANAGER_H
