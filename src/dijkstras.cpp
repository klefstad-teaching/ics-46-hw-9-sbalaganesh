#include "../src/dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int n = G.numVertices;
    vector<int> distance(n, INF);
    //distance.assign(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);
    //visited.assign(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, source});
    distance[source] = 0;

    while (!pq.empty()){
        pair<int, int> curr = pq.top();
        pq.pop();
        int u = curr.second;
        if (visited[u]){
            continue;
        }
        visited[u] = true;

        for (const Edge& edge : G[u]){
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && ((distance[u] + weight) < distance[v])){
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;

}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> shortest_path;
    if (distances[destination] == INF){
        return shortest_path;
    }
    if (previous[destination] == -1){
        return shortest_path;
    }
    for (int curr = destination; curr != -1; curr = previous[curr]){
        //if(distances[curr] != 0){
        shortest_path.push_back(curr);
        //}
    }
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}


void print_path(const vector<int>& v, int total){
    for (auto vertex : v){
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    std::cout << "Total cost is " << total << std::endl;
}