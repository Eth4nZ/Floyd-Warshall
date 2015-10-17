#ifndef READ_SQL_H_
#define READ_SQL_H_

#include <iostream>
#include <mysql++.h>
#include "FloydWarshall.h"

using namespace std;
using namespace mysqlpp;

class eSQL{
public:
    eSQL();
    bool readsql(Graph &g, int &nodes, int &edges);
};

#endif //READ_SQL_H_
