#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

/*
// Containers
vector<T>; // dynamisk array

set<T>; // unike verdier i sortert rekkefølge O(lgn)
multiset<T>; // verdier i sortert rekkefølge O(lgn)
unordered_set<T>; // unike verdier i usortert rekkefølge O(1)
unordered_multiset<T>; // verdier i usortert rekkefølge O(1)

list<T>; // Dobbelt lenket liste
queue<T>; // FIFO
stack<T>; // LIFO
priority_queue<T>; // Heap interface (default max-heap)

map<T,T>; // Key -> value, keys unike og sortert O(lgn)
multimap<T,T>; // Key -> value, keys er ikke unike men sortert O(lgn)
unordered_map<T,T>; // Key -> value, keys er unike og usortert O(1)
unordered_multimap<T, T>; // Key -> value, keys verken unike eller sortert O(1)

bitset<NUM_BITS>; // NUM_BITS bits, kan opereres på med bitwise operatorer
                  // Kan redusere tidskompleksiteten fra f.eks en vector
                  // med 0 og 1 med en faktor av 32 (antall bits i en int)

// Algorithms
sort(begin(v), end(v)); // v er f.eks. en vector
lower_bound(begin(v), end(v), x); // v skal være sortert
                               // returnerer en peker til første element som er
                               // >= x
upper_bound(begin(v), end(v), x); // v skal være sortert
                                  // returnerer en peker til første element 
                                  // som er > x 
next_permutation(begin(v), end(v)); // Transformerer v til neste permutasjon
                                    // som kommer etter v i leksikografisk 
                                    // rekkefølge
*/
int main() {
    {
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

