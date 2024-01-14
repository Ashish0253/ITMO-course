#include <bits/stdc++.h>
using namespace std;

struct item {
    long long seg, pref, suf, sum;
};

struct segTree {

    int size;
    vector<item> values;

    item merge(item a, item b) {
        return {
            max({a.seg, b.seg, a.suf + b.pref}), 
            max({a.pref, a.sum + b.pref}),
            max({b.suf, a.suf + b.sum}),
            a.sum + b.sum
        };
    }

    item single(int v) {
        if(v > 0) {
            return {v, v, v, v};
        } else {
            return {0, 0, 0, v};
        } 
    }

    void init(int n) {
        size = 1;
        while(size < n) size *= 2;
        values.resize(2 * size);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < (int)a.size()) {
                values[x] = single(a[lx]);
            }
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<int> &a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if(rx - lx == 1) {
            values[x] = single(v);
            return;
        }

        int mid = (lx + rx) / 2;
        if(i < mid) {
            set(i, v, 2 * x + 1, lx, mid);
        } else {
            set(i, v, 2 * x + 2, mid, rx);
        }
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    item calc() {
        return values[0];
    }

};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> vec(n);
    for(int i = 0; i < n; i++) 
        cin >> vec[i];
    
    segTree str;
    str.init(n);

    str.build(vec);
    
    cout << str.calc().seg << endl;
    while(m--) {

        int idx, v;
        cin >> idx >> v;

        str.set(idx, v);
        cout << str.calc().seg << endl;
    }
    
}