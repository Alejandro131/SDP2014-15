#include "Graph.h"

bool Graph::addNode(int node)
{
	if (hasNode(node))
		return false;
		
	//Add node

	vector<int> v;
	v.push_back(node);
	adj.push_back(v);

	return true;
}

bool Graph::removeNode(int node)
{
	if (!hasNode(node))
		return false;

	//Erase node

	for (int i = 0; i < adj.size(); i++)
		if (adj[i][0] == node)
		{
			adj.erase(adj.begin() + i);
			break;
		}

	//Erase all links to that node

	for (int i = 0; i < adj.size(); i++)
		for (int j = 0; j < adj[i].size(); j++)
			if (adj[i][j] == node)
			{
				adj[i].erase(adj[i].begin() + j);
				break;
			}

	return true;
}

bool Graph::addLink(int start, int end)
{
	if (hasLink(start, end))
		return false;

	//Add nodes if they don't exist

	addNode(start);
	addNode(end);

	//Add link

	for (int i = 0; i < adj.size(); i++)
		if (adj[i][0] == start)
		{
			adj[i].push_back(end);
			break;
		}

	return true;
}

bool Graph::removeLink(int start, int end)
{
	if (!hasLink(start, end))
		return false;

	//Remove link

	for (int i = 0; i < adj.size(); i++)
		if (adj[i][0] == start)
		{
			for (int j = 0; j < adj[i].size(); j++)
				if (adj[i][j] == end)
				{
					adj[i].erase(adj[i].begin() + j);
					break;
				}
			break;
		}

	return true;
}

bool Graph::isEmpty() const
{
	return adj.size() == 0;
}

bool Graph::hasNode(int node) const
{
	for (int i = 0; i < adj.size(); i++)
		if (adj[i][0] == node)
			return true;

	return false;
}

bool Graph::hasLink(int start, int end) const
{
	for (int i = 0; i < adj.size(); i++)
		if (adj[i][0] == start)
			for (int j = 0; j < adj[i].size(); j++)
				if (adj[i][j] == end)
					return true;

	return false;
}

vector<int> Graph::nodes() const
{
	vector<int> result;

	for (int i = 0; i < adj.size(); i++)
		result.push_back(adj[i][0]);

	return result;
}

vector<int> Graph::adjacentNodes(int node) const
{
	vector<int> result;

	if (hasNode(node))
		for (int i = 0; i < adj.size(); i++)
			if (adj[i][0] == node)
				for (int j = 1; j < adj[i].size(); j++)
					result.push_back(adj[i][j]);

	return result;
}
