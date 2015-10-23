#include <iostream>
#include "Graph.h"

using namespace std;

Graph::Graph(){
//    Graph(10);
}

Graph::Graph(int numVertex){
    this->numVertex = numVertex;
    numEdge = 0;
    visited = new bool[numVertex];
    indegree = new int[numVertex];
    for(int i = 0; i < numVertex; i++){
        visited[i] = false;
        indegree[i] = 0;
    }
}

Graph::~Graph(){
    delete []visited;
    delete []indegree;
}

int Graph::vecticesNumber(){
    return numVertex;
}

int Graph::edgesNumber(){
    return numEdge;
}

void Graph::setNumEdge(int numEdge){
    this->numEdge = numEdge;
}

bool* Graph::getVisited(){
    return visited;
}

int* Graph::getIndegree(){
    return indegree;
}

bool Graph::isEdge(Edge edge){
    if(edge.getWeight() > 0 && edge.getWeight() < INFINITY && edge.getTo() >= 0)
        return true;
    else
        return false;
}

vector<int> Graph::findShortestPath(int s, int sto){
    bool FOUND;
    int i;
    Dist d;
    Dist** D;
    s--;
    sto--;

    D = new Dist*[vecticesNumber()];
    for(i = 0; i < vecticesNumber(); i++){
        D[i] = new Dist;
        getVisited()[i] = false;
        D[i]->index = i;
        D[i]->length = INFINITY;
        D[i]->pre = s;
    //    cout << i << " index: " << D[i]->index <<  " length: " << D[i]->length << " pre: " << D[i]->pre << endl;
    }
    cout << "aaa" << endl;
    D[s]->length = 0;
    MinHeap H(edgesNumber()); // = new MinHeap(G.edgesNumber());
    H.insert(D[s]);
    for(i = 0; i < vecticesNumber(); i++){
        FOUND = false;
        while(!H.isEmpty()){
            d = H.removeMin();
            if(getVisited()[d.index] == false){
                FOUND = true;
                break;
            }
        }
        if(!FOUND)
            break;
        int v = d.index;
        getVisited()[v] = true;
        for(Edge e = firstEdge(v); isEdge(e); e = nextEdge(e))
            if(D[toVertex(e)]->length
                    > (D[v]->length+weight(e))){
                D[toVertex(e)]->length = D[v]->length+weight(e);
                D[toVertex(e)]->pre = v;
                H.insert(D[toVertex(e)]);
            }
    }
    vector<int> path;
    int p = sto;
    path.insert(path.begin(), p+1);
    while(p != s){
        path.insert(path.begin(), D[p]->pre+1);
        p = D[p]->pre;
    }
    path.insert(path.begin(), D[sto]->length);
    return path;
}


