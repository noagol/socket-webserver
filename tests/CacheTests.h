//
// Created by EB on 04/01/2019.
//

#ifndef SERVER_SIDE_PROJECT_CACHETESTS_H
#define SERVER_SIDE_PROJECT_CACHETESTS_H

#include "../cache/FileCacheManager.h"

class CacheTests {
    static void simpleTask() {
        FileCacheManager<string> cm = FileCacheManager<string>("test.txt");
        string a = "elad";
        string *b = new string("test");

        cm.add(a, b);

        string *search = cm.find(a);

        cout << *search << endl;
    }
};

#endif //SERVER_SIDE_PROJECT_CACHETESTS_H
