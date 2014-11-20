#include "GraphWeighed.h"

bool GraphWeighed::addNode(int node)
{
	if (hasNode(node))
		return false;
		
	//Add node

	Edge temp;
	temp.end = node;
	temp.weight = 0;

	vector<Edge> v;
	v.push_back(temp);
	adj.push_back(v);

	return true;
}

bool GraphWeighed::removeNode(int node)
{
	if (!hasNode(node))
		return false;

	//Erase node

	for (int i = 0; i < adj.size(); i++)
		if (adj[i][0].end == node)
		{
			adj.erase(adj.begin() + i);
			break;
		}

	//Erase all links to that node

	for (int i = 0; i < adj.size(); i++)
		for (int j = 0; j < adj[i].size(); j++)
			if (adj[i][j].end == node)
			{
				adj[i].erase(adj[i].begin() + j);
				break;
			}

	return true;
}

bool GraphWeighed::addLink(int start, int end, int weight)
{
	if (hasLink(start, end))
		return false;

	//Add nodes if they don't exist

	addNode(start);
	addNode(end);

	//Add link

	for (int i = 0; i < adj.size(); i++)
		if (adj[i][0].end == start)
		{
			Edge temp;
			temp.end = end;
			temp.weight = weight;
			adj[i].push_back(temp);
			break;
		}

	return true;
}

bool GraphWeighed::removeLink(int start, int end)
{
	if (!hasLink(start, end))
		return false;

	//Remove link

	for (int i = 0; i < adj.size(); i++)
		if (adj[i][0].end == start)
		{
			for (int j = 0; j < adj[i].size(); j++)
				if (adj[i][j].end == end)
				{
					adj[i].erase(adj[i].begin() + j);
					break;
				}
			break;
		}

	return true;
}

bool GraphWeighed::isEmpty() const
{
	return adj.size() == 0;
}

bool GraphWeighed::hasNode(int node) const
{
	for (int i = 0; i < adj.size(); i++)
		if (adj[i][0].end == node)
			return true;

	return false;
}

bool GraphWeighed::hasLink(int start, int end) const
{
	for (int i = 0; i < adj.size(); i++)
		if (adj[i][0].end == start)
			for (int j = 0; j < adj[i].size(); j++)
				if (adj[i][j].end == end)
					return true;

	return false;
}

vector<int> GraphWeighed::nodes() const
{
	vector<int> result;

	for (int i = 0; i < adj.size(); i++)
		result.push_back(adj[i][0].end);

	return result;
}

vector<Edge> GraphWeighed::adjacentNodes(int node) const
{
	vector<Edge> result;

	if (hasNode(node))
		for (int i = 0; i < adj.size(); i++)
			if (adj[i][0].end == node)
				for (int j = 1; j < adj[i].size(); j++)
					result.push_back(adj[i][j]);

	return result;
}
