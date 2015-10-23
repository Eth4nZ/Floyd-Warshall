#ifndef ADJACENCY_LIST_H_
#define ADJACENCY_LIST_H_
#include <stddef.h>
#include "Graph.h"

struct listUnit{
    int vertex;
    int weight;
};


template <class Elem>
class Link{
public: Elem element;
    Link *next;
   /* Link(){
        next = NULL;
    }*/

    Link(const Elem& elemval, Link *nextval = NULL){
        element = elemval;
        next = nextval;
    }

    Link(Link *nextval = NULL){
        next = nextval;
    }
};


template <class Elem>
class LList{
public:
    Link<Elem> *head;
    LList(){
        head = new Link<Elem>();
    }
};


class AdjacencyList: public Graph{
private:
    LList<listUnit> *graList;
public:
    AdjacencyList(int);
    ~AdjacencyList();
    Edge firstEdge(int oneVertex);
    Edge nextEdge(Edge pre);
    void setEdge(int from, int to, int weight);
    void delEdge(int from, int to);
    int fromVertex(Edge edge);
    int toVertex(Edge edge);
    int weight(Edge edge);

};

#endif // ADJACENCY_LIST_H_
