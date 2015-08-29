/**
  \file Graph.h
  \author Eduard Igushev visit <www.igushev.com> e-mail: <first name at last name dot com>
  \brief Graph C++ implementation

  The implementation provides depth-first traversal, breadth-first traversal,
  creating adjacency list and adjacency maxtrix,
  Prim-Dijkstra’s Minimul Spanning Tree Algorithm, Kruskal’s Minimul Spanning Tree Algorithm
  and Dijkstra’s Minimul Path Algorithm.

  Warranty and license
  The implementation is provided “as it is” with no warranty.
  Any private and commercial usage is allowed.
  Keeping the link to the source is required.
  Any feedback is welcomed :-)
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stdexcept>
#include <algorithm>

class Graph {
  struct Edge {
    Edge(unsigned id_, unsigned from_, unsigned to_, unsigned weight_)
      : id(id_), from(from_), to(to_), weight(weight_) {}
    unsigned id;
    unsigned from;
    unsigned to;
    unsigned weight;
    bool operator<(const Edge& edge) const { return weight < edge.weight; }
  };

  struct EdgePointerComparator {
    bool operator()(const Edge* left, const Edge* right) { return (left->weight < right->weight); }
  };

  unsigned _nodes_count;
  std::vector<Edge> _edges;

public:
  struct NodeEdge {
    NodeEdge(unsigned node_, unsigned edge_) : node(node_), edge(edge_) {}
    unsigned node;
    unsigned edge;
  };
  typedef std::vector<NodeEdge> node_edge_vector_t;
  typedef std::vector<node_edge_vector_t> node_edge_vector_vector_t;

  typedef std::vector<unsigned> id_vector_t;
  typedef std::vector<id_vector_t> id_vector_vector_t;
  typedef std::vector<std::list<unsigned> > adjacency_list_t;
  typedef std::vector<std::vector<unsigned> > adjacency_matrix_t;

  Graph() : _nodes_count(0), _uptodate_adjacency_list(false), _uptodate_adjacency_matrix(false), _uptodate_mstpd_edges(false), _uptodate_mstk_edges(false) {}

  void ReserveNodes(unsigned size) { if (_nodes_count < size) _nodes_count = size; }
  void ReserveEdges(unsigned size) { _edges.reserve(size); }
  unsigned PushEdge(unsigned from, unsigned to, unsigned weight);

  size_t NodesCount() const { return _nodes_count; }
  size_t EdgesCount() const { return _edges.size(); }

  template <class Visitor>
  void DepthFirstTraversal(Visitor* visitor) const;
  template <class Visitor>
  void BreadthFirstTraversal(Visitor* visitor) const;
  const adjacency_list_t& AdjacencyList() const;
  const adjacency_matrix_t& AdjacencyMaxtrix() const;
  const id_vector_t& MinimulSpanningTreePrimDijkstra() const;
  const id_vector_t& MinimulSpanningTreeKruskal() const;
  node_edge_vector_t MinimulPathDijkstra(unsigned from, unsigned to) const;
  node_edge_vector_vector_t MinimulPathsDijkstra(unsigned from, unsigned to, double k = 1.0) const;

private:
  template <class Visitor>
  class DepthFirstTraversaler {
  public:
    DepthFirstTraversaler(const Graph& graph, Visitor* visitor);
    void Execute(unsigned node);
  private:
    const Graph& _graph;
    std::vector<bool> _visited_nodes;
    Visitor* _visitor;
  };

  class Subgraphes {
    struct SubgraphItem {
      SubgraphItem() : root(1), ancestor(-1) {}
      unsigned root;
      unsigned ancestor;
    };
    std::vector<SubgraphItem> _sub_graphes;

  public:
    Subgraphes(unsigned size) { _sub_graphes.resize(size); }
    unsigned FindRoot(unsigned node) const;
    void Unite(unsigned one, unsigned two);
  };

  struct PathToNode {
    PathToNode(unsigned from_node_, unsigned using_edge_, unsigned long total_weight_to_)
      : from_node(from_node_), using_edge(using_edge_), total_weight_to(total_weight_to_) {}
    unsigned from_node;
    unsigned using_edge;
    unsigned long total_weight_to;
  };

  typedef std::vector<PathToNode> PathsToNode;

  class MinimulPathsResult {
  public:
    MinimulPathsResult(const std::vector<PathsToNode>& paths_to_nodes)
      : _paths_to_nodes(paths_to_nodes) {}
    node_edge_vector_vector_t Process(unsigned path_from, unsigned path_to);

  private:
    node_edge_vector_vector_t _Process(unsigned node);
    const std::vector<PathsToNode>& _paths_to_nodes;
    unsigned _path_from;
  };

  mutable bool _uptodate_adjacency_list;
  mutable bool _uptodate_adjacency_matrix;
  mutable bool _uptodate_mstpd_edges;
  mutable bool _uptodate_mstk_edges;

  mutable adjacency_list_t _adjacency_list;
  mutable adjacency_matrix_t _adjacency_matrix;
  mutable id_vector_t _mstpd_edges;
  mutable id_vector_t _mstk_edges;
};

template <class Visitor>
void Graph::DepthFirstTraversal(Visitor* visitor) const
{
  if (!_nodes_count)
    return;

  AdjacencyList();

  DepthFirstTraversaler<Visitor> traversaler(*this, visitor);
  traversaler.Execute(0);
}

template <class Visitor>
void Graph::BreadthFirstTraversal(Visitor* visitor) const
{
  if (!_nodes_count)
    return;

  AdjacencyList();

  std::vector<bool> queued_nodes;
  queued_nodes.resize(_nodes_count, false);
  std::queue<unsigned> nodes_queue;
  nodes_queue.push(0);
  queued_nodes[0] = true;

  while (nodes_queue.size()) {
    unsigned next = nodes_queue.front();
    nodes_queue.pop();
    visitor->visit(next);
    std::list<unsigned>& add_list = _adjacency_list[next];
    for (typename std::list<unsigned>::const_iterator add_node = add_list.begin();
      add_node != add_list.end(); ++add_node)
      if (!queued_nodes[*add_node]) {
        nodes_queue.push(*add_node);
        queued_nodes[*add_node] = true;
      }
  }
}

template <class Visitor>
Graph::DepthFirstTraversaler<Visitor>::DepthFirstTraversaler(const Graph& graph, Visitor* visitor)
  : _graph(graph), _visitor(visitor)
{
  _visited_nodes.resize(_graph._nodes_count);
}

template <class Visitor>
void Graph::DepthFirstTraversaler<Visitor>::Execute(unsigned node)
{
  if (_visited_nodes[node])
    return;

  _visitor->visit(node);
  _visited_nodes[node] = true;

  std::list<unsigned>& visit_list = _graph._adjacency_list[node];
  for (typename std::list<unsigned>::const_iterator visit_node = visit_list.begin();
    visit_node != visit_list.end(); ++visit_node)
    Execute(*visit_node);
}

#endif
