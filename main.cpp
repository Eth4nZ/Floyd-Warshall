#include <vector>
#include <iostream>
#include <stdexcept>
#include "Graph.h"
#include "AdjacencyList.h"
#include "readsql.h"

using namespace std;

int main(){
    int nodes, edges;
    int from, to;

    edges = 0;
    nodes = 500;
    AdjacencyList g(nodes);
    eSQL e = eSQL();
    e.readGraph(g, nodes, edges);
    cout << nodes << " " << edges << endl;

    //cout << "please input queries: ";
    //cin >> queries;


    vector<int> path;
    //for(int i = 0; i < queries; i++){
    while(1){
        cout << "1.BJUT 2.BUAA 3.CUC 4.BNU 5.PKU 6.THU 7.RUC" << endl;
        cout << "please input a route (from, to): ";
        cin >> from;
        if(from < 0)
            break;
        cin >> to;
        try{
            cout << "---" << endl;
            path = g.findShortestPath(from, to);
            cout << "---" << endl;
            e.writeRoute(path);
        }catch(logic_error& e){
            cout << e.what() << endl;
        }
    }
    return 0;
}
