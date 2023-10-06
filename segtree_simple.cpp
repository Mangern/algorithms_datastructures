// Very clean segtree implementation
// Only point updates

int st[mxN * 2];
int arr[mxN];
 
void build() {  // build the tree
  for (int i = n - 1; i > 0; --i) st[i] = max(st[i<<1], st[i<<1|1]);
}
 
void update(int p, int value) {  // set value at position p
  for (st[p += n] = value; p > 1; p >>= 1) st[p>>1] = max(st[p], st[p^1]);
}
 
int rmq(int l, int r) { 
  int res = 0;
  for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
    if (l&1)res = max(res, st[l++]);
    if (r&1)res = max(res, st[--r]);
  }
  return res;
}
 

