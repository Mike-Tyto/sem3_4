#pragma once

#include "array_sequence.h"
#include "hash_map.h"
#include "hasher.h"
#include "idict.h"
#include "queue.h"
#include "shared.h"
#include "stack.h"
#include <functional>
#include <optional>
#include <queue>
#include <stdexcept>

struct Nothing {
    friend bool operator<(const Nothing& lhs, const Nothing& rhs) {
        return true;
    }

    friend bool operator>(const Nothing& lhs, const Nothing& rhs) {
        return true;
    }

    friend bool operator==(const Nothing& lhs, const Nothing& rhs) {
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const Nothing&) {
        os << "_";
        return os;
    }
};

template <typename T>
concept Iterable = requires(T t) {
    t.begin();
    t.end();
};

template <typename Id, typename T, typename E>
class Graph {
    public:
    struct Node {
        Id id;
        T data;

        Node() {
        }

        Node(Id id, T data) {
            this->id = id;
            this->data = data;
        }

        Node(const Node& other) {
            this->id = other.id;
            this->data = other.data;
        }

        Node(Node&& other) {
            this->id = std::move(other.id);
            this->data = std::move(other.data);
        }

        ~Node() {
        }

        Node& operator=(const Node& other) {
            this->id = other.id;
            this->data = other.data;
            return *this;
        }

        Node& operator=(Node&& other) {
            this->id = std::move(other.id);
            this->data = std::move(other.data);
            return *this;
        }
    };

    struct Edge {
        E data;
        SharedPtr<Node> start;
        SharedPtr<Node> end;

        Edge() {
        }

        Edge(Node* start, Node* end, E data) {
            this->start = start;
            this->end = end;
            this->data = data;
        }

        Edge(SharedPtr<Node> start, SharedPtr<Node> end, E data) {
            this->start = start;
            this->end = end;
            this->data = data;
        }

        Edge(const Edge& other) {
            this->start = other.start;
            this->end = other.end;
            this->data = other.data;
        }

        Edge(Edge&& other) {
            this->start = std::move(other.start);
            this->end = std::move(other.end);
            this->data = std::move(other.data);
        }

        ~Edge() {
        }

        Edge& operator=(const Edge& other) {
            this->start = other.start;
            this->end = other.end;
            this->data = other.data;
            return *this;
        }

        Edge& operator=(Edge&& other) {
            this->start = std::move(other.start);
            this->end = std::move(other.end);
            this->data = std::move(other.data);
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const Edge& edge) {
            os << "data:" << edge.data << " | (" << edge.start << ", " << edge.end << ")";
            return os;
        }

        // Node GetStart() {
        //     return *start;
        // }

        // Node GetEnd() {
        //     return *end;
        // }
    };

    struct Path {

        ArraySequence<Edge> path;

        Path() {
        }

        Path(ArraySequence<Edge>&& path) {
            this->path = std::move(path);
        }

        Path(const Path& other) {
            this->path = other.path;
        }

        Path(Path&& other) {
            this->path = std::move(other.path);
        }

        ~Path() {
        }

        Edge Start() {
            return path.GetFirst();
        }

        Edge End() {
            return path.GetLast();
        }

        friend Path operator+(const Path& lhs, const Path& rhs) {
            return Path(lhs.path.Concat(rhs.path));
        }

        friend std::ostream& operator<<(std::ostream& os, Path& path) {
            // os << &path.path;
            for (Edge& e : path.path) {
                std::cout << "Data: " << e.data << " | (" << e.start->id << ", " << e.end->id << ") ";
            }
            return os;
        }

        // friend Path operator=(const Path& other) {
        //     return Path(other.path);
        // }
    };

    using Adjacency = ArraySequence<Edge>;

    enum Type {
        Directed,
        Undirected
    };

    private:
    HashTable<Id, SharedPtr<Adjacency>>* adjacency;
    HashTable<Id, SharedPtr<Node>>* nodes;
    Type type;

    public:
    Graph() {
        this->adjacency = new HashTable<Id, SharedPtr<Adjacency>>();
        this->nodes = new HashTable<Id, SharedPtr<Node>>();
        this->type = Graph::Type::Directed;
    }

    Graph(Type type) {
        this->adjacency = new HashTable<Id, SharedPtr<Adjacency>>();
        this->nodes = new HashTable<Id, SharedPtr<Node>>();
        this->type = type;
    }

    Graph(
            std::initializer_list<Pair<Id, SharedPtr<Adjacency>>> adjacency,
            std::initializer_list<Pair<Id, SharedPtr<Node>>> nodes
    ) {
        this->adjacency = new HashTable<Id, SharedPtr<Adjacency>>(adjacency);
        this->nodes = new HashTable<Id, SharedPtr<Node>>(nodes);
        this->type = Graph::Type::Directed;
    }

    Graph(
            std::initializer_list<Pair<Id, SharedPtr<Adjacency>>> adjacency,
            std::initializer_list<Pair<Id, SharedPtr<Node>>> nodes,
            Type type
    ) {
        this->adjacency = new HashTable<Id, SharedPtr<Adjacency>>(adjacency);
        this->nodes = new HashTable<Id, SharedPtr<Node>>(nodes);
        this->type = type;
    }

    ~Graph() {
        delete this->adjacency;
        delete this->nodes;
    }

    Type GetType() {
        return type;
    }

    SharedPtr<Node> GetNode(Id id) {
        return this->nodes->get(id);
    }

    void AddNode(Id id, T data) {
        if (!nodes->contains_key(id)) {
            nodes->add(id, new Node(id, data));
            return;
        }
        throw std::invalid_argument("Id already exists");
    }

    void AddNode(Node node) {
        if (!nodes->contains_key(node.id)) {
            nodes->add(node.id, new Node(node));
            return;
        }
        throw std::invalid_argument("Id already exists");
    }

    // container must be iterable of Pair<Id, T>
    template <Iterable container>
    void AddNodes(container args) {
        for (auto& e : args) {
            AddNode(e.first, e.last);
        }
    }

    void AddNodes(std::initializer_list<Pair<Id, T>> args) {
        for (auto& e : args) {
            AddNode(e.first, e.last);
        }
    }

    void AddNodes(std::initializer_list<Node> args) {
        for (auto& e : args) {
            AddNode(e);
        }
    }

    void AddEdge(Id start, Id end, E data) {
        if (!adjacency->contains_key(start)) {
            SharedPtr<Adjacency> newAdj = SharedPtr<Adjacency>::makeShared();
            newAdj->Append(Edge(nodes->get(start), nodes->get(end), data));
            adjacency->add(start, newAdj);
        } else {
            adjacency->get(start)->Append(Edge(nodes->get(start), nodes->get(end), data));
        }

        if (type == Graph::Type::Undirected) {
            AddEdgeOnce(end, start, data);
        }
    }

    void AddEdge(Edge edge) {
        if (!adjacency->contains_key(edge.start->id)) {
            SharedPtr<Adjacency> newAdj = SharedPtr<Adjacency>::makeShared();
            newAdj->Append(edge);
            adjacency->add(edge.start->id, newAdj);
            // adjacency->add(edge.start->id, newAdj);
        } else {
            adjacency->get(edge.start->id)->Append(edge);
        }

        if (type == Graph::Type::Undirected) {
            AddEdgeOnce(edge.end->id, edge.start->id, edge.data);
        }
    }

    // void RemoveEdge(Id start, Id end, E data) {
        
    // }

    // container must be iterable of Edge<Id, T, E>
    template <Iterable container>
    void AddEdges(container args) {
        for (auto& e : args) {
            AddEdge(e);
        }
    }

    void AddEdges(std::initializer_list<Edge> args) {
        for (auto& e : args) {
            AddEdge(e);
        }
    }

    void BFS(Id start, std::function<void(SharedPtr<Node>)> map, IHasher<Id>* hasher = new STLHasher<Id>()) {
        HashTable<Id, Id> visited = HashTable<Id, Id>(hasher);
        Queue<Id> queue;
        queue.Enqueue(start);
        while (!queue.IsEmpty()) {
            Id cur = queue.Dequeue();
            if (!visited.contains_key(cur)) {
                visited.add(cur, cur);
                map(nodes->get(cur));
                if (adjacency->contains_key(cur)) {
                    for (int i = 0; i < adjacency->get(cur)->GetLength(); i++) {
                        queue.Enqueue(adjacency->get(cur)->Get(i).end->id);
                    }
                }
            }
        }
    }

    void DFS(Id start, std::function<void(SharedPtr<Node>)> map, IHasher<Id>* hasher = new STLHasher<Id>()) {
        HashTable<Id, Id> visited = HashTable<Id, Id>(hasher);
        Stack<Id> stack;
        stack.Push(start);
        while (!stack.IsEmpty()) {
            Id cur = stack.Pop();
            if (!visited.contains_key(cur)) {
                visited.add(cur, cur);
                map(nodes->get(cur));
                if (adjacency->contains_key(cur)) {
                    for (int i = 0; i < adjacency->get(cur)->GetLength(); i++) {
                        stack.Push(adjacency->get(cur)->Get(i).end->id);
                    }
                }
            }
        }
    }

    Path Dijkstra(Id start, Id end, IHasher<Id>* hasher = new STLHasher<Id>()) {
        HashTable<Id, std::optional<E>> distance = HashTable<Id, std::optional<E>>(hasher);
        HashTable<Id, Id> shortest = HashTable<Id, Id>(hasher->copy());
        ArraySequence<Id> unvisited;
        ArraySequence<Id> visited;
        SharedPtr<Node> prev = nullptr;

        distance.add(start, E());
        for (auto& e : *this->nodes) {
            unvisited.Append(e.first);
            if (start != e.first) {
                distance.add(e.first, std::nullopt);
            }
        }

        const auto is_unvisited = [&unvisited](Id id) -> bool {
            for (Id curr : unvisited) {
                if (curr == id) {
                    return true;
                }
            }
            return false;
        };

        const auto smallest_node = [&distance, &unvisited, &visited, this, &prev, is_unvisited]() -> std::optional<Id> {
            std::optional<E> min = std::nullopt;
            Id node_id;
            for (Id visited_id : visited) {
                if (this->adjacency->contains_key(visited_id)) {
                    for (Edge& e : *this->adjacency->get(visited_id)) {
                        if (!is_unvisited(e.end->id)) {
                            continue;
                        }
                        Id node = e.end->id;
                        std::optional<E> curr_distance = distance.get(node);
                        if (!curr_distance) {
                            continue;
                        }
                        if (!min) {
                            min = curr_distance;
                            node_id = node;
                            prev = this->nodes->get(visited_id);
                            continue;
                        }
                        if (curr_distance < min) {
                            min = curr_distance;
                            node_id = node;
                            prev = this->nodes->get(visited_id);
                        }
                    }
                }
            }
            return !min ? std::nullopt : std::optional<Id>(node_id);
        };

        std::optional<Id> curr = std::optional<Id>(start);

        while (!unvisited.IsEmpty() && !curr == false) {
            SharedPtr<Node> curr_node = nodes->get(*curr);

            if (this->adjacency->contains_key(*curr)) {
                for (Edge& edge : *(this->adjacency->get(*curr))) {
                    if (!distance.get(edge.end->id)) {
                        Pair<Id, std::optional<E>*> entry = distance.get_entry(edge.end->id);
                        *entry.last = edge.data;
                        continue;
                    }
                    if (edge.data < *distance.get(edge.end->id)) {
                        Pair<Id, std::optional<E>*> entry = distance.get_entry(edge.end->id);
                        *entry.last = edge.data;
                    }
                }
            }

            if (!prev) {
                shortest.add(start, start);
            } else {
                shortest.add(*curr, prev->id);
            }

            if (*curr == end) {
                break;
            }

            int index = 0;
            for (int i = 0; i < unvisited.GetLength(); i++) {
                if (unvisited.Get(i) == curr) {
                    index = i;
                    break;
                }
            }
            unvisited.Remove(index);
            visited.Append(*curr);
            curr = smallest_node();
        }

        const auto edge_from_to = [this](Id start, Id end) -> Edge& {
            if (this->adjacency->contains_key(start)) {
                for (Edge& edge : *this->adjacency->get(start)) {
                    if (edge.end->id == end) {
                        return edge;
                    }
                }
            }
            throw std::invalid_argument("Start is not connected with end");
        };

        Id shortest_id = shortest.get(end);
        Path path;
        path.path.Prepend(edge_from_to(shortest_id, end));
        while (shortest_id != shortest.get(shortest_id)) {
            path.path.Prepend(edge_from_to(shortest.get(shortest_id), shortest_id));
            shortest_id = shortest.get(shortest_id);
        }

        return path;
    }

    private:
    void AddEdgeOnce(Id start, Id end, E data) {
        if (!adjacency->contains_key(start)) {
            SharedPtr<Adjacency> newAdj = SharedPtr<Adjacency>::makeShared();
            newAdj->Append(Edge(nodes->get(start), nodes->get(end), data));
            adjacency->add(start, newAdj);
        } else {
            adjacency->get(start)->Append(Edge(nodes->get(start), nodes->get(end), data));
        }
    }
};
