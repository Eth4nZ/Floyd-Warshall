#ifndef FLOYD_WARSHALL_H_
#define FLOYD_WARSHALL_H_

#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class Graph{
private:
    int nodes;
    vector<vector<vector<int> > > adjacency_matrix;
public:
    Graph(int nodes);
    vector<int> findShortestPath(int from, int to);
    vector<int> findLongestPath(int from, int to);
    vector<int> findShortestPath(int from, int trans, int to);
    vector<int> findCheapestPath(int from, int to);
    void connect(int from, int to, int cost);
};

#endif  //FLOYD_WARSHALL_H_
