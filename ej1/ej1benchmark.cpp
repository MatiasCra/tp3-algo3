#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

#define INF numeric_limits<int>::max() / 3

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

void leer_input_lista(list<Calle> &calles, list<Calle> &calles_inv,
                      list<Calle> &propuestas, int &n, int &s, int &t) {
    int cantidad_calles, cantidad_propuestas;
    cin >> n >> cantidad_calles >> cantidad_propuestas >> s >> t;
    --s;
    --t;

    calles = list<Calle>();
    calles_inv = list<Calle>();
    for (int i = 0; i < cantidad_calles; ++i) {
        int desde, hasta, longitud;
        cin >> desde >> hasta >> longitud;
        Calle c = {desde - 1, hasta - 1, longitud};
        Calle c_inv = {hasta - 1, desde - 1, longitud};
        calles.emplace_back(c);
        calles_inv.emplace_back(c_inv);
    }

    for (int i = 0; i < cantidad_propuestas; ++i) {
        int v, u, longitud;
        cin >> v >> u >> longitud;
        propuestas.push_back({v - 1, u - 1, longitud});
    }
}

vector<int> dijkstra_ralo(const vector<list<pair<int, int>>> &adj, int x) {
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

vector<int> dijkstra_denso(const vector<list<pair<int, int>>> &adj, int x) {
    int n = adj.size();
    vector<bool> procesados(n, false);
    vector<int> distancia(n, INF);

    vector<pair<int, int>> q;
    q.reserve(n);

    distancia[x] = 0;
    q.push_back({0, x});
    while (!q.empty()) {
        auto it = max_element(q.begin(), q.end());
        int a = it->second;
        q.erase(it);

        if (procesados[a]) continue;
        procesados[a] = true;
        for (auto u : adj[a]) {
            int b = u.first, w = u.second;
            if (distancia[a] + w < distancia[b]) {
                distancia[b] = distancia[a] + w;
                q.push_back({-distancia[b], b});
            }
        }
    }

    return distancia;
}

vector<int> bellman_ford(const list<Calle> &edges, int x, int n) {
    vector<int> distancia(n, INF);
    bool parar = false;
    distancia[x] = 0;
    for (int i = 0; not parar and i < n; i++) {
        parar = true;
        for (auto e : edges) {
            auto [a, b, w] = e;
            int dist = distancia[a] + w;
            if (dist < distancia[b]) {
                distancia[b] = dist;
                parar = false;
            }
        }
    }

    return distancia;
}

enum Metodo { DIJKSTRA_RALO = 0, DIJKSTRA_DENSO = 1, BELLMAN_FORD = 2 };

int main(int argc, char **argv) {
    if (argc < 2) return 1;

    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    int m = atoi(argv[1]);

    int cant_tests;
    cin >> cant_tests;
    for (int c = 0; c < cant_tests; ++c) {
        list<Calle> propuestas;
        int s, t, n;
        vector<int> distancias_s;
        vector<int> distancias_t;

        if (m == DIJKSTRA_RALO) {
            vector<list<pair<int, int>>> adj;
            vector<list<pair<int, int>>> adj_inv;
            leer_input(adj, adj_inv, propuestas, n, s, t);

            auto t1 = high_resolution_clock::now();
            distancias_s = dijkstra_ralo(adj, s);
            distancias_t = dijkstra_ralo(adj_inv, t);
            auto t2 = high_resolution_clock::now();
            duration<double, std::milli> ms_double = t2 - t1;
            double tiempo = ms_double.count() / 1000;
            cout << tiempo << endl;

        } else if (m == DIJKSTRA_DENSO) {
            vector<list<pair<int, int>>> adj;
            vector<list<pair<int, int>>> adj_inv;
            leer_input(adj, adj_inv, propuestas, n, s, t);

            auto t1 = high_resolution_clock::now();
            distancias_s = dijkstra_denso(adj, s);
            distancias_t = dijkstra_denso(adj_inv, t);
            auto t2 = high_resolution_clock::now();
            duration<double, std::milli> ms_double = t2 - t1;
            double tiempo = ms_double.count() / 1000;
            cout << tiempo << endl;
        } else if (m == BELLMAN_FORD) {
            list<Calle> calles;
            list<Calle> calles_inv;
            leer_input_lista(calles, calles_inv, propuestas, n, s, t);

            auto t1 = high_resolution_clock::now();
            distancias_s = bellman_ford(calles, s, n);
            distancias_t = bellman_ford(calles_inv, t, n);
            auto t2 = high_resolution_clock::now();
            duration<double, std::milli> ms_double = t2 - t1;
            double tiempo = ms_double.count() / 1000;
            cout << tiempo << endl;
        } else {
            return 1;
        }

        int min = distancias_s[t];
        for (Calle calle : propuestas) {
            int d =
                distancias_s[calle.v] + calle.longitud + distancias_t[calle.u];
            if (d < min) min = d;

            d = distancias_s[calle.u] + calle.longitud + distancias_t[calle.v];
            if (d < min) min = d;
        }

        if (min < INF)
            cout << min << endl;
        else
            cout << -1 << endl;
    }

    return 0;
}
