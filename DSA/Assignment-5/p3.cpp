#include <bits/stdc++.h>
using namespace std;
#define vvi vector<vector<int>>
#define vi vector<int>
#define pii pair<int, int>
#define ll long long
#define vvl vector<vector<ll>>
#define vl vector<ll>
#define pll pair<ll, ll>
#define fo(i, j, k) for (int i = j; i < k; i++)
#define endl '\n'
#define mod 1000000000

class Compare
{
public:
    bool operator()(vl a, vl b)
    {
        if(a[1] != b[1])
            return a[1] > b[1] ? true : false;
        return a[2] > b[2] ? true : false;
    }
};

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<vector<int>>> grid(n);
    fo(i, 0, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        grid[a].push_back({b, c, -1});
        grid[b].push_back({a, c, -1});
    }
    
    vl dist(n, __INT64_MAX__);
    dist[0] = 0;
    
    priority_queue<vector<ll>, vvl, Compare> pq;
    pq.push({0, 0, -1});
    
    while(!pq.empty()){
        vl top = pq.top();
        pq.pop();
        ll curr = top[0], type = top[2];
        
        for(auto &i: grid[curr]){
            if(dist[i[0]] > dist[curr] + i[1]){
                dist[i[0]] = dist[curr] + i[1];
                pq.push({i[0], dist[i[0]], i[2]});
            }
        }
    }
    
    fo(i, 0, k)
    {
        int a, b;
        cin >> a >> b;
        a--;
        grid[a].push_back({0, b, i});
        grid[0].push_back({a, b, i});
    }
    
    pq.push({0, 0, -1});
    vi used(k, 0);
    vi prev(n, -1);
    
    while(!pq.empty()){
        vl top = pq.top();
        pq.pop();
        ll curr = top[0], type = top[2];

        for(auto &i: grid[curr]){
            if(dist[i[0]] > dist[curr] + i[1]){
                dist[i[0]] = dist[curr] + i[1];
                prev[i[0]] = i[2];
                pq.push({i[0], dist[i[0]], i[2]});
            }
        }
    }

    int count = 0;
    fo(i, 0, n) if(prev[i] > -1) count++;
    cout << k - count;
}