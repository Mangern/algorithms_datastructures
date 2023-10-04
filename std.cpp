#include <bits/stdc++.h>
using namespace std;

int main() {
    {
        // Dictionary
        // O(lg n) insert / lookup / delete
        // Nøkler ligger sortert
        // Oftere raskere enn unordered_map
        map<int,int> mp;
        mp[5] = 4; // sette en verdi
        cout << mp[5] << endl;
        mp.erase(5);
        mp[3] = 1;
        mp[2] = 2;
        mp[1] = 3;

        // Printer ut i rekkefølge 1: 3, 2: 2, 3: 1
        for (auto [k, v] : mp) {
            cout << k << ": " << v << endl;
        }
    }
    {
        // Dictionary
        // O(1) insert / lookup / delete
        // Nøkler ligger usortert
        // Mye overhead, men kan være raskere enn map
        unordered_map<int,int> mp;
    }
    {
        // Samme som map, men har kun keys (ikke values)
        set<int> st;
    }
    {
        // Samme som unordered_map, men har kun keys
        unordered_set<int> st;
    }
    {
        // Kan ha flere like nøkler
        multiset<int> st;
        unordered_multiset<int> ust;
        multimap<int,int> mp;
        unordered_multimap<int, int> ump;

        st.count(4); // antall av nøkkelen 4
        st.erase(4); // Vil slette alle 4ere
        st.erase(st.find(4)); // Vil slette 1 4er
    }
}

