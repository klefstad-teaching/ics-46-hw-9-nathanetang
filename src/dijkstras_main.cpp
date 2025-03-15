#include "dijkstras.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    
    string filename = argv[1];
    Graph G;
    
    try 
    {
        file_to_graph(filename, G);
        
        int source = 0;
        vector<int> previous;
        
        vector<int> distances = dijkstra_shortest_path(G, source, previous);
        
        for (int destination = 0; destination < G.numVertices; ++destination) 
        {
            vector<int> path = extract_shortest_path(distances, previous, destination);
            
            if (!path.empty()) 
            {
                print_path(path, distances[destination]);
            } 
            else if (destination == source) 
            {
                cout << source << endl;
                cout << "Total cost is 0" << endl;
            }
            else
            {
                cout << "No path exists from " << source << " to " << destination << endl;
            }
        }
    }
    catch (const exception& e) 
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}