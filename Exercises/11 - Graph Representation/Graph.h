#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using namespace std;

class Graph
{
	public:
		bool addNode(int node);
		bool removeNode(int node);

		bool addLink(int start, int end);
		bool removeLink(int start, int end);

		bool isEmpty() const;

		bool hasNode(int node) const;
		bool hasLink(int start, int end) const;

		vector<int> nodes() const;
		vector<int> adjacentNodes(int node) const;
	private:
		vector< vector<int> > adj;
};

#endif