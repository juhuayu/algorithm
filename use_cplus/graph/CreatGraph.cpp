#include <iostream>
#include <vector>
#include "GraphStructure.cpp"
using namespace std;

class CreatGraph
{
private:
public:

  Graph* creat(vector<vector<int>> matrix);
};

Graph* CreatGraph::creat(vector<vector<int>> matrix) {
  Graph* graph = new Graph();
  for(int i=0; i<matrix.size(); i++) {
    int from = matrix[i][0];
    int to = matrix[i][1];
    int weight = matrix[i][2];
    if(!(graph->nodes.find(from) != graph->nodes.end())) { // 没遇到过该点
      graph->nodes.insert(pair<int, Node*>(from, new Node(from)));
    }
    if(!(graph->nodes.find(to) != graph->nodes.end())) {
      graph->nodes.insert(pair<int, Node*>(to, new Node(to)));
    }
    Node* fromNode = graph->nodes.at(from);
    Node* toNode = graph->nodes.at(to);
    Edge* newEdge = new Edge(weight, fromNode, toNode);
    fromNode->nexts.push_back(toNode);
    fromNode->out++;
    toNode->in++;
    fromNode->edges.push_back(newEdge);
    graph->edges.insert(newEdge);
  }
  return graph;
} 















