#include <bits/stdc++.h>
using namespace std;

void countSort(vector<int> &map, vector<int> &order) {

    int n = map.size();
    vector<int> bucket(n);

    // ADDING CNT IN bucket
    for(int i = 0; i < n; i++) 
        bucket[map[i]]++;
    
    // TAKING PREFIX SUM IN bucket ARRAY
    for(int i = 1; i < n; i++) 
        bucket[i] += bucket[i - 1];
    
    vector<int> newOrder(n);
    for(int i = n - 1; i >= 0; i--) {

        int idx = bucket[map[order[i]]] - 1;
        newOrder[idx] = order[i];
        bucket[map[order[i]]] -= 1;
    }  

    order = newOrder; 
}

vector<int> orderedSubstring(string &str, int n) {

    vector<int> map(n), order(n); 

    // k == 0
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
            else 
                map[order[i]] = map[order[i - 1]] + 1;
        }

    }

    // k > 0
    int k = 0;
    while((1 << k) < n) {

        // SHIFT THE INDEX (1 << k) LEFT
        for(int i = 0; i < n; i++) {
            order[i] = (order[i] - (1 << k) + n) % n;
        }

        // TO UPDATE THE ORDER BY CONSIDERING THE LEFT SHIFT IN THE INDEXES
        countSort(map, order);

        // TO UPDATE THE MAP WRT THE NEW ORDER OF INDEXES
        vector<int> newMap(n);

        newMap[order[0]] = 0;
        for(int i = 1; i < n; i++) {
            pair<int, int> prev = {map[order[i - 1]], map[(order[i - 1] + (1 << k)) % n]};
            pair<int, int> curr = {map[order[i]], map[(order[i] + (1 << k)) % n]};

            if(prev == curr) 
                newMap[order[i]] = newMap[order[i -1]];
            else 
                newMap[order[i]] = newMap[order[i -1]] + 1; 
        }

        map = newMap;
        k++;
    }
    
    return order;
}

int main() 
{
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

    // FINDING THE ORDER OF ALL POSSIBLE SUBSTR
    vector<int> order = orderedSubstring(str, n);

    int q;
    cin >> q;

    while(q--) {

        string p;
        cin >> p;

        int m = p.size();

        int low = 0, high = n - 1;
        int left = 0;
        // LOWERBOUND 
        while(low <= high) {

            int mid = low + (high - low) / 2;

            // CHECK IF THE SUBSTRING STARTING FROM mid MATCHES THE QUERY 
            string sub = str.substr(order[mid], p.size());

            if(sub == p) {
                left = mid;
                high = mid - 1;
            }
            else if(sub < p) 
                low = mid + 1;
            else 
                high = mid - 1;
        }

        low = 0, high = n - 1;
        int right = -1;
        // UPPERBOUND
        while(low <= high) {

            int mid = low + (high - low) / 2;

            // CHECK IF THE SUBSTRING STARTING FROM mid MATCHES THE QUERY 
            string sub = str.substr(order[mid], p.size());

            if(sub == p) {
                right = mid;
                low = mid + 1;
            }
            else if(sub < p) 
                low = mid + 1;
            else 
                high = mid - 1;
        }

        cout << right - left + 1 << endl;
    }

}