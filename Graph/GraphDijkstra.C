#include "Graph.h"

Graph::node_edge_vector_t Graph::MinimulPathDijkstra(unsigned path_from, unsigned path_to) const
{
  AdjacencyMaxtrix();

  if (path_from >= _nodes_count || path_to >= _nodes_count)
    throw std::out_of_range("Path nodes are out of range");

  std::vector<bool> nodes_in_tree;
  nodes_in_tree.resize(_nodes_count, false);
  std::vector<bool> neighbour_nodes;
  neighbour_nodes.resize(_nodes_count, false);
  std::vector<PathToNode> path_to_nodes;
  path_to_nodes.resize(_nodes_count, PathToNode(-1, -1, 0));
  std::multiset<const Edge*, EdgePointerComparator> neighbour_edges;

  nodes_in_tree[path_from] = true;
  for (unsigned j = 0; j < _nodes_count; ++j)
    if (_adjacency_matrix[path_from][j] != -1) {
      neighbour_nodes[j] = true;
      path_to_nodes[j] = PathToNode(path_from,
        _adjacency_matrix[path_from][j],
        _edges[ _adjacency_matrix[path_from][j] ].weight);
      neighbour_edges.insert(&_edges[ _adjacency_matrix[path_from][j] ]);
    }

  while (!nodes_in_tree[path_to] && neighbour_edges.size()) {
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
    for (unsigned j = 0; j < _nodes_count; ++j) {

      //for each new neighbour node
      if (_adjacency_matrix[add_node][j] != -1 && !nodes_in_tree[j]) {

        //if it wasn't in neighbour multiset just add it
        if (!neighbour_nodes[j]) {
          neighbour_nodes[j] = true;
          path_to_nodes[j] = PathToNode(add_node,
            _adjacency_matrix[add_node][j],
            path_to_nodes[add_node].total_weight_to + _edges[ _adjacency_matrix[add_node][j] ].weight);
          neighbour_edges.insert(&_edges[ _adjacency_matrix[add_node][j] ]);
        }
        //else compare the edge with the existed one
        else {
          unsigned from = path_to_nodes[j].from_node;
          unsigned add_weight =
            path_to_nodes[add_node].total_weight_to + _edges[ _adjacency_matrix[add_node][j] ].weight;
          unsigned from_weight =
            path_to_nodes[from].total_weight_to + _edges[ _adjacency_matrix[from][j] ].weight;
          if (add_weight < from_weight) {
            path_to_nodes[j].from_node = add_node;
            path_to_nodes[j].using_edge = _adjacency_matrix[add_node][j];
            path_to_nodes[j].total_weight_to = add_weight;
            neighbour_edges.insert(&_edges[ _adjacency_matrix[add_node][j] ]);
            neighbour_edges.erase(&_edges[ _adjacency_matrix[from][j] ]);
          }
        }
      }
    }
  }

  if (!nodes_in_tree[path_to])
    throw std::runtime_error("The path doesn't exist");

  node_edge_vector_t result_reverse, result;
  unsigned current = path_to;
  result_reverse.push_back(NodeEdge(path_to, -1));
  while (current != path_from) {
    result_reverse.push_back( NodeEdge( path_to_nodes[current].from_node, path_to_nodes[current].using_edge ) );
    current = path_to_nodes[current].from_node;
  }

  result.reserve(result_reverse.size());
  for (unsigned i = result_reverse.size()-1; i != -1; --i)
    result.push_back(result_reverse[i]);
  return result;
}

Graph::node_edge_vector_vector_t Graph::MinimulPathsDijkstra(unsigned path_from, unsigned path_to, double k) const
{
  AdjacencyMaxtrix();

  if (path_from >= _nodes_count || path_to >= _nodes_count)
    throw std::out_of_range("Path nodes are out of range");

  enum State {Initial, FindedMinimum, Complete};

  std::vector<bool> nodes_in_tree;
  nodes_in_tree.resize(_nodes_count, false);
  std::vector<bool> edges_in_tree;
  edges_in_tree.resize(_edges.size(), false);
  std::vector<bool> neighbour_nodes;
  neighbour_nodes.resize(_nodes_count, false);
  std::vector<bool> neighbour_edges;
  neighbour_edges.resize(_edges.size(), false);
  std::vector<PathsToNode> paths_to_nodes;
  paths_to_nodes.resize(_nodes_count);
  std::multiset<const Edge*, EdgePointerComparator> neighbour_edges_queue;

  nodes_in_tree[path_from] = true;
  for (unsigned j = 0; j < _nodes_count; ++j)
    if (_adjacency_matrix[path_from][j] != -1) {
      neighbour_nodes[j] = true;
      neighbour_edges[ _adjacency_matrix[path_from][j] ] = true;
      paths_to_nodes[j].push_back( PathToNode(path_from,
        _adjacency_matrix[path_from][j],
        _edges[ _adjacency_matrix[path_from][j] ].weight) );
      neighbour_edges_queue.insert(&_edges[ _adjacency_matrix[path_from][j] ]);
    }

  unsigned long minimum_weight = 0;
  State state = Initial;

  while (state != Complete && neighbour_edges_queue.size()) {
    //choose edge with minimul weight
    //the multiset is sorted, the first element is minimul
    typename std::multiset<const Edge*, EdgePointerComparator>::iterator add_edge_it =
      neighbour_edges_queue.begin();
    const Edge* add_edge = *add_edge_it;
    neighbour_edges_queue.erase(add_edge_it);

    //add node which is the end of the minimul edge
    unsigned add_node = add_edge->to;
    neighbour_nodes[add_node] = false;
    neighbour_edges[add_edge->id] = false;

    //insert new node and new edge
    nodes_in_tree[add_node] = true;
    edges_in_tree[add_edge->id] = true;
    for (unsigned j = 0; j < _nodes_count; ++j) {

      //for each new neighbour node
      if (_adjacency_matrix[add_node][j] != -1 &&
          !edges_in_tree[ _adjacency_matrix[add_node][j] ] &&
          !neighbour_edges[ _adjacency_matrix[add_node][j] ]) {
        //We don't need to check if it was in neighbour multiset
        //because we are interested in all paths
        neighbour_nodes[j] = true;
        neighbour_edges[ _adjacency_matrix[add_node][j] ] = true;

        paths_to_nodes[j].push_back(
          PathToNode(add_node,
          _adjacency_matrix[add_node][j],
          paths_to_nodes[add_node][0].total_weight_to + _edges[ _adjacency_matrix[add_node][j] ].weight) );

        neighbour_edges_queue.insert(&_edges[ _adjacency_matrix[add_node][j] ]);
      }
    }

    if (state == Initial && nodes_in_tree[path_to]) {
      state = FindedMinimum;
      minimum_weight = paths_to_nodes[path_to][0].total_weight_to;
    }
    else if (state == FindedMinimum && paths_to_nodes[add_node].back().total_weight_to / minimum_weight > k) {
      state = Complete;
    }
  }

  if (!nodes_in_tree[path_to])
    return node_edge_vector_vector_t();

  MinimulPathsResult result(paths_to_nodes);
  return result.Process(path_from, path_to);
}

Graph::node_edge_vector_vector_t Graph::MinimulPathsResult::Process(unsigned path_from, unsigned path_to)
{
  _path_from = path_from;
  node_edge_vector_vector_t result = _Process(path_to);
  for (unsigned i = 0; i < result.size(); ++i)
    result[i].push_back(NodeEdge(path_to, -1));
  return result;
}

Graph::node_edge_vector_vector_t Graph::MinimulPathsResult::_Process(unsigned node)
{
  node_edge_vector_vector_t result;
  for (unsigned i = 0; i < _paths_to_nodes[node].size(); ++i) {
    unsigned from_node = _paths_to_nodes[node][i].from_node;
    unsigned using_edge = _paths_to_nodes[node][i].using_edge;
    if (from_node == _path_from) {
      node_edge_vector_t mid_result(1, NodeEdge(from_node, using_edge));
      result.push_back(mid_result);
    }
    else {
      node_edge_vector_vector_t mid_results = _Process(from_node);
      for (unsigned j = 0; j < mid_results.size(); ++j) {
        node_edge_vector_t mid_result(mid_results[j]);
        mid_result.push_back(NodeEdge(from_node, using_edge));
        result.push_back(mid_result);
      }
    }
  }
  return result;
}
