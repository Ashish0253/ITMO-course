#include <bits/stdc++.h>
using namespace std;

struct segTree {

    int size;
    vector<int> values;

    int single(int v, int idx) {
        return v;
    }

    void init(int n) {
        size = 1;
        while(size < n) size *= 2;
        values.resize(2 * size);
    }
    
    void build(vector<int> &a, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < (int)a.size()) {
                values[x] = single(a[lx], lx);
            }
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);
        values[x] = values[2 * x + 1] + values[2 * x + 2];
    }
    
    void build(vector<int> &a) {
        build(a, 0, 0, size);
    }

    void set(int i, int x, int lx, int rx) {
        if(rx - lx == 1) {
            values[x] = 1 - values[x];
            return;
        }

        int mid = (lx + rx) / 2;
        if(i < mid) {
            set(i, 2 * x + 1, lx, mid);
        } else {
            set(i, 2 * x + 2, mid, rx);
        }
        values[x] = values[2 * x + 1] + values[2 * x + 2];
    }

    void set(int i) {
        set(i, 0, 0, size);
    }

    int calc(int k, int x, int lx, int rx) {
        if(rx - lx == 1) {
            return lx;
        }

        int mid = (lx + rx) / 2;
        int s1 = values[2 * x + 1];
        if(k < s1) {
            return calc(k, 2 * x + 1, lx, mid);
        } else {
            return calc(k - s1, 2 * x + 2, mid, rx);
        }    
    }

    int calc(int k) {
        return calc(k, 0, 0, size);
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
    for(int i = 0; i < n; i++) {
        cin >> vec[i];
    }

    segTree str;
    str.init(n);

    str.build(vec);

    while(q--) {
        int op, i;
        cin >> op;

        if(op == 1) {
            int i;
            cin >> i;

            vec[i] = 1 - vec[i];
            str.set(i);
        } else {
            int k;
            cin >> k;

            cout << str.calc(k) << endl;
        }
    }
}