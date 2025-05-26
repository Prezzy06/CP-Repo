#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n,D,arr[100100];
map<ll,ll> compVal;

int tree[400400];

void update(int index, int l, int r, int pos, int val){
    if(pos < l or pos > r){
        return; 
    } 
    if(l == r){
        tree[index] = max(tree[index], val);
        return;
    }
    int mid = (l + r) >> 1;
    update(2*index, l, mid, pos, val);
    update(2*index+1, mid+1, r, pos, val);
    tree[index] = max(tree[2*index], tree[2*index+1]);
}

int query(int index, int l, int r, int lq, int rq){
    if(lq > r or l > rq){
        return 0;
    }
    if(lq <= l and r <= rq){
        return tree[index];
    }
    int mid = (l + r) >> 1;
    return max(query(2*index, l, mid, lq, rq), query(2*index+1, mid+1, r, lq, rq));
}

void solve(){
    cin >> n >> D;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        compVal[arr[i]];
    }

    int cnt = 0;

    for(auto &val : compVal){
        val.second = cnt++;
    }

    int dp[n];
    int ans = 0;

    for(int i = 0; i < n; i++){
        int lo = arr[i] - D;
        int hi = arr[i] + D;

        auto it = compVal.upper_bound(hi);
        it--;   hi = it->second; 

        it = compVal.lower_bound(lo);
        lo = it->second;

        dp[i] = query(1, 0, cnt-1, lo, hi) + 1;
        ans = max(ans, dp[i]);
        update(1, 0, cnt-1, compVal[arr[i]], dp[i]);
    }

    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    solve();
}
