// **************************************************************************
//  File       [cyclebreaker.cpp]
//  Author     [Yu-Heng Lai]
//  Synopsis   [The main program of 2025 spring Algorithm PA3]
// **************************************************************************
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <sstream>
#include <numeric>
#include <fstream>
#include <functional>

#include "../lib/tm_usage.h"
using namespace std;

void help_message() {
    cout << "Usage: ./bin/cb <input_file> <output_file>" << endl;
}

struct UnionFind {
    vector<int> parent;
    vector<int> rank;
    UnionFind(int size) : parent(size), rank(size, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
};

int uf_find(UnionFind &uf, int x) {
    if(uf.parent[x] != x) uf.parent[x] = uf_find(uf,uf.parent[x]);
    return uf.parent[x];
}

void uf_union_sets(UnionFind &uf, int x, int y) {
    int rootX = uf_find(uf, x);
    int rootY = uf_find(uf, y);
    if (rootX != rootY) {
        if (uf.rank[rootX] > uf.rank[rootY]) uf.parent[rootY] = rootX;
        else if(uf.rank[rootX] < uf.rank[rootY]) uf.parent[rootX] = rootY;
        else{
            uf.parent[rootY] = rootX;
            uf.rank[rootX]++;
        }
    }
}

bool dfs_search(int u, int target, vector<char> &visited, const vector<vector<int>> &G) {
    if (u == target) return true;
    visited[u] = 1;
    for (int next : G[u]) {
        if (!visited[next] && dfs_search(next, target, visited, G))
            return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        help_message();
        return 0;
    }
    fstream fin(argv[1]);
    fstream fout(argv[2], ios::out);
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    char mode;
    fin >> mode;
    int n, m, junk;
    fin >> n >> m;
    vector<pair<int, pair<int, int>>> edges_test;
    vector<pair<int,int>> edges[201];

    for (int k = 0; k < m; ++k) {
        int u, v, w;
        fin >> u >> v >> w;
        edges[w + 100].push_back({u, v});
        edges_test.push_back({w, {u, v}});
    }
    sort(edges_test.begin(), edges_test.end(), [](auto &a, auto &b) {
        return a.first > b.first;
    });

    if (mode == 'u') {
        if (m == n - 1) {
            fout << 0;
            fin >> junk;
            tmusg.periodStart();
            tmusg.getPeriodUsage(stat);
            cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
            cout << "memory: " << stat.vmPeak << "KB" << endl;
            return 0;
        }
        fin >> junk;
        tmusg.periodStart();

        UnionFind uf(n+1);
        vector<pair<int, pair<int, int>>> removed_edges;
        int total_weight = 0;
        for (auto &edge : edges_test) {
            int w = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            if (uf_find(uf, u) != uf_find(uf, v)) {
                uf_union_sets(uf, u, v);
            } else {
                removed_edges.push_back(edge);
                total_weight += w;
            }
        }

        if (removed_edges.empty()) {
            fout << "0" << endl;
        } else {
            fout << total_weight << endl;
            for (auto &e : removed_edges) {
                fout << e.second.first << " " << e.second.second << " " << e.first << endl;
            }
        }

    } else {
        if (m == n - 1) {
            fout << 0;
            fin >> junk;
            tmusg.periodStart();
            tmusg.getPeriodUsage(stat);
            cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
            cout << "memory: " << stat.vmPeak << "KB" << endl;
            return 0;
        }
        fin >> junk;
        tmusg.periodStart();

        UnionFind uf(n+1);
        vector<vector<int>> G(n);
        vector<pair<int, pair<int, int>>> deferred_edges;
        for (int b = 200; b >= 0; b--) {
            int w = b - 100;
            for (auto &uv : edges[b]) {
                int u = uv.first, v = uv.second;
                if (uf_find(uf, u) != uf_find(uf, v)) {
                    uf_union_sets(uf, u, v);
                    G[u].push_back(v);
                } else {
                    deferred_edges.push_back({w, {u, v}});
                }
            }
        }

        vector<pair<int, pair<int, int>>> removed_edges;
        int total_weight = 0;
        for (auto &edge : deferred_edges) {
            if (edge.first < 0) {
                removed_edges.push_back(edge);
                total_weight += edge.first;
            } else {
                vector<char> vis(n, 0);
                if (dfs_search(edge.second.second, edge.second.first, vis, G)) {
                    removed_edges.push_back(edge);
                    total_weight += edge.first;
                } else {
                    G[edge.second.first].push_back(edge.second.second);
                }
            }
        }

        if (removed_edges.empty()) {
            fout << "0" << endl;
        } else {
            fout << total_weight << "\n";
            for (auto &e : removed_edges) {
                fout << e.second.first << " " << e.second.second << " " << e.first << "\n";
            }
        }
    }


    tmusg.getPeriodUsage(stat);
    cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout << "memory: " << stat.vmPeak << "KB" << endl;
    return 0;
}
