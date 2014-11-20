#include "GraphWeighed.h"
#include <set>

void dijkstra(int source, const GraphWeighed& g, vector<int>& min_distance, vector<int>& previous)
{
    int n = g.nodes().size();

    min_distance.clear();
    min_distance.resize(n, -1);
    min_distance[source] = 0;

    previous.clear();
    previous.resize(n, -1);

    set< pair<int, int> > vertex_queue;
    vertex_queue.insert(make_pair(min_distance[source], source));
 
    while (!vertex_queue.empty()) 
    {
        int dist = vertex_queue.begin()->first;
        int u = vertex_queue.begin()->second;

        vertex_queue.erase(vertex_queue.begin());

		vector<Edge> neighbors = g.adjacentNodes(u);

        for (int i = 0; i < neighbors.size(); i++)
        {
            int v = neighbors[i].end;
            int weight = neighbors[i].weight;
            int distance_through_u = dist + weight;

		    if (distance_through_u < min_distance[v]) 
		    {
		        vertex_queue.erase(make_pair(min_distance[v], v));
	 
		        min_distance[v] = distance_through_u;
		        previous[v] = u;
		        vertex_queue.insert(make_pair(min_distance[v], v));
		    }
        }
    }
}