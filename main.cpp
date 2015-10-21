#include <vector>
#include <iostream>
#include <stdexcept>
#include "FloydWarshall.h"
#include "readsql.h"

using namespace std;

int main(){
    int nodes, edges;
    int from, to;

    edges = 0;
    nodes = 71;
    Graph g = Graph(nodes);
    eSQL e = eSQL();
    e.readGraph(g, nodes, edges);

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
            path = g.findShortestPath(from, to);
            e.writeRoute(path);
            /*e.readStation(path[1], fromName);
            if(path[0] < 9999999){
                cout << fromName;
                for(int i = 2; i < path.size(); i++){
                    e.readLink(path[i-1], path[i], curRouteID, lastRouteID, cost);
                    e.readStation(path[i], toName);
                    if(curRouteID != lastRouteID){
                        e.readRoute(curRouteID, price);
                        sum += price;
                    }
                    cout << "--" << curRouteID << "/" << cost << "m--" << toName;
                    lastRouteID = curRouteID;
                }
                cout << endl;
                cout << "distance: " << (double)path[0]/1000 << "km, time:" << (double)path[0]/15000*60 << "min, " << "price: " << sum << " yuan" << endl << endl;;
            }
            else
                cout << "NO PATH" << endl;*/
        }catch(logic_error& e){
            cout << e.what() << endl;
        }
    }
    return 0;
}
