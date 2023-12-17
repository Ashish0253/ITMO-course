#include <bits/stdc++.h>
using namespace std;

struct segTree {

    int size;
    vector<long long> sums;

    void init(int n) {
        size = 1;
        while(size < n) size *= 2;
        sums.assign(2 * size, 0LL);
    }

    void print() {
        for(auto i: sums) 
            cout << i << " ";
        cout << endl;
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < (int)a.size()) {
                sums[x] = a[lx];
            }
            return;
        }

        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];    
    }

    void build(vector<int> &a) {
        build(a, 0, 0, size);
    }
    long long sum(int l, int r, int x, int lx, int rx) {
        if(l >= rx || r <= lx) return 0;
        if(l <= lx && rx <= r) return sums[x];

        int m = (lx + rx) / 2;
        long long s1 = sum(l, r, 2 * x + 1, lx, m);
        long long s2 = sum(l, r, 2 * x + 2, m, rx);
        return s1 + s2;
    }

    long long sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
    
    void set(int i, int v, int x, int  lx, int rx) {
        if(rx - lx == 1) {
            sums[x] = v;
            return;
        }
        
        int m = (lx + rx) / 2;
        if(i < m) {
            set(i, v, 2 * x + 1, lx, m);
        } 
        else {
            set(i, v, 2 * x + 2, m, rx);
        }
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
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

            cout << str.sum(l, r) << endl;
        }
    }

    // str.print();
}