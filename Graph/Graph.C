#include "Graph.h"

unsigned Graph::PushEdge(unsigned from, unsigned to, unsigned weight)
{
  _uptodate_adjacency_list = false;
  _uptodate_adjacency_matrix = false;
  _uptodate_mstpd_edges = false;
  _uptodate_mstk_edges = false;

  ReserveNodes(from+1);
  ReserveNodes(to+1);

  unsigned id = _edges.size();
  _edges.push_back(Edge(id, from, to, weight));
  return id;
}

const Graph::adjacency_list_t& Graph::AdjacencyList() const
{
  if (_uptodate_adjacency_list)
    return _adjacency_list;

  _adjacency_list.resize(_nodes_count);
  for (unsigned i = 0; i < _adjacency_list.size(); ++i)
    _adjacency_list[i].clear();

  for (unsigned i = 0; i < _edges.size(); ++i)
    _adjacency_list[_edges[i].from].push_back(_edges[i].to);

  _uptodate_adjacency_list = true;
  return _adjacency_list;
}

const Graph::adjacency_matrix_t& Graph::AdjacencyMaxtrix() const
{
  if (_uptodate_adjacency_matrix)
    return _adjacency_matrix;

  _adjacency_matrix.resize(_nodes_count);
  for (unsigned i = 0; i < _adjacency_matrix.size(); ++i)
  {
    _adjacency_matrix[i].resize(_nodes_count);
    for (unsigned j = 0; j < _adjacency_matrix[i].size(); ++j)
      _adjacency_matrix[i][j] = -1;
  }

  for (unsigned i = 0; i < _edges.size(); ++i)
    _adjacency_matrix[_edges[i].from][_edges[i].to] = i;

  _uptodate_adjacency_matrix = true;
  return _adjacency_matrix;
}
