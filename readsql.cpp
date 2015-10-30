#include "readsql.h"
#include <vector>

using namespace std;
using namespace mysqlpp;

eSQL::eSQL(){
}

bool eSQL::readGraph(Graph &g, int &nodes, int &edges){
    StoreQueryResult ares;
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();

        query << "SELECT COUNT(*) AS Station_count FROM Station;";
        ares = query.store();
        nodes = ares[0]["Station_count"];

        query << "SELECT * FROM Link;";
        ares = query.store();
        for (size_t i = 0; i < ares.num_rows(); i++){
            edges++;
            g.setEdge(ares[i]["sfrom"], ares[i]["sto"], ares[i]["cost"]);
        }
    } catch (BadQuery er) { // handle any connection or
        // query errors that may come up
        cerr << "Error: " << er.what() << endl;
        return -1;
    } catch (const BadConversion& er) {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
                "\tretrieved data size: " << er.retrieved <<
                ", actual size: " << er.actual_size << endl;
        return -1;
    } catch (const Exception& er) {
        // Catch-all for any other MySQL++ exceptions
        cerr << "Error: " << er.what() << endl;
        return -1;
    }

    return (EXIT_SUCCESS);
}

bool eSQL::readGraphMinWalk(Graph &g, int &nodes, int &edges){
    StoreQueryResult ares;
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();

        query << "SELECT COUNT(*) AS Station_count FROM Station;";
        ares = query.store();
        nodes = ares[0]["Station_count"];

        query << "SELECT * FROM Link;";
        ares = query.store();
        for (size_t i = 0; i < ares.num_rows(); i++){
            edges++;
            if(ares[i]["routeID"] == "foot")
                g.setEdge(ares[i]["sfrom"], ares[i]["sto"], ares[i]["cost"]*10);
            else
                g.setEdge(ares[i]["sfrom"], ares[i]["sto"], 1);
        }
    } catch (BadQuery er) { // handle any connection or
        // query errors that may come up
        cerr << "Error: " << er.what() << endl;
        return -1;
    } catch (const BadConversion& er) {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
                "\tretrieved data size: " << er.retrieved <<
                ", actual size: " << er.actual_size << endl;
        return -1;
    } catch (const Exception& er) {
        // Catch-all for any other MySQL++ exceptions
        cerr << "Error: " << er.what() << endl;
        return -1;
    }

    return (EXIT_SUCCESS);
}

bool eSQL::readGraphCheapest(Graph &g, int &nodes, int &edges){
    StoreQueryResult ares, ares1;
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();

        query << "SELECT COUNT(*) AS Station_count FROM Station;";
        ares = query.store();
        nodes = ares[0]["Station_count"];

        query << "SELECT * FROM Link;";
        ares = query.store();
        for (size_t i = 0; i < ares.num_rows(); i++){
            edges++;
            Query q1 = conn.query();
            q1 << "SELECT * FROM Route where id = '" << ares[i]["routeID"] << "';";
            ares1 = q1.store();
            int pr = ares1[0]["price"];
            if(pr == 0)
                pr = 1;
            else
                pr *= 10;
            g.setEdge(ares[i]["sfrom"], ares[i]["sto"], pr);
        }
    } catch (BadQuery er) { // handle any connection or
        // query errors that may come up
        cerr << "Error: " << er.what() << endl;
        return -1;
    } catch (const BadConversion& er) {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
                "\tretrieved data size: " << er.retrieved <<
                ", actual size: " << er.actual_size << endl;
        return -1;
    } catch (const Exception& er) {
        // Catch-all for any other MySQL++ exceptions
        cerr << "Error: " << er.what() << endl;
        return -1;
    }

    return (EXIT_SUCCESS);
}

bool eSQL::readStation(int id, string &name){
    name = "";
    StoreQueryResult ares;
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();
        query << "SELECT * FROM Station where id = " << id << ";";
        StoreQueryResult ares = query.store();
        name.append(ares[0]["name"]);
    } catch (BadQuery er) { // handle any connection or
        // query errors that may come up
        cerr << "Error: " << er.what() << endl;
        return -1;
    } catch (const BadConversion& er) {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
                "\tretrieved data size: " << er.retrieved <<
                ", actual size: " << er.actual_size << endl;
        return -1;
    } catch (const Exception& er) {
        // Catch-all for any other MySQL++ exceptions
        cerr << "Error: " << er.what() << endl;
        return -1;
    }

    return (EXIT_SUCCESS);
}

bool eSQL::readLink(int sfrom, int sto, string &routeID, string lastRouteID, int &cost){
    StoreQueryResult ares;
    int cost_temp;
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();
        query << "SELECT * FROM Link where sfrom = " << sfrom << " and sto = " << sto <<  ";";
        StoreQueryResult ares = query.store();
        if(ares.num_rows() > 1){
            int mincost = ares[0]["cost"];
            routeID = "";
            routeID.append(ares[0]["routeID"]);
            for (size_t i = 0; i < ares.num_rows(); i++){
                if(ares[i]["routeID"] == lastRouteID){
                    routeID = "";
                    routeID.append(ares[i]["routeID"]);
                    cost = ares[i]["cost"];
                }
                else{
                    cost_temp = ares[i]["cost"];
                    if(cost_temp < mincost){
                        mincost = ares[i]["cost"];
                        routeID = "";
                        routeID.append(ares[i]["routeID"]);
                    }
                }
            }
        }
        else{
            routeID = "";
            routeID.append(ares[0]["routeID"]);
            cost = ares[0]["cost"];
        }
    } catch (BadQuery er) { // handle any connection or
        // query errors that may come up
        cerr << "Error: " << er.what() << endl;
        return -1;
    } catch (const BadConversion& er) {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
                "\tretrieved data size: " << er.retrieved <<
                ", actual size: " << er.actual_size << endl;
        return -1;
    } catch (const Exception& er) {
        // Catch-all for any other MySQL++ exceptions
        cerr << "Error: " << er.what() << endl;
        return -1;
    }

    return (EXIT_SUCCESS);
}

bool eSQL::readRoute(string id, int &price){
    StoreQueryResult ares;
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();
        query << "SELECT * FROM Route where id = '" << id << "';";
        StoreQueryResult ares = query.store();
        price = (ares[0]["price"]);
    } catch (BadQuery er) { // handle any connection or
        // query errors that may come up
        cerr << "Error: " << er.what() << endl;
        return -1;
    } catch (const BadConversion& er) {
        // Handle bad conversions
        cerr << "Conversion error: " << er.what() << endl <<
                "\tretrieved data size: " << er.retrieved <<
                ", actual size: " << er.actual_size << endl;
        return -1;
    } catch (const Exception& er) {
        // Catch-all for any other MySQL++ exceptions
        cerr << "Error: " << er.what() << endl;
        return -1;
    }

    return (EXIT_SUCCESS);
}

bool eSQL::writeRoute(vector<int> path){
    string curRouteID, lastRouteID;
    string fromName, toName;
    int sumPrice = 0, price, cost;
    int sumDistance = 0;
    int footDistance = 0;

    readStation(path[1], fromName);
    if(path[0] < 9999999){
        cout << fromName;
        for(int i = 2; i < (int)path.size(); i++){
            readLink(path[i-1], path[i], curRouteID, lastRouteID, cost);
            readStation(path[i], toName);
            sumDistance += cost;
            if(curRouteID == "foot")
                footDistance += cost;
            if(curRouteID != lastRouteID){
                readRoute(curRouteID, price);
                sumPrice += price;
            }
            cout << "--" << curRouteID << "/" << cost << "m--" << toName;
            lastRouteID = curRouteID;
        }
            cout << endl;
            cout << "distance: " << (double)sumDistance/1000 << "km, time:" << (double)sumDistance/15000*60 << "min, " << "price: " << sumPrice << " yuan" << endl;
            cout << "foot distance: " << footDistance << "m" << endl;
            return 1;
    }
    else{
        cout << "NO PATH" << endl;
        return 0;
    }
}

bool eSQL::writeBrief(int from, int to){
    string fromName, toName;
    readStation(from, fromName);
    readStation(to, toName);
    cout << fromName << " ---> " << toName << endl;;
    return 1;
}

bool eSQL::writeBrief(int from, int trans, int to){
    string fromName, transName, toName;
    readStation(from, fromName);
    readStation(to, toName);
    readStation(trans, transName);
    cout << fromName << " ---> " << transName << " ---> " << toName << endl;;
    return 1;
}
