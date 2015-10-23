#ifndef READ_SQL_H_
#define READ_SQL_H_

#include <mysql++.h>
#include <vector>
#include <iostream>
#include "Graph.h"
#include "AdjacencyList.h"
#include "readsql.h"

using namespace std;
using namespace mysqlpp;

class eSQL{
public:
    eSQL();

    bool readGraph(Graph&, int&, int&);
    bool readStation(int, string&);
    bool readRoute(string, int&);
    bool readLink(int, int, string&, string, int&);
    bool writeRoute(vector<int> path);
};

#endif  //READ_SQL_H_
