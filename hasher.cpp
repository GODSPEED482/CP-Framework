#include<bits/stdc++.h>
#define eol '\n'
#define lli long long int
#define FastIO ios_base::sync_with_stdio(0); cin.tie(NULL);
using namespace std;


struct Hasher{
    int sz, mod, p;
    vector<int> fhash, rhash;
    vector<int> pk;
    string s;

    Hasher(){

    }

    Hasher(string& s, int mod, int p): sz(s.size()), mod(mod), p(p){
        this -> s = s;
        fhash.resize(sz), pk.resize(sz), rhash.resize(sz);
        fhash[0] = ((s[0] - 'a') + 1)%mod;
        rhash[sz - 1] = ((s[sz - 1] - 'a') + 1)%mod;
        pk[0] = 1;

        for(int i = 1 ; i < sz; i++){
            fhash[i] = (fhash[i - 1]*p + (s[i] - 'a') + 1)%mod;
            pk[i] = (pk[i - 1]*p)%mod;
        }
        for(int i = sz - 2 ; i >= 0; i--){
            rhash[i] = (rhash[i + 1]*p + (s[i] - 'a') + 1)%mod;
        }
    }

    int getForwardHash(int l, int r){
        if(l == 0){
            return fhash[r];
        }else{
            return (mod + (fhash[r] - (fhash[l - 1]*pk[r - l + 1])%mod))%mod;
        }
    }
    int getReverseHash(int l, int r){
        if(r == sz - 1){
            return rhash[l];
        }else{
            return (mod + (rhash[l] - (rhash[r + 1]*pk[r - l + 1])%mod))%mod;
        }
    }

    pair<int, int> getDoubleHash(int l, int r){
        return make_pair(getForwardHash(l, r), getReverseHash(l, r));
    }
    
    void display(){
        cout<<"\nFhash: ";
        for(auto it: fhash)cout<<it<<" ";
        cout<<endl;

        cout<<"Rhash: ";
        for(auto it: rhash)cout<<it<<" ";
        cout<<endl;        
        
        cout<<"Pk: ";
        for(auto it: pk)cout<<it<<" ";
        cout<<endl;
        
    }

} hs1;

int size_ = 0;

void display(int i, int size){
    cout<<"["<<i<<"..."<<i + size - 1<<"]"<<": ";
}

bool cmp(int i, int j){
    int lo = 1, hi = size_;
    if(hs1.getForwardHash(i, i)!=hs1.getForwardHash(j, j)) return hs1.getForwardHash(i , i) < hs1.getForwardHash(j, j);
    int ans = lo;
    int mid;
    int hash1, hash2;
    while(lo <= hi){
        mid = (lo+ hi)/2;
        // cout<<i + mid - 1<<" "<<j + mid - 1<<eol;
        hash1 = hs1.getForwardHash(i, i +mid - 1), hash2 = hs1.getForwardHash(j, j + mid - 1);
        // cout<<endl<<mid<<endl;
        // display(i, mid), cout<<hash1<<endl;
        // display(j, mid), cout<<hash2<<endl;

        if(hash1 == hash2){
            ans = mid;
            lo = mid + 1;
        }else{
            hi = mid - 1;
        }
    }
    // cout<<i<<" , "<<j<<" : "<<ans<<eol;
    if(ans >= size_){
        return false;
    }else{
        return hs1.getForwardHash(i+ans,i+ans) < hs1.getForwardHash(j+ans, j+ans);
    }
}

int main()
{
    FastIO
    string s1 , s2;
    cin >> s1;
    size_ = s1.length();
    s1 = s1 + s1;

    hs1 = Hasher(s1, 1e9 + 7, 31);
    vector<int> v(size_, 0);
    for(int i = 0; i< size_; i++){
        v[i] = i;
        // cout<<i<<": "<<s1.substr(i, size_)<<endl;
        // cout << hs1.getForwardHash(i,i)<<endl;
    }
    // cmp(0, 3);

    sort(v.begin(), v.end(), cmp);
    for(auto it: v) cout<<it<<" ";
    cout<<endl;
    
    return 0;
}