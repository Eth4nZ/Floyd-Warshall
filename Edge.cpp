#include "Edge.h"

Edge::Edge(){
    from = -1;
    to = -1;
    weight = 0;
}

Edge::Edge(int from, int to, int weight){
    this->from = from;
    this->to = to;
    this->weight = weight;
}

Edge::~Edge(){
}

int Edge::getFrom(){
    return from;
}

void Edge::setFrom(int from){
    this->from = from;
}

int Edge::getTo(){
    return to;
}

void Edge::setTo(int to){
    this->to = to;
}

int Edge::getWeight(){
    return weight;
}

void Edge::setWeight(int weight){
    this->weight = weight;
}


