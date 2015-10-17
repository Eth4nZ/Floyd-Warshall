#ifndef READ_SQL_H_
#define READ_SQL_H_

#include <mysql++.h>
#include "FloydWarshall.h"
#include "readsql.h"

using namespace std;
using namespace mysqlpp;

class eSQL{
public:
    eSQL();

    bool readsql(Graph&, int&, int&);
};

#endif  //READ_SQL_H_
