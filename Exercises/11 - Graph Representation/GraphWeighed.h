#ifndef GRAPH_WEIGHED_H
#define GRAPH_WEIGHED_H

#include <vector>

using namespace std;

struct Edge
{
	int end;
	int weight;
};

class GraphWeighed
{
	public:
		bool addNode(int node);
		bool removeNode(int node);

		bool addLink(int start, int end, int weight);
		bool removeLink(int start, int end);

		bool isEmpty() const;

		bool hasNode(int node) const;
		bool hasLink(int start, int end) const;

		vector<int> nodes() const;
		vector<Edge> adjacentNodes(int node) const;
	private:
		vector< vector<Edge> > adj;
};

#endif