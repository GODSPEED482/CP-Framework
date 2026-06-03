#include<bits/stdc++.h>
#define eol '\n'
#define lli long long int
#define FastIO ios_base::sync_with_stdio(0); cin.tie(NULL);
using namespace std;

struct Node{
    int prefix;
    // vector<int> wordIndex;
    Node* child[26];

    Node(){
        this -> prefix = 0;
        for(int i = 0; i < 26 ; i++ ){
            this -> child[i] = NULL;
        }
    }
};

struct Trie{
    Node* root;
    Trie(){
        root = new Node;
    }

    void insert(string& s){
        // cout<<"Hello\n";
        Node* curr = root;
        curr -> prefix++;
        for(auto it: s){
            int index = (it - 'a');
            // cout<<"Adding ["<<it<<", "<<index<<"]\n";
            if(curr -> child[index] == NULL) curr -> child[index] = new Node;
            curr = curr -> child[index];
            curr -> prefix++;
        }
        // cout<<"Successfully added: "<<s<<" to trie \n";
    }

    void erase(string& s){
        Node* curr = root;
        curr -> prefix--;
        for(auto it: s){
            int index = (it - 'a');
            curr = curr -> child[index];
            curr -> prefix--;
            // curr -> wend.push_back(index);
        }
    }

    int find(string &s){
        Node* curr = root;
        for(auto it: s){
            curr = curr -> child[it - 'a'];
            if(curr == NULL) return 0;
        }
        return curr -> prefix;
    }
};



int main()
{
    FastIO
    Trie tr;
    int q;
    cin >> q;
    while(q--){
        string query, val;
        cin >> query >> val;
        // cout<<
        if(query == "add"){
            tr.insert(val);
        }else{
            cout<<tr.find(val)<<endl;
        }
    }
    return 0;
}