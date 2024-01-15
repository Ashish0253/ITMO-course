#include <bits/stdc++.h>
using namespace std;

struct segTree {

    int size;
    vector<int> values;

    void init(int n) {
        size = 1;
        while(size < n) size *= 2;
        values.resize(2 * size);
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
        values[x] = max(values[2 * x + 1], values[2 * x + 2]);
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
        } else {
            set(i, v, 2 * x + 2, m, rx);
        }
        values[x] = max(values[2 * x + 1], values[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int calc(int k, int l, int x, int lx, int rx) {
        if(values[x] < k) {
            return -1;
        }

        if(rx <= l) {
            return -1;
        }
        
        if(rx - lx == 1) {
            return lx;
        }

        int m = (lx + rx) / 2;
        int res = calc(k, l, 2 * x + 1, lx, m);
        if(res == -1) {
            res = calc(k, l, 2 * x + 2, m, rx);
        }

        return res;
    }

    int calc(int k, int l) {
        return calc(k, l, 0, 0, size);
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

    vector<int> vec(n);
    for(int i = 0; i < n; i++) 
        cin >> vec[i];
    
    segTree str;
    str.init(n);

    str.build(vec);
    
    while(q--) {
        int op;
        cin >> op;

        if(op == 1) {
            int i, v;
            cin >> i >> v;

            vec[i] = v;
            str.set(i, v);
        } else {
            int x, l;
            cin >> x >> l;

            cout << str.calc(x, l) << endl;
        }
    }
}