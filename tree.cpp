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
    vector<int> par;
    vector<vector<int>> adjacency;
    vector<int> depth; 
    Tree(int n = 1){
        this -> n = n;
        root = 0;
        par.assign(n + 1, 0);
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
        par[node] = parent;
        depth[node] = currentDepth;
        for(auto child: adjacency[node]){
            if(child != parent){
                dfs(node, child, currentDepth + 1);
            }
        }
    }

    int getDiameter(){
        dfs(0, 1, 0);
        int farthestNode = max_element(depth.begin()+1, depth.end()) - depth.begin();
        dfs(0 , farthestNode, 0);
        int diameter = *max_element(depth.begin()+1, depth.end());

        return diameter;
    }

    int getDepth(int parent, int node, int currentLevel, int queryLevel){
        if(currentLevel == queryLevel) return 1;
        int ans = 0;
        for(auto child: adjacency[node]){
            if(child != parent){
                ans += getDepth(node, child, currentLevel + 1, queryLevel);
            }
        }

        return ans;
    }

    int getNumberOfDiametersFromOneCenter(){
        int diameter = getDiameter();
        int endpoint = max_element(depth.begin() + 1, depth.end()) - depth.begin();
        int radius = diameter/2;
        int center = endpoint;
        for(int i = 1; i <= radius; i++ ){
            center = par[center];
        }

        int squareSum , sum;
        squareSum = sum = 0;
        for(auto child: adjacency[center]){
            int temp = getDepth(center, child, 1, radius);
            squareSum += temp*temp;
            sum += temp;
        }

        int numberOfDiameters = (sum*sum - squareSum)/2;
        return numberOfDiameters;
    }

    int getNumberOfDiametersFromTwoCenters(){
        int diameter = getDiameter();
        int endpoint = max_element(depth.begin() + 1, depth.end()) - depth.begin();
        int radius = diameter/2;
        int center1 = endpoint, center2;

        for(int i = 1; i <= radius; i++ ){
            center1 = par[center1];
        }

        center2 = par[center1];

        int pathCollections[2] = {0, 0};
        pathCollections[0] = getDepth(center1, center2, 0, radius);
        pathCollections[1] = getDepth(center2, center1, 0, radius);

        return pathCollections[1]*pathCollections[0];
    }

    int getNumberOfDiameters(){
        if(n == 1) return 1;
        int diameter = getDiameter();
        if(diameter%2 == 0) return getNumberOfDiametersFromOneCenter();
        else return getNumberOfDiametersFromTwoCenters();
    }


};

void solve(){
    //code here...
    int n;
    cin >> n;

    Tree tt(n);

    cout<<tt.getNumberOfDiameters()<<endl;
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