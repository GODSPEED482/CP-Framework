// Write your code here
// You can set your Template at profile settings [https://maang.in/profile/template-code]
#include<bits/stdc++.h>
#define lli long long 
#define int long long
#define eol '\n'
#define FastIO ios_base::sync_with_stdio(0); cin.tie(NULL);
using namespace std;

struct Tree{
    int root;
    int n;
    int rank = 0;
    int LOG = 18;
    vector<vector<int>> par;
    vector<vector<int>> adjacency;
    vector<int> depth; 
    
    
    
    Tree(int n = 1){
        this -> n = n;
        root = 0;
        //Initialize the binary lift parent vector
        par.assign(n + 1, vector<int>(LOG, 0));
        adjacency.resize(n + 1);
        depth.assign(n + 1, 0);
        // edges.resize(2*n);
        for(int i = 1; i < n ; i++ ){
            int a, b;
            cin >> a >> b;
            adjacency[a].push_back(b);
            adjacency[b].push_back(a);
        }

    }

    void dfs(int parent, int node, int currentDepth){
        if(parent == 0) root = node;
        par[node][0] = parent;// 2^0th = 1st parent of node = parent

        for(int i = 1; i < LOG;i++){
            par[node][i] = par[par[node][i - 1]][i - 1]; // 2^(i-1) + 2^(i - 1) = 2^ith parent of node
        }
        depth[node] = currentDepth;
        for(auto child: adjacency[node]){
            if(child != parent){
                dfs(node, child, currentDepth + 1);
            }
        }
    }

    int getKthAncestor(int node, int k){
        for(int i = LOG - 1; i >= 0; i--){
            if(k & (1 << i)){
                node = par[node][i];
            }
        }
        return node;
    }

    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = LOG - 1; i >= 0; i--) {
            if ((diff & (1 << i))) u = par[u][i];
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--)
            if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
        return par[u][0];
    }

    void displayBinaryLift(){
        for(int i = 0; i <= n ; i++ ){
            cout<<i<<": ";
            for(auto it: par[i]){
                cout<<it<<" ";
            }
            cout<<"\n";
        }
    }


};

void solve(){
    //code here...
    int n;
    cin >> n;

    Tree tt(n);
    int node1, node2;
    tt.dfs(0, 1, 0);
    tt.displayBinaryLift();
    cout<<endl;
    while(1){
        cin >> node1 >> node2;
        cout<< tt.getLCA(node1, node2)<< endl;
    }

    // cout<<tt.getNumberOfDiameters()<<endl;
}



signed main()
{
    FastIO
    lli t = 1;
    // cin>>t;
    while(t--){
        solve();
    }
    return 0;
}