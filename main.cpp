#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include "Graph.h"
#include "AdjacencyList.h"
#include "readsql.h"

using namespace std;

int main(){
    int nodes, edges;
    int from, to, trans;

    edges = 0;
    nodes = 500;
    AdjacencyList g(nodes);
    eSQL e = eSQL();
    e.readGraph(g, nodes, edges);



    vector<int> path;
    //for(int i = 0; i < queries; i++){
    while(1){
        cout << "1.BJUT 2.BUAA 3.CUC 4.BNU 5.PKU 6.THU 7.RUC" << endl;
        cout << "please input a route (from, to): ";
        cin >> from;
        cin >> to;

        char ch;
        ch = getchar();
        trans = -1;
        if(ch != '\n')
            cin >> trans;
        if(from < 0)
            break;

        try{
            if(trans == -1){
                path = g.findShortestPath(from, to);
                e.writeRoute(path);
            }
            else{
                path = g.findShortestPath(from, trans);
                e.writeRoute(path);
                path = g.findShortestPath(trans, to);
                e.writeRoute(path);
            }
        }catch(logic_error& e){
            cout << e.what() << endl;
        }
    }
    return 0;
}
