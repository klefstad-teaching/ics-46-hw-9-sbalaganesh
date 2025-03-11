#include "../src/dijkstras.cpp"

int main(){
    Graph g;
    file_to_graph("src/small.txt", g);
    vector<int> previous;
    vector<int> distance = dijkstra_shortest_path(g, 0, previous);
    print_path(extract_shortest_path(distance, previous, 0), distance[0]);
    print_path(extract_shortest_path(distance, previous, 1), distance[1]);
    print_path(extract_shortest_path(distance, previous, 2), distance[2]);
    print_path(extract_shortest_path(distance, previous, 3), distance[3]);
}