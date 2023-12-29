#include <bits/stdc++.h>
using namespace std;

struct segTree {

    int size;
    vector<pair<int, int>> values;

    void init(int n) {
        size = 1;
        while(size < n) size *= 2;
        values.resize(2 * size);
    }

    pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
        if(a.first < b.first) {
            return a;
        }
        else if(a.first > b.first) {
            return b;
        }
        else {
            return {a.first, a.second + b.second};
        }
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < (int)a.size()) {
                values[x] = {a[lx], 1};
            }
            else {
                values[x] = {INT_MAX, 1};
            }
            return;
        }

        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);

        // UPDATING CURR NODE
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<int> &a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if(rx - lx == 1) {
            values[x] = {v, 1};
            return;
        }

        int m = (lx + rx) / 2;
        if(i < m) {
            set(i, v, 2 * x + 1, lx, m);
        }
        else {
            set(i, v, 2 * x + 2, m, rx);
        }

        // UPDATING CURR NODE
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    pair<int, int> count(int l, int r, int x, int lx, int rx) {
        if(r <= lx || rx <= l) return {INT_MAX, 0};
        if(l <= lx && rx <= r) {
            return values[x];
        }

        int m = (lx + rx) / 2;
        pair<int, int> v1 = count(l, r, 2 * x + 1, lx, m);
        pair<int, int> v2 = count(l, r, 2 * x + 2, m, rx);

        // RETURNING THE LEAST VALUE
        return merge(v1, v2);
    }

    pair<int, int> count(int l, int r) {
        return count(l, r, 0, 0, size);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    void print() {
        for(auto i: values) {
            cout << i.first << " " << i.second << " ";
        }
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios_base::sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    segTree str;
    str.init(n);

    str.build(a);

    // str.print();
    while(q--) {
        int op;
        cin >> op;

        if(op == 1) {
            int i, v;
            cin >> i >> v;

            str.set(i, v);
        }
        else {
            int l, r;
            cin >> l >> r;
            // cout << l << r << endl;
            cout << str.count(l, r).first << " " << str.count(l, r).second << endl;
        }   
    }
}