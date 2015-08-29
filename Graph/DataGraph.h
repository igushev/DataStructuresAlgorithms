#ifndef DATA_GRAPH_H
#define DATA_GRAPH_H

#include "Graph.h"

template <class NodeKey, class NodeData, class EdgeKey, class EdgeData>
class DataGraph : private Graph {
  struct DataNode {
    DataNode(unsigned id_, const NodeKey& key_, const NodeData& data_): id(id_), key(key_), data(data_) {}
    unsigned id;
    NodeKey key;
    NodeData data;
  };

  struct DataEdge {
    DataEdge(unsigned id_, const EdgeKey& key_, const EdgeData& data_): id(id_), key(key_), data(data_) {}
    unsigned id;
    EdgeKey key;
    EdgeData data;
  };

  std::vector<DataNode> _data_nodes;
  typedef std::pair<NodeKey, unsigned> _node_id_t;
  std::map<NodeKey, unsigned> _nodes_map;

  std::vector<DataEdge> _data_edges;
  typedef std::pair<EdgeKey, unsigned> _edge_id_t;
  std::map<EdgeKey, unsigned> _edges_map;

public:
  struct NodeResult {
    NodeResult(const NodeKey* key_, const NodeData* data_) : key(key_), data(data_) {}
    const NodeKey* key;
    const NodeData* data;
  };

  struct EdgeResult {
    EdgeResult(const EdgeKey* key_, const EdgeData* data_) : key(key_), data(data_) {}
    const EdgeKey* key;
    const EdgeData* data;
  };

  struct NodeEdgeResult {
    NodeEdgeResult(const NodeKey* node_key_, const NodeData* node_data_, const EdgeKey* edge_key_, const EdgeData* edge_data_)
      : node_key(node_key_), node_data(node_data_), edge_key(edge_key_), edge_data(edge_data_) {}
    const NodeKey* node_key;
    const NodeData* node_data;
    const EdgeKey* edge_key;
    const EdgeData* edge_data;
  };

  typedef std::vector<NodeEdgeResult> node_edge_key_data_vector_t;
  typedef std::vector<node_edge_key_data_vector_t> node_edge_key_data_vector_vector_t;

  void ReserveNodes(unsigned size) { _data_nodes.reserve(size); }
  void ReserveEdges(unsigned size) { _data_edges.reserve(size); }

  void PushNode(const NodeKey& key, const NodeData& data);
  void PushEdge(const EdgeKey& key, const EdgeData& data,
    const NodeKey& from, const NodeKey& to, unsigned weight);

  size_t NodesCount() const { return _data_nodes.size(); }
  size_t EdgesCount() const { return _data_edges.size(); }

  node_edge_key_data_vector_t MinimulPathDijkstra(const NodeKey& from, const NodeKey& to) const;
  node_edge_key_data_vector_vector_t MinimulPathsDijkstra(const NodeKey& from, const NodeKey& to, double k = 1.0) const;
};

template <class NodeKey, class NodeData, class EdgeKey, class EdgeData>
void DataGraph<NodeKey, NodeData, EdgeKey, EdgeData>::PushNode(const NodeKey& key, const NodeData& data)
{
  typename std::map<NodeKey, unsigned>::iterator key_it = _nodes_map.find(key);
  if (key_it != _nodes_map.end())
    throw std::runtime_error("The key of node is already in graph");

  unsigned id = _data_nodes.size();
  ReserveNodes(id+1);
  _data_nodes.push_back(DataNode(id, key, data));
  _nodes_map.insert(key_it, _node_id_t(key, id));
}

template <class NodeKey, class NodeData, class EdgeKey, class EdgeData>
void DataGraph<NodeKey, NodeData, EdgeKey, EdgeData>::PushEdge(const EdgeKey& key, const EdgeData& data,
  const NodeKey& from, const NodeKey& to, unsigned weight)
{
  typename std::map<EdgeKey, unsigned>::iterator key_it = _edges_map.find(key);
  if (key_it != _edges_map.end())
    throw std::runtime_error("The key of edge is already in graph");

  typename std::map<NodeKey, unsigned>::iterator from_it = _nodes_map.find(from);
  typename std::map<NodeKey, unsigned>::iterator to_it = _nodes_map.find(to);
  if (from_it == _nodes_map.end() || to_it == _nodes_map.end())
    throw std::runtime_error("One of the keys of nodes are not found");

  unsigned id = Graph::PushEdge(from_it->second, to_it->second, weight);
  if (id != _data_edges.size())
    throw std::runtime_error("The graph has been corrupted");

  _data_edges.push_back(DataEdge(id, key, data));
  _edges_map.insert(key_it, _edge_id_t(key, id));
}

template <class NodeKey, class NodeData, class EdgeKey, class EdgeData>
typename DataGraph<NodeKey, NodeData, EdgeKey, EdgeData>::node_edge_key_data_vector_t
  DataGraph<NodeKey, NodeData, EdgeKey, EdgeData>::MinimulPathDijkstra(const NodeKey& from, const NodeKey& to) const
{
  typename std::map<NodeKey, unsigned>::const_iterator from_it = _nodes_map.find(from);
  typename std::map<NodeKey, unsigned>::const_iterator to_it = _nodes_map.find(to);
  if (from_it == _nodes_map.end() || to_it == _nodes_map.end())
    throw std::runtime_error("One of the keys of nodes are not found");

  node_edge_vector_t low_result = Graph::MinimulPathDijkstra(from_it->second, to_it->second);
  node_edge_key_data_vector_t result;
  result.reserve(low_result.size());
  for (unsigned i = 0; i < low_result.size(); ++i) {
    unsigned node = low_result[i].node;
    const NodeKey* node_key = NULL;
    const NodeData* node_data = NULL;

    unsigned edge = low_result[i].edge;
    const EdgeKey* edge_key = NULL;
    const EdgeData* edge_data = NULL;

    if (node != -1) {
      node_key = &_data_nodes[node].key;
      node_data = &_data_nodes[node].data;
    }
    if (edge != -1) {
      edge_key = &_data_edges[edge].key;
      edge_data = &_data_edges[edge].data;
    }
    result.push_back( NodeEdgeResult(node_key, node_data, edge_key, edge_data) );
  }

  return result;
}

template <class NodeKey, class NodeData, class EdgeKey, class EdgeData>
typename DataGraph<NodeKey, NodeData, EdgeKey, EdgeData>::node_edge_key_data_vector_vector_t
  DataGraph<NodeKey, NodeData, EdgeKey, EdgeData>::MinimulPathsDijkstra(const NodeKey& from, const NodeKey& to, double k) const
{
  typename std::map<NodeKey, unsigned>::const_iterator from_it = _nodes_map.find(from);
  typename std::map<NodeKey, unsigned>::const_iterator to_it = _nodes_map.find(to);
  if (from_it == _nodes_map.end() || to_it == _nodes_map.end())
    throw std::runtime_error("One of the keys of nodes are not found");

  node_edge_vector_vector_t low_result = Graph::MinimulPathsDijkstra(from_it->second, to_it->second, k);
  node_edge_key_data_vector_vector_t result;
  result.reserve(low_result.size());
  for (unsigned i = 0; i < low_result.size(); ++i) {
    node_edge_key_data_vector_t mid_result;
    mid_result.reserve(low_result[i].size());
    for (unsigned j = 0; j < low_result[i].size(); ++j) {
      unsigned node = low_result[i][j].node;
      const NodeKey* node_key = NULL;
      const NodeData* node_data = NULL;

      unsigned edge = low_result[i][j].edge;
      const EdgeKey* edge_key = NULL;
      const EdgeData* edge_data = NULL;

      if (node != -1) {
        node_key = &_data_nodes[node].key;
        node_data = &_data_nodes[node].data;
      }
      if (edge != -1) {
        edge_key = &_data_edges[edge].key;
        edge_data = &_data_edges[edge].data;
      }
      mid_result.push_back( NodeEdgeResult(node_key, node_data, edge_key, edge_data) );
    }
    result.push_back(mid_result);
  }

  return result;
}

#endif
