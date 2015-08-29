#include "Graph.h"

#include <iostream>

void createFakeGrapth1(Graph& graph)
{
  graph.PushEdge(0, 1, 1);
  graph.PushEdge(1, 2, 1);
  graph.PushEdge(0, 3, 5);
  graph.PushEdge(3, 4, 1);
  graph.PushEdge(1, 3, 1);
  graph.PushEdge(4, 5, 1);
  graph.PushEdge(5, 6, 5);
  graph.PushEdge(2, 6, 1);
  graph.PushEdge(6, 0, 1);
  graph.PushEdge(6, 7, 1);
  graph.PushEdge(6, 8, 1);
  graph.PushEdge(7, 9, 1);
  graph.PushEdge(8, 9, 1);
}

void createFakeGrapth2(Graph& graph)
{
  graph.PushEdge(0, 1, 1);
  graph.PushEdge(1, 2, 1);
  graph.PushEdge(2, 3, 1);
  graph.PushEdge(3, 4, 1);
  graph.PushEdge(4, 5, 1);
  graph.PushEdge(0, 5, 1);
  graph.PushEdge(5, 4, 2);
}

struct Visitor {
  void visit(unsigned id) { std::cout << id << ' '; }
};

int main(int argc, char** args)
{
  Graph graph;
  createFakeGrapth1(graph);
  std::cout << "Nodes count is " << graph.NodesCount() << std::endl;

  std::cout << "Adjacency List:" << std::endl;
  Graph::adjacency_list_t adjacency_list = graph.AdjacencyList();
  for (int i = 0; i < adjacency_list.size(); ++i) {
    std::cout << i << ": ";
    for (std::list<unsigned>::const_iterator node = adjacency_list[i].begin();
      node != adjacency_list[i].end(); ++node)
      std::cout << *node << ' ';
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Adjacency Maxtrix:" << std::endl;
  Graph::adjacency_matrix_t adjacency_matrix = graph.AdjacencyMaxtrix();

  std::cout << std::string(4, ' ');
  for (int i = 0; i < adjacency_matrix.size(); ++i) {
      std::cout.width(3);
      std::cout << i;
  }
  std::cout << std::endl;

  for (int i = 0; i < adjacency_matrix.size(); ++i) {
    std::cout.width(3);
    std::cout << i << ":";
    for (int j = 0; j < adjacency_matrix[i].size(); ++j) {
      std::cout.width(3);
      if (adjacency_matrix[i][j] != -1)
        std::cout << adjacency_matrix[i][j];
      else
        std::cout << "-";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  Visitor visitor;

  std::cout << "Depth-First Traversal: ";
  graph.DepthFirstTraversal(&visitor);
  std::cout << std::endl << std::endl;

  std::cout << "Breadth-First Traversal: ";
  graph.BreadthFirstTraversal(&visitor);
  std::cout << std::endl << std::endl;

  std::cout << "Minimul Spanning Tree by Kruskal: ";
  Graph::id_vector_t mstk_edges = graph.MinimulSpanningTreeKruskal();
  for (unsigned i = 0; i < mstk_edges.size(); ++i)
    std::cout << mstk_edges[i] << ' ';
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Minimul Spanning Tree by Prim-Dijkstra: ";
  Graph::id_vector_t mstpd_edges = graph.MinimulSpanningTreePrimDijkstra();
  for (unsigned i = 0; i < mstpd_edges.size(); ++i)
    std::cout << mstpd_edges[i] << ' ';
  std::cout << std::endl;
  std::cout << std::endl;

  int path_from = 0, path_to = 9;
  std::cout << "Minimul Path by Dijkstra from " << path_from << " to " << path_to << ": ";
  Graph::node_edge_vector_t mp = graph.MinimulPathDijkstra(path_from, path_to);
  for (unsigned i = 0; i < mp.size(); ++i) {
    std::cout << mp[i].node << ' ';
    if (mp[i].edge != -1)
      std::cout << '(' << mp[i].edge << ") ";
  }
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Minimul Paths by Dijkstra from " << path_from << " to " << path_to << ":" << std::endl;
  Graph::node_edge_vector_vector_t mps = graph.MinimulPathsDijkstra(path_from, path_to);
  for (unsigned i = 0; i < mps.size(); ++i) {
    for (unsigned j = 0; j < mps[i].size(); ++j) {
      std::cout << mps[i][j].node << ' ';
      if (mps[i][j].edge != -1)
        std::cout << '(' << mps[i][j].edge << ") ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
