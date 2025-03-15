#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) 
{
    vector<int> distances(G.numVertices, INF);
    distances[source] = 0;
    
    previous.resize(G.numVertices, -1);
    
    vector<bool> visited(G.numVertices, false);
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    pq.push({0, source});
    
    while (!pq.empty()) 
    {
        int u = pq.top().second;
        pq.pop();
        
        if (visited[u]) 
        {
            continue;
        }
        
        visited[u] = true;
        
        for (const Edge& edge : G[u]) 
        {
            int v = edge.dst;
            int weight = edge.weight;
            
            if (!visited[v] && distances[u] != INF && distances[u] + weight < distances[v]) 
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) 
{
    vector<int> path;
    stack<int> temp_path;
    
    if (previous[destination] == -1 && destination != 0) 
    {
        return path;
    }
    
    for (int vertex = destination; vertex != -1; vertex = previous[vertex]) 
    {
        temp_path.push(vertex);
    }
    
    while (!temp_path.empty()) 
    {
        path.push_back(temp_path.top());
        temp_path.pop();
    }
    
    return path;
}

void print_path(const vector<int>& path, int total) 
{
    for (size_t i = 0; i < path.size(); ++i) 
    {
        cout << path[i];
        if (i < path.size() - 1) 
        {
            cout << " ";
        }
    }
    cout << endl;
    
    cout << "Total cost is " << total << endl;
}