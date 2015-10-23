#include "AdjacencyList.h"

AdjacencyList::AdjacencyList(int numVert):Graph(numVert){
    graList = new LList<listUnit>[numVert];
}

AdjacencyList::~AdjacencyList(){
    //delete []LList<listUnit>;
}

Edge AdjacencyList::firstEdge(int oneVertex){
    Edge myEdge;
    myEdge.setFrom(oneVertex);
    Link<listUnit> *temp = graList[oneVertex].head;
    if(temp->next != NULL){
        myEdge.setTo(temp->next->element.vertex);
        myEdge.setWeight(temp->next->element.weight);
    }
    return myEdge;
}

Edge AdjacencyList::nextEdge(Edge pre){
    Edge myEdge;
    myEdge.setFrom(pre.getFrom());
    Link<listUnit> *temp = graList[pre.getFrom()].head;
    while(temp->next != NULL && temp->next->element.vertex <= pre.getTo())
        temp = temp->next;
    if(temp->next != NULL){
        myEdge.setTo(temp->next->element.vertex);
        myEdge.setWeight(temp->next->element.weight);
    }
    return myEdge;
}

void AdjacencyList::setEdge(int from, int to, int weight){
    from--;
    to--;
    Link<listUnit> *temp = graList[from].head;
    while(temp->next != NULL && temp->next->element.vertex < to)
        temp = temp->next;
    if(temp->next == NULL){
        temp->next = new Link<listUnit>;
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;
        setNumEdge(edgesNumber()+1);
        getIndegree()[to]++;
        return;
    }
    if(temp->next->element.vertex == to){
        temp->next->element.weight = weight;
        return;
    }
    if(temp->next->element.vertex > to){
        Link<listUnit> *other = temp->next;
        temp->next = new Link<listUnit>;
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;
        temp->next->next = other;
        setNumEdge(edgesNumber()+1);
        getIndegree()[to]++;
        return;
    }
}

void AdjacencyList::delEdge(int from, int to){
    Link<listUnit> *temp = graList[from].head;
    while(temp->next != NULL
            && temp->next->element.vertex < to)
        temp = temp->next;
    if(temp->next == NULL)
        return;
    if(temp->next->element.vertex > to)
        return;
    if(temp->next->element.vertex == to){
        Link<listUnit> *other = temp->next->next;
        delete temp->next;
        temp->next = other;
        setNumEdge(edgesNumber()-1);
        getIndegree()[to]--;
        return;
    }
}
int AdjacencyList::fromVertex(Edge edge){
    return edge.getFrom();
}

int AdjacencyList::toVertex(Edge edge){
    return edge.getTo();
}

int AdjacencyList::weight(Edge edge){
    return edge.getWeight();
}

