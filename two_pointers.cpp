#include<bits/stdc++.h>
#define eol '\n'
#define lli long long int
#define FastIO ios_base::sync_with_stdio(0); cin.tie(NULL);
using namespace std;

struct DataDashboard{
    queue<int> ds;
    int k;
    
    DataDashboard(int k) : k(k){
    }

    void push(int element){

        if(element == 0){
            if(k == 0) cerr<<"Error: Queue can't take anymore!!\n";
            else k--;
        };
        ds.push(element);
    }
    void pop(){
        if(ds.empty()) cerr<<"Error: Can't pop, Queue empty!!\n";
        if(ds.front() == 0) k++;
        ds.pop();
    }

    bool full(int nextElement){
        return k == 0 && nextElement == 0;
    }

    int size(){
        return ds.size();
    }

    bool empty(){
        return ds.empty();
    }
};

struct TwoPointer{
    int start, end;
    //some structure and space
    vector<int>& space;
    DataDashboard ds;
    //Answer
    int& ans;

    TwoPointer(vector<int>& space, int k, int& ans): space(space), ans(ans), ds(DataDashboard(k)){

        start = -1, end = 0;
    }

    bool condition(){
        return end < space.size();
    }
    bool consumeCondition(){
        //Some condition 
        return (start + 1 < space.size()) && !ds.full(space[start + 1]);
    }
    void consume(){
        
        start++;
        // cout<<"Consuming Element: "<<space[start]<<endl;
        //feed the new element into the structure;
        if(start < space.size()) ds.push(space[start]);
        else cerr<<"Error: Search Space Limit Exceeded!!\n";
    }
    void update(){
        ans = max(ans, (int)ds.size());
    }
    void pop(){
        //release the new element from the structure
        if(end > start){
            end++;
            start = end - 1;
        }
        else if(ds.empty()){
            cerr<<"Error: pointers and structure are not in sync!!"<<endl;
        }
        else{
            ds.pop();
            end++;
        }
    }

};

void solve(){
    int n, k;
    cin >> n >> k;

    vector<int> v(n, 0);
    for(auto &it: v) cin >> it;
    int ans = 0;

    TwoPointer tp(v, k, ans);

    while(tp.condition()){
        // cout<<tp.consumeCondition()<<endl;
        while(tp.consumeCondition()){
            tp.consume();
        }
        tp.update();

        tp.pop();
    }

    cout<<ans<<endl;

}

int main()
{
    FastIO
    solve();
    return 0;
}