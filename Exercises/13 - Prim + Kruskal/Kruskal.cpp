#include "GraphWeighed.h"
#include <set>
#include <algorithm>

struct Link
{
	int start;
	int end;
	int weight;

	bool operator < (const Link& l) const
    {
        return (weight < l.weight);
    }
};

bool kruskal(const GraphWeighed& g, vector<Link>& result)
{
	vector< set<int> > spanningTrees;

	int nodeCount = g.nodes().size();

	if (nodeCount > 1)
	{
		vector<Link> graphLinks;

		vector<int> graphNodes = g.nodes();

		for (int i = 0; i < graphNodes.size(); i++)
		{
			vector<Edge> adjNodes = g.adjacentNodes(graphNodes[i]);
			for (int j = 0; j < adjNodes.size(); j++)
			{
				Link temp;
				temp.start = graphNodes[i];
				temp.end = adjNodes[j].end;
				temp.weight = adjNodes[j].weight;
				graphLinks.push_back(temp);
			}
		}

		sort(graphLinks.begin(), graphLinks.end());

		while (!graphLinks.empty())
		{
			Link t = graphLinks[0];
			graphLinks.erase(graphLinks.begin());

			int startSetId = -1;
			int endSetId = -1;

			for (int i = 0; i < spanningTrees.size(); i++)
			{
				for (set<int>::iterator it = spanningTrees[i].begin(); it != spanningTrees[i].end(); ++it)
				{
					if (*it == t.start)
					{
						startSetId = i;
					}
					else if (*it == t.end)
					{
						endSetId = i;
					}
				}
			}

			if (startSetId == -1 && endSetId == -1) //not found in trees, make a new tree
			{
				set<int> temp;
				temp.insert(t.start);
				temp.insert(t.end);
				spanningTrees.push_back(temp);

				result.push_back(t);
			}
			else if (startSetId == -1) //add to end set id tree
			{
				spanningTrees[endSetId].insert(t.start);

				result.push_back(t);
			}
			else if (endSetId == -1) //add to start set id tree
			{
				spanningTrees[startSetId].insert(t.end);

				result.push_back(t);
			}
			else if (startSetId != endSetId) //found in 2 different trees, merge them and delete the second tree
			{
				int minId = (startSetId < endSetId) ? startSetId : endSetId;
				int maxId = (startSetId > endSetId) ? startSetId : endSetId;

				spanningTrees[minId].insert(spanningTrees[maxId].begin(), spanningTrees[maxId].end());

				spanningTrees.erase(spanningTrees.begin() + maxId);

				result.push_back(t);
			}
		}

		if (nodeCount != spanningTrees[0].size())
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