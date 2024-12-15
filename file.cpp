#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    int id;
    int seen = 0;
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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int stations, connections, lines;
    cin >> stations >> connections >> lines;
    if (connections < stations - 1) {
        cout << "-1\n";
        return 0;
    }

    unordered_map<int, Node*> graph;
    readInput(connections, lines, graph);
    // print graph
    cout << "Graph:\n";
    for (auto it = graph.begin(); it != graph.end(); it++) {
        cout << it->first << ": ";
        for (Node* n : it->second->neighbors) {
            cout << n->id << " ";
        }
        cout << "\n";
    }
    return 0;
}