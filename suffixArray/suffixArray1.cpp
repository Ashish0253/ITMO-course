#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define fo(i, a, n) for (ll i = a; i < n; i++)
#define Fo(i, k, n) for (i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, false, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define PI 3.1415926535897932384626
#define mod 1000000007
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;

void solve() {
    
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

        for(int i = 0; i < n; i++) 
            order[i] = vec[i].second;

        map[order[0]] = 0;
        
        for(int i = 1; i < n; i++) {

            if(vec[i].first == vec[i - 1].first) {
                map[order[i]] = map[order[i - 1]];
            }
            else {
                map[order[i]] = map[order[i - 1]] + 1;
            }
        }
    }

    // k > 0

    int k = 0;
    while((1 << k) < n) {

        vector<pair<pair<int, int>, int>> vec(n);

        for(int i = 0; i < n; i++) 
            vec[i] = {{map[i], map[(i + (1 << k)) % n]}, i};

        sort(vec.begin(), vec.end());
        
        for(int i = 0; i < n; i++) 
            order[i] = vec[i].second;
        
        map[order[0]] = 0;
        for(int i = 1; i < n; i++) {

            if(vec[i].first == vec[i - 1].first) {
                map[order[i]] = map[order[i - 1]]; 
            }
            else {
                map[order[i]] = map[order[i - 1]] + 1;
            }
        }

        k++;
    }

    for(int i = 0; i < n; i++) 
        cout << order[i] << " ";
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
    // int t;
    // cin >> t;
    // while (t--)
    // {
        solve();
    // }
    return 0;
}