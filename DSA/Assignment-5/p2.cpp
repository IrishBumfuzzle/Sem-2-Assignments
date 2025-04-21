#include <bits/stdc++.h>
using namespace std;
#define vvi vector<vector<int>>
#define vi vector<int>
#define pii pair<int, int>
#define ll long long
#define vvl vector<vector<ll>>
#define vl vector<ll>
#define pll pair<ll, ll>
#define fo(i, j, k) for(int i = j; i < k; i++)
#define endl '\n'
#define mod 1000000000

bool comp_x(vi node1, vi node2){
    return node1[1] < node2[1] ? true : false;
}
bool comp_y(vi node1, vi node2){
    return node1[2] < node2[2] ? true : false;
}
bool comp_z(vi node1, vi node2){
    return node1[3] < node2[3] ? true : false;
}
bool comp(vi node1, vi node2){
    return node1[2] < node2[2] ? true : false;
}

class Disjoint {
    vi parent, rank;
public:
    Disjoint(int n) {
        parent.resize(n);
        rank.resize(n);
        fo (i, 0, n){
            rank[i] = 1;
            parent[i] = i;
        }
    }
    int par(int i){
        return parent[i] == i ? i : (parent[i] = par(parent[i]));
    }

    void uni(int x, int y){
        int par1 = par(x), par2 = par(y);
        if(par1 != par2){
            if(rank[par1] < rank[par2]) parent[par1] = par2;
            else if(rank[par1] > rank[par2]) parent[par2] = par1;
            else parent[par1] = par2, rank[par2]++;
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vvi nodes(n, vi(4));
    vvi edges(m, vi(3));
    fo(i, 0, n){
        nodes[i][0] = i;
        cin >> nodes[i][1] >> nodes[i][2] >> nodes[i][3];
    }
    fo(i, 0, m){
        edges[i][2] = 0;
        cin >> edges[i][0] >> edges[i][1];
        edges[i][0]--, edges[i][1]--;
    }

    auto nodes_x = nodes;
    sort(nodes_x.begin(), nodes_x.end(), comp_x);
    auto nodes_y = nodes;
    sort(nodes_y.begin(), nodes_y.end(), comp_y);
    auto nodes_z = nodes;
    sort(nodes_z.begin(), nodes_z.end(), comp_z);
    

    fo(i, 0, n-1){
        // grid[nodes_x[i][0]].push_back({nodes_x[i+1][0], nodes_x[i+1][1] - nodes_x[i][1]});
        // grid[nodes_x[i+1][0]].push_back({nodes_x[i][0], nodes_x[i+1][1] - nodes_x[i][1]});

        // grid[nodes_y[i][0]].push_back({nodes_y[i+1][0], nodes_y[i+1][2] - nodes_y[i][2]});
        // grid[nodes_y[i+1][0]].push_back({nodes_y[i][0], nodes_y[i+1][2] - nodes_y[i][2]});
        
        // grid[nodes_z[i][0]].push_back({nodes_z[i+1][0], nodes_z[i+1][3] - nodes_z[i][3]});
        // grid[nodes_z[i+1][0]].push_back({nodes_z[i][0], nodes_z[i+1][3] - nodes_z[i][3]});
        edges.push_back({nodes_x[i][0] ,nodes_x[i+1][0], nodes_x[i+1][1] - nodes_x[i][1]});
        edges.push_back({nodes_y[i][0], nodes_y[i+1][0], nodes_y[i+1][2] - nodes_y[i][2]});
        edges.push_back({nodes_z[i][0], nodes_z[i+1][0], nodes_z[i+1][3] - nodes_z[i][3]});
    }
    sort(edges.begin(), edges.end(), comp);

    Disjoint dis(n);
    long long cost = 0, count = 0;
    for (auto &e : edges) {
        int x = e[0], y = e[1], w = e[2];
        
        if (dis.par(x) != dis.par(y)) {
            dis.uni(x, y);
            cost += w;
            if (++count == n - 1) break;
        }
    }
    cout << cost << endl;


    return 0;
}