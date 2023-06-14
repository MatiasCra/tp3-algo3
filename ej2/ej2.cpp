#include <iostream>
#include <limits>
#include <queue>
#include <vector>

#define INF std::numeric_limits<int>::max() / 3

using namespace std;

// Implementación de maxflow de
// https://cp-algorithms.com/graph/edmonds_karp.html
int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while ((new_flow = bfs(s, t, parent))) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

enum Preferencia { PRIM = 0, KRUSKAL = 1 };

void leer_input() {
    capacity = vector<vector<int>>(n, vector<int>(n, 0));
    adj = vector<vector<int>>(n);
    int cant_relaciones;
    cin >> cant_relaciones;

    vector<int> preferencias(n - 2, PRIM);
    for (int i = 0; i < n - 2; ++i) {
        int aux;
        cin >> aux;
        preferencias[i] = aux;
    }

    int s = n - 2;
    int t = n - 1;
    for (int i = 0; i < n - 2; ++i) {
        if (preferencias[i] == KRUSKAL) {
            adj[s].emplace_back(i);
            adj[i].emplace_back(s);
            capacity[s][i] = 1;
        } else {
            adj[i].emplace_back(t);
            adj[t].emplace_back(i);
            capacity[i][t] = 1;
        }
    }

    for (int i = 0; i < cant_relaciones; ++i) {
        int v, u;
        cin >> v >> u;
        --v;
        --u;
        adj[v].emplace_back(u);
        adj[u].emplace_back(v);
        if (preferencias[v] == PRIM and preferencias[u] == KRUSKAL) swap(v, u);
        capacity[v][u] = 1;

        if (preferencias[v] == preferencias[u]) capacity[u][v] = 1;
    }
}

int main() {
    // IO rápido con cin/cout
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> n) {
        if (n == 0) break;

        n += 2;
        int s = n - 2;
        int t = n - 1;
        leer_input();

        int flujo = maxflow(s, t);
        cout << flujo << "\n";
    }

    return 0;
}
