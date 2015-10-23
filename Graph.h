#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <vector>
#include "Edge.h"
#include "Dist.h"
#include "MinHeap.h"

using namespace std;

class Graph{
private:
    int numVertex;
    int numEdge;
    bool *visited;
    int *indegree;
public:
    Graph();
    Graph(int numVertex);
    ~Graph();
    int vecticesNumber();
    int edgesNumber();
    void setNumEdge(int numEdge);
    bool* getVisited();
    int* getIndegree();
    bool isEdge(Edge edge);
    vector<int> findShortestPath(int s, int sto);
    virtual Edge firstEdge(int oneVertex)=0;
    virtual Edge nextEdge(Edge pre)=0;
    virtual void setEdge(int from, int to, int weight)=0;
    virtual void delEdge(int from, int to)=0;
    virtual int fromVertex(Edge edge)=0;
    virtual int toVertex(Edge edge)=0;
    virtual int weight(Edge edge)=0;
};

#endif
