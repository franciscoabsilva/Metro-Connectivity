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
    void resetNode() {
        seen = false;
        distance = -1;
    }
};


Node* getNode(unordered_map<int, Node*>& graph, int id) {
    if (graph.find(id) == graph.end()) {
        graph[id] = new Node(id);
    }
    return graph[id];
}

void readInput(vector<unordered_set<int>>& stationsGraph, vector<int>& lineFrequency) {
    int id1, id2, idLine;
    while (cin >> id1 >> id2 >> idLine) {
        // O QUE FAZER SE ID1 OU ID 2 FOR MAIOR QUE STATIONS COUNT ?? TODO
        if (stationsGraph[id1].find(idLine) == stationsGraph[id1].end()) {
            lineFrequency[idLine]++;
        }
        if (stationsGraph[id2].find(idLine) == stationsGraph[id2].end()) {
            lineFrequency[idLine]++;
        }
        stationsGraph[id1].insert(idLine);
        stationsGraph[id2].insert(idLine);
    }
}

int buildLinesGraph(vector<unordered_set<int>>& stationsGraph, unordered_map<int, Node*>& linesGraph, int stationsCount) {
    for (int station = 1; station <= stationsCount; station++) {
        
        // If there is a station with no connections
        if (stationsGraph[station].empty()) {
            return 1;
        }
        if (stationsGraph[station].size() > 1) {
            for (int currentLine : stationsGraph[station]) {
                Node* lineNode = getNode(linesGraph, currentLine);
                for (int connectedLine : stationsGraph[station]) {
                    if (connectedLine != currentLine) {
                        Node* neighborNode = getNode(linesGraph, connectedLine);
                        lineNode->addNeighbor(neighborNode);
                        // NAO VALE APENA ADD O VIZINHO PQ ELE EVENTUALMENTE CHEGA LÁ
                        // ISTO É SO PRA MARTA VER, APAGAR TODO
                    }
                }
            }
        }
    }
    return 0;
}

int calculateDistance(unordered_map<int, Node*>& linesGraph, Node* startLine, int linesCount) {
    queue<Node*> queue;
    startLine->distance = 0;
    queue.push(startLine);
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

    // If there are lines that are not connected
    if (seen < linesCount) {
        return -1;
    }
    for (pair<const int, Node*>& pair : linesGraph) {
        Node* node = pair.second;
        if (node->distance > maxDistance) {
            maxDistance = node->distance;
        }
    }
    return maxDistance;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int stationsCount, connectionsCount, linesCount;
    cin >> stationsCount >> connectionsCount >> linesCount;

    // If there are not enough connections
    if (stationsCount > connectionsCount + 1) {
        cout << "-1\n";
        return 0;
    }

    // If there is only one line
    if(linesCount <= 1) {
        cout << "0\n";
        return 0;
    }
    
    vector<unordered_set<int>> stationsGraph(stationsCount + 1);
    vector<int> lineFrequency(linesCount + 1, 0);
    readInput(stationsGraph, lineFrequency);

    for (int i = 1; i <= linesCount; i++) {
        // If there is a line that connects all stations
        if (lineFrequency[i] == stationsCount) {
            cout << "0\n";
            return 0;
        }
        // PENSEI NESTE CASO, NAO SEI SE QUERO RETORNAR 0 OU -1 OU
        // SE É SEQUER POSSIVEL, SE FOR 0 POSSO METER NA CONDIÇÃO DE CIMA
        // TODO
        /*if (lineFrequency[i] == 0) {
            cout << "0\n";
            return 0;
        }*/
    }
    

    unordered_map<int, Node*> linesGraph;
    if (buildLinesGraph(stationsGraph, linesGraph, stationsCount)) {
        cout << "-1\n";
        return 0;
    }

    int maxDistance = 0;
    for (int startLine = 1; startLine <= linesCount; startLine++) {
        int distance = calculateDistance(linesGraph, linesGraph[startLine], linesCount);
        
        if (distance == -1) {
            cout << "-1\n";
            return 0;
        }
        maxDistance = max(maxDistance, distance);
        if (maxDistance == linesCount-1) {
            break;
        }
        for (pair<const int, Node*>& pair : linesGraph) {
            Node* node = pair.second;
            node->resetNode();
        }
    }
    
    cout << maxDistance << "\n";

    return 0;
}