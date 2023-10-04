#include <bits/stdc++.h>
using namespace std;

// Stolen shamelessly from github
//
// Divide and conquer algorithm for trees
// Basically if the problem is solvable by 
// looking at bigger and bigger "areas" in the tree,
// Centroid decomposition can be useful
// It recursively divides a tree into smaller subtrees,
// Ensuring three properties:
//  1. The size of each subtree is at most half the size of the enclosing tree
//     This recurses down, ensuring that the height of the decomposition is
//     O(lg n)
//  2. For each node, it belongs to the component of all its ancestor
//     As a collorary, to calculate the path between node a and node b,
//     use dist(a, lca(a,b)) + dist(b, lca(a,b)) where dist works in the original
//     tree and lca works in the centroid tree (Where lca is trivially found
//     in lg n time
//  3. If we define a set of O(nlgn) paths as "all paths from a node
//     to one of its (centroid decomp) ancestors", then all O(n²) paths
//     in the original tree is just a concatenation of two paths in 
//     this set.
//
//  All of this is useful if you, for example, want to quickly update
//  and query things involving "all possible paths" from a node,
//  because you basically only need to consider paths to the centroid decomp 
//  ancestors
//  For example, consider this problem:
//  All nodes except one are initially blue
//  You need to process two types of queries:
//  1. Color a node red
//  2. Given node v, find the distance to the nearest red node
//
//  You can solve this by doing a centroid decomposition and storing
//  an array ans[u] = # distance to the closest red node
//  1. Color node v, and for each ancestor a of v, update
//     ans[a] = min(ans[a], dist(a,v))
//  2. Take the minimum of ans[a] + dist(a,v) for each ancestor a of v
//
//  Smooth
    
};
struct CentroidDecomposition {
	vector<set<int>> tree; // it's not vector<vector<int>>!
	vector<int> dad;
	vector<int> sub;

	CentroidDecomposition(vector<set<int>> &tree) : tree(tree) {
		int n = tree.size();
		dad.resize(n);
		sub.resize(n);
		build(0, -1);
	}

	void build(int u, int p) {
		int n = dfs(u, p); // find the size of each subtree
		int centroid = dfs(u, p, n); // find the centroid
		if (p == -1) p = centroid; // dad of root is the root itself
		dad[centroid] = p;

		// for each tree resulting from the removal of the centroid
        while (tree[centroid].size()) {
            int v = *tree[centroid].begin();
            tree[centroid].erase(v);
            tree[v].erase(centroid);
            build(v, centroid);
        }
	}

	int dfs(int u, int p) {
		sub[u] = 1;

		for (auto v : tree[u])
			if (v != p) sub[u] += dfs(v, u);

		return sub[u];
	}

	int dfs(int u, int p, int n) {
		for (auto v : tree[u])
			if (v != p and sub[v] > n/2) return dfs(v, u, n);

		return u;
	}

	int operator[](int i) {
		return dad[i];
	}
};

int main() {
    int n, m;
    cin >>n >> m;
    vector<set<int>> tree(n);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v, --u, --v;
        tree[u].insert(v);
        tree[v].insert(u);
    }

    auto decomp = CentroidDecomposition(tree);
}
