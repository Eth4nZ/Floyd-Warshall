#include <iostream>
#include "Graph.h"
//#include "readsql.h"

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
    }
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


vector<int> Graph::findShortestPath_trans(int from, int trans, int to){
    vector<int> path;
    vector<int> path1;
    vector<int> path2;
    path1 = findShortestPath(from, trans);
    path2 = findShortestPath(trans, to);
    path.push_back(path1[0]+path2[0]);
    for(int i = 1; i < (int)path1.size(); i++)
        path.push_back(path1[i]);
    for(int i = 2; i < (int)path2.size(); i++)
        path.push_back(path2[i]);
    return path;
}

vector<int> Graph::findFewestTransPath(int s, int sto){
/*    bool FOUND;
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
    }
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
            string lastRouteID = "";   //D[v]->pre, v
            string curRouteID;    //v, toVertex(e)
            int cost;
            eSQL es = eSQL();
            es.readLink(D[v]->pre, v, lastRouteID, "", cost);
            es.readLink(v, toVertex(e), curRouteID, lastRouteID, cost);
            if(curRouteID == lastRouteID)
                //D[toVertex(e)]->length = 


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
    */
}

