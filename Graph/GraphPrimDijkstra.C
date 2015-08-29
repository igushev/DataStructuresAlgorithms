#include "Graph.h"

const Graph::id_vector_t& Graph::MinimulSpanningTreePrimDijkstra() const
{
  if (_uptodate_mstpd_edges)
    return _mstpd_edges;

  _mstpd_edges.clear();

  if (!_nodes_count)
    return _mstpd_edges;

  AdjacencyMaxtrix();

  std::vector<bool> nodes_in_tree;
  nodes_in_tree.resize(_nodes_count, false);
  std::vector<bool> neighbour_nodes;
  neighbour_nodes.resize(_nodes_count, false);
  std::vector<unsigned> path_to_nodes;
  path_to_nodes.resize(_nodes_count, -1);
  std::multiset<const Edge*, EdgePointerComparator> neighbour_edges;

  nodes_in_tree[0] = true;
  for (unsigned j = 0; j < _nodes_count; ++j)
    if (_adjacency_matrix[0][j] != -1) {
      neighbour_nodes[j] = true;
      path_to_nodes[j] = 0;
      neighbour_edges.insert(&_edges[ _adjacency_matrix[0][j] ]);
    }

  while (neighbour_edges.size()) {
    //choose edge with minimul weight
    //the multiset is sorted, the first element is minimul
    typename std::multiset<const Edge*, EdgePointerComparator>::iterator add_edge_it =
      neighbour_edges.begin();
    const Edge* add_edge = *add_edge_it;
    neighbour_edges.erase(add_edge_it);

    //add node which is the end of the minimul edge
    unsigned add_node = add_edge->to;
    neighbour_nodes[add_node] = false;

    //insert new node and new edge
    nodes_in_tree[add_node] = true;
    _mstpd_edges.push_back(add_edge->id);
    for (unsigned j = 0; j < _nodes_count; ++j) {

      //for each new neighbour node
      if (_adjacency_matrix[add_node][j] != -1 && !nodes_in_tree[j]) {

        //if it wasn't in neighbour multiset just add it
        if (!neighbour_nodes[j]) {
          neighbour_nodes[j] = true;
          path_to_nodes[j] = add_node;
          neighbour_edges.insert(&_edges[ _adjacency_matrix[add_node][j] ]);
        }
        //else compare the edge with the existed one
        else {
          unsigned from = path_to_nodes[j];
          unsigned add_weight = _edges[ _adjacency_matrix[add_node][j] ].weight;
          unsigned from_weight = _edges[ _adjacency_matrix[from][j] ].weight;
          if (add_weight < from_weight) {
            path_to_nodes[j] = add_node;
            neighbour_edges.insert(&_edges[ _adjacency_matrix[add_node][j] ]);
            neighbour_edges.erase(&_edges[ _adjacency_matrix[from][j] ]);
          }
        }
      }
    }
  }

  _uptodate_mstpd_edges = true;
  return _mstpd_edges;
}
