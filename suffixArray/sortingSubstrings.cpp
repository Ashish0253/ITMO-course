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

pair<vector<int>, vector<vector<int>>> computeSuffixArray(string &str) {
    
    // BECAUSE THE STRING WILL CONTAIN THE CHARACTERS BETWEEN 33 TO 127
    str += char(32);
    int n = str.size();
    
    // FOR STORING ALL THE MAP PRODUCED IN THE PROCESS
    vector<vector<int>> allMaps;
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
    allMaps.push_back(map);
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
        allMaps.push_back(map);
    }

    return {order, allMaps};
}

void sortSubstrings(vector<pair<int, int>> &subStrings, vector<vector<int>> &allMaps) {

    sort(subStrings.begin(), subStrings.end(), [&allMaps](pair<int, int> &a, pair<int, int> &b) {
        int l1 = a.first, r1 = a.second, len1 = r1 - l1 + 1;
        int l2 = b.first, r2 = b.second, len2 = r2 - l2 + 1;

        int minLen = min(len1, len2);
        int k = 0;
        while((1 << k) <= minLen) {
            k++;
        }
        k--;
        
        if(k >= allMaps.size()) {
            k = allMaps.size() - 1;
        }

        pair<int, int> class1 = {allMaps[k][l1 - 1], allMaps[k][l1 + minLen - 1 - (1 <<k)]};
        pair<int, int> class2 = {allMaps[k][l2 - 1], allMaps[k][l2 + minLen - 1 - (1 <<k)]};

        bool res = false;
        if(class1 != class2) {
            res = class1 < class2;
        }
        else {
            if(len1 != len2) {
                res = len1 < len2;
            }
            else {
                res = a < b;
            }
        }

        return res;
    });
}



int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios_base::sync_with_stdio(0);

    string str;
    cin >> str;

    int n;
    cin >> n;

    vector<pair<int, int>> subStrings(n);
    for(int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        subStrings[i] = {l, r};
    }

    auto result = computeSuffixArray(str);

    sortSubstrings(subStrings, result.second);

    // cout << result.second.size() << endl;

    for(int i = 0; i < n; i++) {
        cout << subStrings[i].first << " " << subStrings[i].second << endl;
    }
    
}