#include <vector>
#include <iostream>
#include <stdexcept>
#include "FloydWarshall.h"
#include "readsql.h"

using namespace std;

int main(){
    int nodes, edges, queries;
    int from, to;

    edges = 0;
    nodes = 70;
    Graph g(nodes);
    eSQL e;
    e.readsql(g, nodes, edges);

    cout << "please input queries: ";
    cin >> queries;


    vector<int> path;
    for(int i = 0; i < queries; i++){
        cin >> from;
        cin >> to;
        try{
            path = g.findShortestPath(from, to);
            cout << "cost = " << path[0] << endl;
            for(int i = 1; i < path.size()-1; i++){
                cout << path[i] << "-";
            }
            cout << path.back() << endl;
        }catch(logic_error& e){
        cout << e.what() << endl;
        }
    }
    return 0;
}
