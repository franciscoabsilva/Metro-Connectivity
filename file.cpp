#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    int id;
    bool seen = false;
    int distance = -1;
    vector<Node*> neighbors;

    Node(int id) : id(id) {}
    void addNeighbor(Node* neighbor) { // pode valer a pena usar um set
        for (Node* n : neighbors) {
            if (n->id == neighbor->id) {
                return;
            }
        }   
        neighbors.push_back(neighbor);
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
    vector<Node*> queue;
    Node* start = graph[1];
    start->distance = 0;
    queue.push_back(start);
    int maxDistance = 0;
    int seen = 0;
    while (!queue.empty()) {
        Node* current = queue.front();
        current->seen = true;
        queue.erase(queue.begin());
        seen++;
        for (Node* neighbor : current->neighbors) {
            if (neighbor->seen) {
                continue;
            }
            if (neighbor->distance == -1 || neighbor->distance > current->distance + 1) {
                neighbor->distance = current->distance + 1;
                queue.push_back(neighbor);
                maxDistance = max(maxDistance, neighbor->distance);
            }
        }
    }
    if(seen < numNodes) {
        return -1;
    }
    return(maxDistance / 2 - 1);
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