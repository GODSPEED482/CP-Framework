#include<bits/stdc++.h>
#define eol '\n'
#define lli long long
#define int long long
#define FastIO ios_base::sync_with_stdio(0); cin.tie(NULL);
using namespace std;




signed main()
{
    FastIO
    string l, r;
    cin >> l >> r;

    reverse(l.begin(), l.end());
    
    int diff = r.size() - l.size();
    while(diff--){
        l.push_back('0');
    }
    
    reverse(l.begin(), l.end());

    int dp[19][2][2];
    memset(dp, -1, sizeof(dp));
    int n = r.size();

    function<int(int, int, int)> getNum = [&](int level, int istlo, int isthi){
        if(level == n) return 1ll;
        int& ans = dp[level][istlo][isthi];

        if(ans != -1) return ans;
        ans = 0;
        int lo = 0 , hi = 9;
        if(istlo){
            lo = l[level] - '0';
        }
        if(isthi){
            hi = r[level] - '0';
        }

        for(int option = lo; option <= hi; option++){
            int _level = level + 1, _istlo = 0, _isthi = 0;
            if(isthi && option == hi){
                _isthi = 1;
            }
            if(istlo && option == lo) _istlo = 1;

            ans += getNum(_level, _istlo, _isthi);
        }

        return ans;
    };
    
    int ans = getNum(0, 1, 1);
    cout<<ans<<endl;
    return 0;
}