#include "DataGraph.h"

#include <string>
#include <iostream>

int main(int argc, char** args)
{
  DataGraph<std::string, std::string, std::string, std::string> data_graph;
  data_graph.PushNode("msc", "Moscow City");
  data_graph.PushNode("nnv", "N-Novgorod");
  data_graph.PushNode("krv", "Kirov");
  data_graph.PushNode("skt", "Syktyvkar");
  data_graph.PushNode("yrs", "Yaroslavl");
  data_graph.PushNode("spb", "Saint-Petersburg");

  data_graph.PushEdge("m5", "M5 road", "msc", "nnv", 300);
  data_graph.PushEdge("m6", "M6 road", "nnv", "krv", 500);
  data_graph.PushEdge("m7", "M7 road", "krv", "skt", 500);
  data_graph.PushEdge("e23", "E23 road", "msc", "spb", 700);
  data_graph.PushEdge("e34", "E34 road", "spb", "yrs", 300);
  data_graph.PushEdge("e43", "E43 road", "yrs", "nnv", 500);
  data_graph.PushEdge("e50", "E50 road", "yrs", "skt", 800);

  std::string from = "msc", to = "skt";

  std::cout << "Minimul path from " << from << " to " << to << ":" << std::endl;
  typename DataGraph<std::string, std::string, std::string, std::string>::node_edge_key_data_vector_t mp =
    data_graph.MinimulPathDijkstra(from , to);
  for (unsigned i = 0; i < mp.size(); ++i) {
    std::cout << *mp[i].node_data;
    if (mp[i].edge_data)
      std::cout << " (" << *mp[i].edge_data << ")";
    if (i != mp.size()-1)
      std::cout << " - ";
  }
  std::cout << std::endl << std::endl;

  std::cout << "Minimul paths from " << from << " to " << to << ":" << std::endl;
  typename DataGraph<std::string, std::string, std::string, std::string>::node_edge_key_data_vector_vector_t mps =
    data_graph.MinimulPathsDijkstra(from , to);
  for (unsigned i = 0; i < mps.size(); ++i) {
    for (unsigned j = 0; j < mps[i].size(); ++j) {
      std::cout << *mps[i][j].node_data;
      if (mps[i][j].edge_data)
        std::cout << " (" << *mps[i][j].edge_data << ")";
      if (j != mps[i].size()-1)
        std::cout << " - ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
