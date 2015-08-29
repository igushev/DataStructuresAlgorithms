CC=g++
INC=-I./
CFLAGS=-c -Wall
BIN=Graph
DATA_BIN=DataGraph

all: Graph DataGraph

Graph: Graph.o GraphPrimDijkstra.o GraphKruskal.o GraphDijkstra.o GraphUnit.o
	$(CC) $(INC) -Wall Graph.o GraphPrimDijkstra.o GraphKruskal.o GraphDijkstra.o GraphUnit.o -o $(BIN)

Graph.o: Graph.h Graph.C
	$(CC) $(INC) $(CFLAGS) Graph.C

GraphPrimDijkstra.o: Graph.h GraphPrimDijkstra.C
	$(CC) $(INC) $(CFLAGS) GraphPrimDijkstra.C

GraphKruskal.o: Graph.h GraphKruskal.C
	$(CC) $(INC) $(CFLAGS) GraphKruskal.C

GraphDijkstra.o: Graph.h GraphDijkstra.C
	$(CC) $(INC) $(CFLAGS) GraphDijkstra.C

GraphUnit.o: Graph.h GraphUnit.C
	$(CC) $(INC) $(CFLAGS) GraphUnit.C

DataGraph: Graph.o GraphPrimDijkstra.o GraphKruskal.o GraphDijkstra.o DataGraph.o
	$(CC) $(INC) -Wall Graph.o GraphPrimDijkstra.o GraphKruskal.o GraphDijkstra.o DataGraph.o -o $(DATA_BIN)

DataGraph.o: DataGraph.h DataGraph.C
	$(CC) $(INC) $(CFLAGS) DataGraph.C

clean:
	rm -rf *.o $(BIN) $(DATA_BIN)
