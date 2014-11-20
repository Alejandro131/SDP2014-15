#include "GraphWeighed.h"
#include <set>

struct Link
{
	int start;
	int end;
	int weight;
};

bool prim(const GraphWeighed& g, vector<Link>& result)
{
	set<int> nodes;

	int nodeCount = g.nodes().size();
	if (nodeCount > 1)
	{
		int currentNode = g.nodes()[0];
		nodes.insert(currentNode);

		bool addedNewLink = true;

		while (addedNewLink)
		{
			addedNewLink = false;

			vector<Link> temp;

			for (set<int>::iterator it = nodes.begin(); it != nodes.end(); ++it)
			{
				vector<Edge> adjNodes = g.adjacentNodes[*it];
				for (int i = 0; i < adjNodes.size(); i++)
				{
					if (nodes.find(adjNodes[i].end) == nodes.end()) //element is not present in spanning tree
					{
						Link t;
						t.start = *it;
						t.end = adjNodes[i].end;
						t.weight = adjNodes[i].weight;
						temp.push_back(t);
					}
				}
			}

			if (temp.size() != 0)
			{
				int minIndex = 0;
				int minWeight = temp[0].weight;

				for (int i = 1; i < temp.size(); i++)
				{
					if (temp[i].weight < minWeight)
					{
						minIndex = i;
						minWeight = temp[i].weight;
					}
				}

				result.push_back(temp[minIndex]);
				nodes.insert(temp[minIndex].end);

				addedNewLink = true;
			}
		}

		if (nodeCount != nodes.size())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}