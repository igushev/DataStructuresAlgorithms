#include "Graph.h"

const Graph::id_vector_t& Graph::MinimulSpanningTreeKruskal() const
{
  if (_uptodate_mstk_edges)
    return _mstk_edges;

  _mstk_edges.clear();

  if (!_nodes_count)
    return _mstk_edges;

  std::vector<const Edge*> sorted_edges;
  sorted_edges.reserve(_edges.size());
  for (unsigned i = 0; i < _edges.size(); ++i)
    sorted_edges.push_back(&_edges[i]);
  std::sort(sorted_edges.begin(), sorted_edges.end(), EdgePointerComparator());

  unsigned edges_in_mst = 0;
  Subgraphes subgraphes(_nodes_count);
  for (unsigned i = 0; i < sorted_edges.size() && edges_in_mst < _nodes_count-1; ++i) {
    unsigned root_from = subgraphes.FindRoot(sorted_edges[i]->from);
    unsigned root_to = subgraphes.FindRoot(sorted_edges[i]->to);
    if (root_from == root_to)
      continue;
    subgraphes.Unite(root_from, root_to);
    _mstk_edges.push_back(sorted_edges[i]->id);
    ++edges_in_mst;
  }

  _uptodate_mstk_edges = true;
  return _mstk_edges;
}

unsigned Graph::Subgraphes::FindRoot(unsigned node) const
{
  while (!_sub_graphes[node].root)
    node = _sub_graphes[node].ancestor;
  return node;
}

void Graph::Subgraphes::Unite(unsigned one, unsigned two)
{
  if (!_sub_graphes[one].root || !_sub_graphes[two].root)
    throw std::runtime_error("You can't unite non-root nodes");

  if (_sub_graphes[one].root < _sub_graphes[two].root) {
    _sub_graphes[two].root += _sub_graphes[one].root;
    _sub_graphes[one].root = 0;
    _sub_graphes[one].ancestor = two;
  }
  else {
    _sub_graphes[one].root += _sub_graphes[two].root;
    _sub_graphes[two].root = 0;
    _sub_graphes[two].ancestor = one;
  }
}

