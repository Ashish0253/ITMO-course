#include <bits/stdc++.h>
using namespace std;

void radixSort(vector<pair<pair<int, int>, int>> &vec) {

    int n = vec.size();

    // COUNTING SORT WRT SECOND VALUE
    {
        vector<int> bucket(n);
        for(auto x: vec) 
            bucket[x.first.second]++;
        
        vector<int> pos(n);
        pos[0] = 0;
        for(int i = 1; i < n; i++) 
            pos[i] = pos[i - 1] + bucket[i - 1];
        
        vector<pair<pair<int, int>, int>> vecNew(n);

        for(auto x: vec) {
            int i = x.first.second;

            vecNew[pos[i]] = x;
            pos[i]++;
        }

        vec = vecNew;
    }

    // COUNTING SORT WRT FIRST VALUE
    {
        vector<int> bucket(n);
        for(auto x: vec) 
            bucket[x.first.first]++;
        
        vector<int> pos(n);
        pos[0] = 0;
        for(int i = 1; i < n; i++) 
            pos[i] = pos[i - 1] + bucket[i - 1];
        
        vector<pair<pair<int, int>, int>> vecNew(n);

        for(auto x: vec) {
            int i = x.first.first;

            vecNew[pos[i]] = x;
            pos[i]++;
        }

        vec = vecNew;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    str += "$";
    int n = str.size();

    vector<int> map(n), order(n);

    // k = 0
    {
        vector<pair<char, int>> vec(n);

        for(int i = 0; i < n; i++) 
            vec[i] = {str[i], i};
        
        sort(vec.begin(), vec.end());

        // STORING SORTED ORDER OF INDEXES IN "vector order"
        for(int i = 0; i < n; i++) 
            order[i] = vec[i].second;
        
        map[order[0]] = 0;

        for(int i = 1; i < n; i++) {

            if(vec[i].first == vec[i - 1].first) 
                map[order[i]] = map[order[i - 1]];
            else 
                map[order[i]] = map[order[i - 1]] + 1;
        }
    } 

    // k > 0

    int k = 0; 
    while((1 << k) < n) {

        vector<pair<pair<int, int>, int>> vec(n);

        for(int i = 0; i < n; i++) 
            vec[i] = {{map[i], map[(i + (1 << k)) % n]}, i};
        
        radixSort(vec);

        // STORING SORTED ORDER OF INDEXES IN "vector order"
        for(int i = 0; i < n; i++) 
            order[i] = vec[i].second;
        
        map[order[0]] = 0;
        for(int i = 1; i < n; i++) {

            if(vec[i].first == vec[i - 1].first) 
                map[order[i]] = map[order[i - 1]];
            else 
                map[order[i]] = map[order[i - 1]] + 1;
        }

        k++;
    }

    for(int i = 0; i < n; i++) 
        cout << order[i] << " ";
    
    return 0;
}