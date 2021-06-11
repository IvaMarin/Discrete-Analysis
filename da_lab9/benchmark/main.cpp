#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>

using namespace std;
using TDuration = chrono::microseconds;

const int INF = 1e9 + 1;

struct TEdge {          
    pair<int, int> vertices;  
    int capacity;       
};

// Breadth-first search
int BFS(vector<vector<int>> &residualNetwork, vector<int> &parent, vector<vector<int>> &adj, int s, int t) {
    // filling an array to remeber the path
	// "-1" indicates unvisited vertices
	// "-2" indicates source
	fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

	// creates a queue of pairs (vertex, minimum residual capacity) for BFS
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

		// for every vertex in Adjacency List for current vertex
        for (int next : adj[cur]) {
			// if vertex is unvisited and still has capacity
            if (parent[next] == -1 && residualNetwork[cur][next]) {
                parent[next] = cur; // add vertex next to the path
                int minFlow = min(flow, residualNetwork[cur][next]);
                if (next == t)
                    return minFlow;
                q.push({next, minFlow});
            }
        }
    }

    return 0;
}

bool DFS(vector<vector<int>> &residualNetwork, vector<vector<int>> &adj, vector<int> &parent, int cur, int t) {
    if (cur == t)
        return true;

    for (int next : adj[cur]) {
        if (residualNetwork[cur][next] && parent[next] == -1) {
            parent[next] = cur;
            if (DFS(residualNetwork, adj, parent, next, t))
                return true;
        }
    }

    return false;
}

long long FordFulkerson(vector<vector<int>> &residualNetwork, vector<vector<int>> &adj, int s, int t) {
    long long maxFlow = 0;
    vector<int> parent(t + 1);
    int flow;
    /*
    while ((flow = BFS(residualNetwork, parent, adj, s, t))) {
        maxFlow += flow;

		// go from sink to source
        int cur = t;
        while (cur != s) {
            int prev = parent[cur]; // using path established by BFS
            residualNetwork[prev][cur] -= flow; // subtract flow capacity of an edge along the path
            residualNetwork[cur][prev] += flow; // add flow capacity along the reversed edge
            cur = prev;
        }
    }

    return maxFlow;
    */
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

    int cur, prev;
    while (DFS(residualNetwork, adj, parent, s, t)) {
        flow = INF;

        cur = t;
        while (cur != s) {
            prev = parent[cur];
            flow = min(flow, residualNetwork[prev][cur]);
            cur = prev;
        }

        cur = t;
        while (cur != s) {
            prev = parent[cur];
            residualNetwork[prev][cur] -= flow;
            residualNetwork[cur][prev] += flow;
            cur = prev;
        }

        maxFlow += flow;

        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
    }
    return maxFlow;
}

int main() {
    chrono::time_point<chrono::high_resolution_clock> start, end;
    int64_t timeStamp = 0;
    start = chrono::high_resolution_clock::now();

    int n; // number of vertices
    int m; // number of lines
    cin >> n >> m;

    // creates Residual Capacity matrix nxn filled with zeros
    vector<vector<int>> residualGraph(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        residualGraph[i].resize(n + 1);
    }

	// creates Adjacency List filled with zeros
	vector<vector<int>> adjacencyList(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        adjacencyList[i].resize(n + 1);
    }

    TEdge edge;
    for (int i = 0; i < m; ++i) { 
        cin >> edge.vertices.first >> edge.vertices.second >> edge.capacity;

		// fills Residual Capacity matrix with elements
    	// where [u][v] element stores residual capacity of an edge from vertex u to vertex v
        residualGraph[edge.vertices.first][edge.vertices.second] = edge.capacity;

		// fills Adjacency List with elements
    	// where every element has a list of connected vertices, assuming the graph is undirected
		adjacencyList[edge.vertices.first][edge.vertices.second] = edge.vertices.second;
		adjacencyList[edge.vertices.second][edge.vertices.first] = edge.vertices.first;
    }   

	// writes maximal flow or 0 if it doesn't exist
	cout << FordFulkerson(residualGraph, adjacencyList, 1, n) << endl;

    /*
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << residualGraph[i][j] << ' ';
        cout << endl;
    }
	cout << endl;
	for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << adjacencyList[i][j] << ' ';
        cout << endl;
    }
	*/

    end = chrono::high_resolution_clock::now();
    timeStamp += chrono::duration_cast<TDuration>(end - start).count();
    cout << "Time: " << timeStamp << " microsec" << endl;
    
    return 0;
}