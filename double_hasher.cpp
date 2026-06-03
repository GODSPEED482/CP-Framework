#include<bits/stdc++.h>
#define eol '\n'
#define lli long long int
#define FastIO ios_base::sync_with_stdio(0); cin.tie(NULL);
using namespace std;

struct Hasher{
    vector<int> fHash, rHash, pk; 
    int sz, mod, p;
    string s;

    Hasher(){

    }

    Hasher(string &s, int mod, int p): mod(mod), p(p), sz(s.length()){
        this->s = s;
        fHash.resize(sz), rHash.resize(sz), pk.resize(sz);
        fHash[0] = ((s[0] - 'a') + 1)%mod;
        rHash[sz - 1] = ((s[sz - 1] - 'a') + 1)%mod;
        pk[0] = 1;
        for(int i = 1; i < sz; i++){
            pk[i] = (pk[i - 1]*p)%mod;
            fHash[i] = ((fHash[i - 1]*p)%mod + (s[i] - 'a' + 1))%mod;
            rHash[sz - i - 1] = ((rHash[sz - i]*p)%mod  + (s[sz - i - 1] - 'a' + 1))%mod;
        }
    }
    int getForwardHash(int i, int j){
        if(i == 0) return fHash[j];
        return ((fHash[j] - (fHash[i - 1]*pk[j - i + 1])%mod)%mod + mod)%mod;
    }
    int getReverseHash(int i, int j){
        if(j == sz - 1) return rHash[i];
        return ((rHash[i] - (rHash[j + 1]*pk[j - i + 1])%mod)%mod + mod)%mod;     
    }
};

struct DoubleHasher{
    Hasher hs1, hs2;
    int sz;
    string s;

    DoubleHasher(string &s): sz(s.length()), s(s){
        hs1 = Hasher(s, 1e9 + 7, 31);
        hs2 = Hasher(s, 1e9 + 7, 37);
    }  
    pair<int, int> getForwardHash(int i, int j){
        return make_pair(hs1.getForwardHash(i, j), hs2.getForwardHash(i, j));
    }
    pair<int, int> getReverseHash(int i, int j){
        return make_pair(hs1.getReverseHash(i, j), hs2.getReverseHash(i, j));
    }
};

pair<string, bool> check(DoubleHasher& hs1, DoubleHasher& hs2, int size){
    map<pair<int, int>, int> mp;
    for(int i = 0; i + size - 1 < hs1.sz; i++){
        mp[hs1.getForwardHash(i, i + size - 1)]++;
    }
    for(int i = 0; i + size - 1 < hs2.sz; i++){
        if(mp[hs2.getForwardHash(i, i + size - 1)]){
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

    DoubleHasher hs1(s1), hs2(s2);
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
    
    // return 0;/
    return 0;
}