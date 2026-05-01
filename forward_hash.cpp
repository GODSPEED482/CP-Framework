#include<bits/stdc++.h>
#define eol '\n'
#define lli long long int
#define FastIO ios_base::sync_with_stdio(0); cin.tie(NULL);
using namespace std;


struct Hasher{
    int sz, mod, p;
    vector<int> fhash;
    vector<int> pk;
    string s;

    Hasher(string& s, int mod, int p): sz(s.size()), mod(mod), p(p){
        this -> s = s;
        fhash.resize(sz), pk.resize(sz);
        fhash[0] = ((s[0] - 'a') + 1)%mod;
        pk[0] = 1;
        for(int i = 1 ; i < sz; i++){
            fhash[i] = (fhash[i - 1]*p + (s[i] - 'a') + 1)%mod;
            pk[i] = (pk[i - 1]*p)%mod;
        }
    }

    int getHash(int l, int r){
        if(l == 0){
            return fhash[r];
        }else{
            return (mod + (fhash[r] - (fhash[l - 1]*pk[r - l + 1])%mod))%mod;
        }
    }
    
    void display(){
        cout<<"\nFhash: ";
        for(auto it: fhash)cout<<it<<" ";
        cout<<endl;
        
        cout<<"Pk: ";
        for(auto it: pk)cout<<it<<" ";
        cout<<endl;
        
    }

};

pair<string, bool> check(Hasher& hs1, Hasher& hs2, int size){
    map<int, int> mp;
    for(int i = 0; i + size - 1 < hs1.sz; i++){
        mp[hs1.getHash(i, i + size - 1)]++;
    }
    for(int i = 0; i + size - 1 < hs2.sz; i++){
        if(mp[hs2.getHash(i, i + size - 1)]){
            return make_pair(hs2.s.substr(i, size), true);
        }
    }

    return make_pair("", false);

}

int main()
{
    FastIO
    string s1 , s2;
    cin >> s1 >> s2;

    Hasher hs1(s1, 1e9 + 7, 31), hs2(s2, 1e9 + 7, 31);
    int lo = 0, hi = min(s1.size(), s2.size()), mid, ans;
    ans = hi;
    string s;

    while(lo <= hi){
        mid = (hi + lo)/2;
        auto cond = check(hs1, hs2, mid);
        if(cond.second){
            s = cond.first;
            ans = mid;
            lo = mid + 1;
        }else{
            hi = mid - 1;
        }
    }

    cout<<ans<<" "<<s<<endl;
    
    return 0;
}