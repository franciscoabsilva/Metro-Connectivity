#include <iostream>
#include <vector>

using namespace std;

void readInput(int& n, int& m, int& l, vector<vector<int>>& connections) {
    cin >> n >> m >> l;
    connections.resize(m, vector<int>(3));

    for (int i = 0; i < m; i++) {
        cin >> connections[i][0] >> connections[i][1] >> connections[i][2];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, l;
    vector<vector<int>> connections;

    readInput(n, m, l, connections);

    cout << "Estações: " << n << ", Ligações: " << m << ", Linhas: " << l << "\n";
    for (int i = 0; i < m; i++) {
        cout << connections[i][0] << " " << connections[i][1] << " " << connections[i][2] << "\n";
    }
    return 0;
}