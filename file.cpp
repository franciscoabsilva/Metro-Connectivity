#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

struct Node {
    int id;
    bool seen = false;
    int distance = -1;
    unordered_set<Node*> neighbors;

    Node(int id) : id(id) {}
    void addNeighbor(Node* neighbor) {
        neighbors.insert(neighbor);
    }
};


Node* getNode(unordered_map<int, Node*>& graph, int id) {
    if (graph.find(id) == graph.end()) {
        graph[id] = new Node(id);
    }
    return graph[id];
}

void readInput(int stations, int lines, unordered_map<int, Node*>& graph) {
    int id1, id2, idLine;
    
    while (cin >> id1 >> id2 >> idLine) {
        Node* station1 = getNode(graph, id1);
        Node* station2 = getNode(graph, id2);
        Node* line = getNode(graph, stations + idLine);
        station1->addNeighbor(line);
        station2->addNeighbor(line);
        line->addNeighbor(station1);
        line->addNeighbor(station2);        
    }
}

int calculateDistance(unordered_map<int, Node*>& graph, int numNodes) {
    queue<Node*> queue;
    Node* start = graph[1];
    start->distance = 0;
    queue.push(start);
    int maxDistance = 0;
    int seen = 0;
    while (!queue.empty()) {
        Node* current = queue.front();
        current->seen = true;
        queue.pop();
        seen++;
        for (Node* neighbor : current->neighbors) {
            if (neighbor->seen) {
                continue;
            }
            if (neighbor->distance == -1 || neighbor->distance > current->distance + 1) {
                neighbor->distance = current->distance + 1;
                queue.push(neighbor);
            }
        }
    }
    if(seen < numNodes) {
        return -1;
    }
    for (auto& pair : graph) {
        Node* node = pair.second;
        if (node->distance > maxDistance) {
            maxDistance = node->distance;
        }
    }
        for (const auto& pair : graph) {
        Node* node = pair.second;
        cout << "Node " << node->id << " has distance " << node->distance << endl;
    }
    cout << "Max distance: " << maxDistance << endl;
    return((maxDistance + 1) / 2 - 1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int stations, connections, lines;
    cin >> stations >> connections >> lines;
    if (connections < stations - 1) {
        cout << "-1\n";
        return 0;
    }
    if(lines <= 1) {
        cout << "0\n";
        return 0;
    }
    int numNodes = stations + lines;
    unordered_map<int, Node*> graph;
    readInput(stations, lines, graph);
    cout << calculateDistance(graph, numNodes) << "\n";


    return 0;
}