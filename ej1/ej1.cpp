#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

#define INF numeric_limits<int>::max()

struct Calle {
    int v;
    int u;
    int longitud;
};

void leer_input(vector<list<pair<int, int>>> &adj,
                vector<list<pair<int, int>>> &adj_inv, list<Calle> &propuestas,
                int &n, int &s, int &t) {
    int cantidad_calles, cantidad_propuestas;
    cin >> n >> cantidad_calles >> cantidad_propuestas >> s >> t;
    --s;
    --t;

    adj = vector<list<pair<int, int>>>(n, list<pair<int, int>>());
    adj_inv = vector<list<pair<int, int>>>(n, list<pair<int, int>>());
    for (int i = 0; i < cantidad_calles; ++i) {
        int desde, hasta, longitud;
        cin >> desde >> hasta >> longitud;
        adj[desde - 1].push_back({hasta - 1, longitud});
        adj_inv[hasta - 1].push_back({desde - 1, longitud});
    }

    for (int i = 0; i < cantidad_propuestas; ++i) {
        int v, u, longitud;
        cin >> v >> u >> longitud;
        propuestas.push_back({v - 1, u - 1, longitud});
    }
}

vector<int> dijkstra(const vector<list<pair<int, int>>> &adj, int x) {
    int n = adj.size();
    vector<bool> procesados(n, false);
    vector<int> distancia(n, INF);
    priority_queue<pair<int, int>> q;

    distancia[x] = 0;
    q.push({0, x});
    while (!q.empty()) {
        int a = q.top().second;
        q.pop();
        if (procesados[a]) continue;
        procesados[a] = true;
        for (auto u : adj[a]) {
            int b = u.first, w = u.second;
            if (distancia[a] + w < distancia[b]) {
                distancia[b] = distancia[a] + w;
                q.push({-distancia[b], b});
            }
        }
    }

    return distancia;
}

int main() {
    int cant_tests;
    cin >> cant_tests;
    for (int c = 0; c < cant_tests; ++c) {
        vector<list<pair<int, int>>> adj;
        vector<list<pair<int, int>>> adj_inv;
        list<Calle> propuestas;
        int s, t, n;
        leer_input(adj, adj_inv, propuestas, n, s, t);

        vector<int> distancias_s = dijkstra(adj, s);
        vector<int> distancias_t = dijkstra(adj_inv, t);

        int min = distancias_s[t];
        for (Calle calle : propuestas) {
            int d =
                distancias_s[calle.v] + calle.longitud + distancias_t[calle.u];
            if (d < min) min = d;

            d = distancias_s[calle.u] + calle.longitud + distancias_t[calle.v];
            if (d < min) min = d;
        }

        cout << min << endl;
    }
}
