#include "readsql.h"

using namespace std;
using namespace mysqlpp;

eSQL::eSQL(){
}

bool eSQL::readsql(Graph &g, int &nodes, int &edges){
    StoreQueryResult ares;
    try {
        Connection conn(false);
        conn.set_option(new SetCharsetNameOption("utf8"));
        conn.connect("map", "localhost", "root", "dtbs");
        Query query = conn.query();

        query << "SELECT COUNT(*) AS Station_count FROM Station;";
        ares = query.store();
        nodes = ares[0]["Station_count"];
        Graph g0(nodes);

        query << "SELECT * FROM Link;";
        ares = query.store();
        for (size_t i = 0; i < ares.num_rows(); i++){
            edges++;
            g0.connect(ares[i]["sfrom"], ares[i]["sto"], ares[i]["cost"]);
        }
        g = g0;
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

