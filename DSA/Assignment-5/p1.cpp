#include <bits/stdc++.h>
using namespace std;
#define vvi vector<vector<int>>
#define vi vector<int>
#define pii pair<int, int>
#define ll long long
#define vvl vector<vector<ll>>
#define vl vector<ll>
#define pll pair<ll, ll>fwf
#define fo(i, j, k) for(int i = j; i < k; i++)
#define endl '\n'
#define mod 1000000000

int main(){
    int n, m;
    cin >> n >> m;

    vvi grid(n);
    vi in_deg(n, 0);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--, b--;
        grid[b].push_back(a);
        in_deg[a]++;
    }
    priority_queue<int> pq;
    fo(i, 0, n){
        if(in_deg[i] == 0) pq.push(i);
    }
    vi result;

    while(!pq.empty()){
        int top = pq.top();
        pq.pop();
        result.push_back(top);

        for(auto i : grid[top]){
            if(--in_deg[i] == 0) pq.push(i);
        }
    }

    vi out(n);
    

    fo(i, 0, n){
        out[result[i]] = n-i;
    }
    fo(i, 0, n) cout << out[i] << ' '; 

    
}