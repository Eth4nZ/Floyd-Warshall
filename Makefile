CXX = g++

CXXFLAGS = -c -Wall -I/usr/include/mysql++ -I/usr/include/mysql
LDFLAGS = -L/usr/lib -lmysqlpp -lmysqlclient -lnsl -lz -lm

SOURCES = Edge.cpp MinHeap.cpp Graph.cpp AdjacencyList.cpp readsql.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = a.out

all: $(SOURCES) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CXX) $< -o $@ $(CXXFLAGS) $(LDFLAGS)

.phony: clean

clean:
	rm *.o

