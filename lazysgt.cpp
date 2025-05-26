#include <bits/stdc++.h>
using namespace std;

struct node{
    int sum, maxr, lazy;
    node(int s = 0, int m = 0, int l = 0){
        sum = s;
        maxr = m;
        lazy = l;
    }
};

node merge(node a, node b){
    node c;
    c.sum = a.sum + b.sum;
    c.maxr = max(a.maxr, b.maxr);
    return c;
}

vector<int> arr(100100);
node tree[400400];

void push(int index, int l, int r){
    if(tree[index].lazy){
        tree[index].sum = tree[index].lazy * (r - l + 1);
        tree[index].maxr = tree[index].lazy;
        if(l != r){
            tree[2*index].lazy = tree[index].lazy;
            tree[2*index+1].lazy = tree[index].lazy;
        }
        tree[index].lazy = 0;
    }
}

void update(int index, int l, int r, int lq, int rq, int val){ 
    push(index, l , r);
    if(lq > r or l > rq){
        return;
    }

    if(lq <= l and r <= rq){
        tree[index].lazy = val;
        push(index, l, r);
        return;
    }

    int mid = (l + r) >> 1;
    update(2*index, l, mid, lq, rq, val);
    update(2*index+1, mid+1, r, lq, rq, val);
    tree[index] = merge(tree[2*index], tree[2*index+1]);
}

node query(int index, int l, int r, int lq, int rq){
    push(index, l, r);
    if(lq > r or l > rq){
        return node();
    }
    if(lq <= l and r <= rq){
        return tree[index];
    }
    int mid = (l + r) >> 1;
    return merge(query(2*index, l, mid, lq, rq), query(2*index+1, mid+1, r, lq, rq));
}

void solve(){

}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    solve();
}
