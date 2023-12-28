#include <bits/stdc++.h>
using namespace std;

// SORT IN LINEAR TIME
void countSort(vector<int> &order, vector<int> &map) {

    int n = order.size();
    
    vector<int> bucket(n);
    for(int i = 0; i < n; i++) 
        bucket[map[i]]++;
    
    for(int i = 1; i < n; i++) 
        bucket[i] += bucket[i - 1];
    
    vector<int> newOrder(n);
    for(int i = n - 1; i >= 0; i--) {

        int idx = bucket[map[order[i]]] - 1;
        bucket[map[order[i]]] -= 1;
        newOrder[idx] = order[i];
    }

    order = newOrder;
}

// FINDING THE LEAST COMMON PREFIX IN LINEAR TIME OF 
// ALL THE ORDERED SUFFIX ARRAY     
vector<int> getLCP(string &str, vector<int> &map, vector<int> &order) {
    int n = str.size();
    vector<int> lcp(n);
    int k = 0;
    for(int i = 0; i < n - 1; i++) {

        int pi = map[i];
        int j = order[pi - 1];

        while(str[i + k] == str[j + k]) k++;
        lcp[pi] = k;
        k = max(k - 1, 0);
    }

    return lcp;
}

string findLCS(string &str, string &a, string &b, vector<int> &order, vector<int> &lcp) {

    string lcs = "";
    int n = lcp.size(), size = a.size(), maxLen = 0;
    for(int i = 2; i < n - 1; i++) {
        bool iIsInA = order[i] <= size - 1, jIsInA = order[i + 1] <= size - 1;

        if(iIsInA != jIsInA) {
            if(maxLen < lcp[i + 1]) {
                maxLen = lcp[i + 1];
                lcs = a.substr(min(order[i], order[i + 1]), maxLen);

                // cout << lcs << endl;
            }
        }
    }

    return lcs;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios_base::sync_with_stdio(0);

    string a, b;
    cin >> a >> b;

    a += "$";
    b += "#";
    string str = a + b;
    long long n = str.size();

    vector<int> map(n), order(n);

    // k = 0 
    {
        vector<pair<char, int>> vec(n);

        for(int i = 0; i < n; i++) 
            vec[i] = {str[i], i};
        
        sort(vec.begin(), vec.end());

        for(int i = 0; i < n; i++) 
            order[i] = vec[i].second;
        
        map[order[0]] = 0;
        for(int i = 1; i < n; i++) {
            if(vec[i].first == vec[i - 1].first) 
                map[order[i]] = map[order[i - 1]];
            else {
                map[order[i]] = map[order[i - 1]] + 1;
            }
        }
    }

    // k > 0
    int k = 0;
    while((1 << k) < n) {

        // SHIFTING ORDERED INDEX LEFT 
        for(int i = 0; i < n; i++) 
            order[i] = (order[i] - (1 << k) + n) % n;
        
        countSort(order, map);

        vector<int> newMap(n);
        newMap[order[0]] = 0;
        for(int i = 1; i < n; i++) {
            pair<int, int> prev = {map[order[i - 1]], map[(order[i - 1] + (1 << k)) % n]}; 
            pair<int, int> curr = {map[order[i]], map[(order[i] + (1 << k)) % n]}; 

            if(prev == curr) 
                newMap[order[i]] = newMap[order[i - 1]];
            else 
                newMap[order[i]] = newMap[order[i - 1]] + 1;
        }

        map = newMap;
        k++;
    }

    vector<int> lcp = getLCP(str, map, order);

    // for(int i = 0; i < n; i++) {
    //     cout << lcp[i] << " " << order[i] << " " << str.substr(order[i], n - order[i]) << endl;
    // }

    string lcs = findLCS(str, a, b, order, lcp);

    cout << lcs << endl;
}