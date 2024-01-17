#include "graph.h"
#include <iostream>

int main() {
    auto type = Graph<int, int, int>::Type::Directed;
    auto graph = Graph<int, int, int>(
            // {},
            // {
            //     // Pair<int, SharedPtr<Graph<int, int, int>::Node>>{ 1, new Graph<int, int, int>::Node() },
            //     { 1, new Graph<int, int, int>::Node() },
            //     { 2, new Graph<int, int, int>::Node() },
            //     { 3, new Graph<int, int, int>::Node() },
            //     { 4, new Graph<int, int, int>::Node() },
            //     { 5, new Graph<int, int, int>::Node() },
            //     { 6, new Graph<int, int, int>::Node() },
            // }
    );
    graph.AddNodes({
            Pair<int, int> {1, int()},
            Pair<int, int> {2, int()},
            Pair<int, int> {3, int()},
            Pair<int, int> {4, int()},
            Pair<int, int> {5, int()},
            Pair<int, int> {6, int()}
    });

    graph.AddEdges({
            Graph<int, int, int>::Edge {graph.GetNode(1), graph.GetNode(2), 1},
            Graph<int, int, int>::Edge {graph.GetNode(2), graph.GetNode(3), 2},
            Graph<int, int, int>::Edge {graph.GetNode(3), graph.GetNode(4), 3},
            Graph<int, int, int>::Edge {graph.GetNode(4), graph.GetNode(5), 4},
            Graph<int, int, int>::Edge {graph.GetNode(1), graph.GetNode(6), 1},
            // Graph<int, int, int>::Edge {graph.GetNode(6), graph.GetNode(5), 1},
            // Graph<int, int, int>::Edge {graph.GetNode(1), graph.GetNode(5), 1},
    });

    Graph<int, int, int>::Path path = graph.Dijkstra(1, 5);
    std::cout << path << '\n';
    // for (Graph<int, Nothing, Nothing>::Edge e : path.path) {
    //     std::cout << "Data: " << e.data << " | (" << e.start->id << ", " << e.end->id << ")\n";
    // }

    // std::cout << *graph.ShortestPath(1, 5) << std::endl;
    //
    // auto path = *graph.ShortestPath(1, 5);
    //
    // for (int i = 0; i < path.GetLength(); i++) {
    //         std::cout << path.Get(i).start->id << " -> " << path.Get(i).end->id;
    //         if (i < path.GetLength() - 1) {
    //             std::cout << " -> ";
    //         }
    //     }
    return 0;
}
