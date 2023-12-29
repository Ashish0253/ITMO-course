#include <bits/stdc++.h>
using namespace std;

struct segTree {

    int size;
    vector<int> values;

    void init(int n) {
        size = 1;
        while(size < n) size *= 2;
        values.assign(2 * size, INT_MAX);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < (int)a.size()) {
                values[x] = a[lx];
            }
            return;
        } 

        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        values[x] = min(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<int> &a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if(rx - lx == 1) {
            values[x] = v;
            return;
        } 

        int m = (lx + rx) / 2;
        if(i < m) {
            set(i, v, 2 * x + 1, lx, m);
        }
        else {
            set(i, v, 2 * x + 2, m, rx);
        }
        values[x] = min(values[2 * x + 1], values[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int calculateMin(int l, int r, int x, int lx, int rx) {
        if(r <= lx || rx <= l) return INT_MAX;
        if(l <= lx && rx <= r) return values[x];

        int m = (lx + rx) / 2;
        int v1 = calculateMin(l, r, 2 * x + 1, lx, m);
        int v2 = calculateMin(l, r, 2 * x + 2, m, rx);
        return min(v1, v2);
    }

    int calculateMin(int l, int r) {
        return calculateMin(l, r, 0, 0, size);
    }

    void print() {
        for(auto i: values)
            cout << i << " ";
        cout << endl;
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

    segTree str;
    str.init(n);

    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    str.build(a);

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

            cout << str.calculateMin(l, r) << endl;
        }
    }
}