// Currently my most powerful segment tree that supports 2 different updates and 8 query
struct segtree_basic {
  struct node {
    int lazyval, mi, ma, sum; char lazytag;
    int len; // not changing
  };
  int stok;
  vector<node> st;
  void bu(int l, int r, int idx) {
    st[idx].lazyval = st[idx].mi = st[idx].ma = st[idx].sum = 0;
    st[idx].lazytag = '?';
    st[idx].len = r - l + 1;
    if(l == r) {
      return;
    }
    int mid = (l + r) >> 1;
    bu(l, mid, 2*idx+1);
    bu(mid+1, r, 2*idx+2);
  }
  void push_down(int idx) {
    if(st[idx].lazytag == '?') return;
    if(st[idx].lazytag == ':') {
      st[2*idx+1].lazyval = st[idx].lazyval;
      st[2*idx+1].mi = st[idx].lazyval;
      st[2*idx+1].ma = st[idx].lazyval;
      st[2*idx+1].sum = st[idx].lazyval * st[2*idx+1].len;
      st[2*idx+1].lazytag = ':';
 
      st[2*idx+2].lazyval = st[idx].lazyval;
      st[2*idx+2].mi = st[idx].lazyval;
      st[2*idx+2].ma = st[idx].lazyval;
      st[2*idx+2].sum = st[idx].lazyval * st[2*idx+2].len;
      st[2*idx+2].lazytag = ':';
 
    }
    else {
      st[2*idx+1].lazyval += st[idx].lazyval;
      st[2*idx+1].mi += st[idx].lazyval;
      st[2*idx+1].ma += st[idx].lazyval;
      st[2*idx+1].sum += st[idx].lazyval * st[2*idx+1].len;
      st[2*idx+1].lazytag = (st[2*idx+1].lazytag == ':' ? ':' : '+');
 
      st[2*idx+2].lazyval += st[idx].lazyval;
      st[2*idx+2].mi += st[idx].lazyval;
      st[2*idx+2].ma += st[idx].lazyval;
      st[2*idx+2].sum += st[idx].lazyval * st[2*idx+2].len;
      st[2*idx+2].lazytag = (st[2*idx+2].lazytag == ':' ? ':' : '+');
    }
    st[idx].lazytag = '?';
    st[idx].lazyval = 0;
  }
  void push_up(int idx) {
    st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
    st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
    st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
  }
  void u1(int l, int r, int constl, int constr, int idx, int val) { // range := v
    if(l <= constl && constr <= r) {
      st[idx].lazyval = val;
      st[idx].mi = val;
      st[idx].ma = val;
      st[idx].sum = val * st[idx].len;
      st[idx].lazytag = ':';
      return;
    }
    int mid = (constl + constr) >> 1;
    push_down(idx);
    if(mid < l || r < constl) u1(l, r, mid+1, constr, 2*idx+2, val);
    else if(constr < l || r < mid + 1) u1(l, r, constl, mid, 2*idx+1, val);
    else {
      u1(l, r, constl, mid, 2*idx+1, val);
      u1(l, r, mid+1, constr, 2*idx+2, val);
    }
    push_up(idx);
  }
 
  void u2(int l, int r, int constl, int constr, int idx, int val) { // range += v
    if(l <= constl && constr <= r) {
      st[idx].lazyval += val;
      st[idx].mi += val;
      st[idx].ma += val;
      st[idx].sum += val * st[idx].len;
      st[idx].lazytag = (st[idx].lazytag == ':' ? ':' : '+');
      return;
    }
    int mid = (constl + constr) >> 1;
    push_down(idx);
    if(mid < l || r < constl) u2(l, r, mid+1, constr, 2*idx+2, val);
    else if(constr < l || r < mid + 1) u2(l, r, constl, mid, 2*idx+1, val);
    else {
      u2(l, r, constl, mid, 2*idx+1, val);
      u2(l, r, mid+1, constr, 2*idx+2, val);
    }
    push_up(idx);
  }
 
  int qu1(int l, int r, int constl, int constr, int idx) { // range min
    if(l <= constl && constr <= r) return st[idx].mi;
    int mid = (constl + constr) >> 1;
    push_down(idx);
    if(mid < l || r < constl) return qu1(l, r, mid+1, constr, 2*idx+2);
    else if(constr < l || r < mid + 1) return qu1(l, r, constl, mid, 2*idx+1);
    else {
      return min(qu1(l, r, constl, mid, 2*idx+1), qu1(l, r, mid+1, constr, 2*idx+2));
    }
  }
 
  int qu2(int l, int r, int constl, int constr, int idx) { // range max
    if(l <= constl && constr <= r) return st[idx].ma;
    int mid = (constl + constr) >> 1;
    push_down(idx);
    if(mid < l || r < constl) return qu2(l, r, mid+1, constr, 2*idx+2); 
    else if(constr < l || r < mid + 1) return qu2(l, r, constl, mid, 2*idx+1);
    else {
      return max(qu2(l, r, constl, mid, 2*idx+1), qu2(l, r, mid+1, constr, 2*idx+2));
    }
  }
  int qu3(int l, int r, int constl, int constr, int idx) { // range sum
    if(l <= constl && constr <= r) return st[idx].sum;
    int mid = (constl + constr) >> 1;
    push_down(idx);
    if(mid < l || r < constl) return qu3(l, r, mid+1, constr, 2*idx+2);
    else if(constr < l || r < mid + 1) return qu3(l, r, constl, mid, 2*idx+1);
    else {
      return qu3(l, r, constl, mid, 2*idx+1) + qu3(l, r, mid+1, constr, 2*idx+2);
    }
  }
  int qu4(int l, int r, int constl, int constr, int idx, int val) { // first at least v
    if(l <= constl && constr <= r) {
      if(st[idx].ma < val) return -1;
      while(constl < constr) {
        int mid = (constl + constr) >> 1;
        push_down(idx);
        if(st[2*idx+1].ma >= val) constr = mid, idx = 2*idx + 1;
        else constl = mid+1, idx = 2*idx + 2;
      }
      return constl;
    }
    int mid = (constl + constr) >> 1;
    push_down(idx);
    if(mid < l || r < constl) return qu4(l, r, mid+1, constr, 2*idx+2, val);
    else if(constr < l || r < mid + 1) return qu4(l, r, constl, mid, 2*idx+1, val);
    else {
      int lchild = qu4(l, r, constl, mid, 2*idx+1, val);
      if(lchild != -1) return lchild;
      return qu4(l, r, mid+1, constr, 2*idx+2, val);
    }
  }
  int qu5(int l, int r, int constl, int constr, int idx, int val) { // first at most v
    if(l <= constl && constr <= r) {
      if(st[idx].mi > val) return -1;
      while(constl < constr) {
        int mid = (constl + constr) >> 1;
        push_down(idx);
        if(st[2*idx+1].mi <= val) constr = mid, idx = 2*idx + 1;
        else constl = mid+1, idx = 2*idx + 2;
      }
      return constl;
    }
    int mid = (constl + constr) >> 1;
    push_down(idx);
    if(mid < l || r < constl) return qu5(l, r, mid+1, constr, 2*idx+2, val);
    else if(constr < l || r < mid + 1) return qu5(l, r, constl, mid, 2*idx+1, val);
    else {
      int lchild = qu5(l, r, constl, mid, 2*idx+1, val);
      if(lchild != -1) return lchild;
      return qu5(l, r, mid+1, constr, 2*idx+2, val);
    }
  }
  int qu6(int l, int r, int constl, int constr, int idx, int val) { // last at least v
    if(l <= constl && constr <= r) {
      if(st[idx].ma < val) return -1;
      while(constl < constr) {
        int mid = (constl + constr) >> 1;
        push_down(idx);
        if(st[2*idx+2].ma >= val) constl = mid+1, idx = 2*idx + 2;
        else constr = mid, idx = 2*idx + 1;
      }
      return constl;
    }
    int mid = (constl + constr) >> 1;
    push_down(idx);
    if(mid < l || r < constl) return qu6(l, r, mid+1, constr, 2*idx+2, val);
    else if(constr < l || r < mid + 1) return qu6(l, r, constl, mid, 2*idx+1, val);
    else {
      int rchild = qu6(l, r, mid+1, constr, 2*idx+2, val);
      if(rchild != -1) return rchild;
      return qu6(l, r, constl, mid, 2*idx+1, val);
    }
  }
  int qu7(int l, int r, int constl, int constr, int idx, int val) { // last at most v
    if(l <= constl && constr <= r) {
      if(st[idx].mi > val) return -1;
      while(constl < constr) {
        int mid = (constl + constr) >> 1;
        push_down(idx);
        if(st[2*idx+2].mi <= val) constl = mid+1, idx = 2*idx + 2;
        else constr = mid, idx = 2*idx + 1;
      }
      return constl;
    }
    int mid = (constl + constr) >> 1;
    push_down(idx);
    if(mid < l || r < constl) return qu7(l, r, mid+1, constr, 2*idx+2, val);
    else if(constr < l || r < mid + 1) return qu7(l, r, constl, mid, 2*idx+1, val);
    else {
      int rchild = qu7(l, r, mid+1, constr, 2*idx+2, val);
      if(rchild != -1) return rchild;
      return qu7(l, r, constl, mid, 2*idx+1, val);
    }
  }
  int qu8(int l, int r, int constl, int constr, int idx, int val) { // first partial sum at least v, only works when partial sum is non-decreasing
    if(l <= constl && constr <= r) {
      if(st[idx].sum < val) return -1;
      while(constl < constr) {
        int mid = (constl + constr) >> 1;
        push_down(idx);
        if(st[2*idx+1].sum >= val) {
          idx = 2*idx+1, constr = mid;
        }
        else {
          val -= st[2*idx+1].sum;
          idx = 2*idx+2, constl = mid+1;
        }
      }
      return constl;
    }
    int mid = (constl + constr) >> 1;
    push_down(idx);
    if(mid < l || r < constl) return qu8(l, r, mid+1, constr, 2*idx+2, val - st[2*idx+1].sum);
    else if(constr < l || r < mid+1) return qu8(l, r, constl, mid, 2*idx+1, val);
    else {
      int lchild = qu8(l, r, constl, mid, 2*idx+1, val);
      if(lchild != -1) return lchild;
      return qu8(l, r, mid+1, constr, 2*idx+2, val - st[2*idx+1].sum);
    }
  }
  public:
  void resize(int k) {
    st.resize(4*k + 10);
    stok = k;
    bu(0, k, 0);
  }
  void range_assign(int l, int r, int v) { u1(l, r, 0, stok, 0, v); }
 
  void range_add(int l, int r, int v) { u2(l, r, 0, stok, 0, v); }
 
  int query_min(int l, int r) { return qu1(l, r, 0, stok, 0); }
 
  int query_max(int l, int r) { return qu2(l, r, 0, stok, 0); }
 
  int query_sum(int l, int r) { return qu3(l, r, 0, stok, 0); }
 
  int query_firstAtLeast(int l, int r, int v) { return qu4(l, r, 0, stok, 0, v); }
 
  int query_firstAtMost(int l, int r, int v) { return qu5(l, r, 0, stok, 0, v); }
 
  int query_lastAtLeast(int l, int r, int v) { return qu6(l, r, 0, stok, 0, v); } 
 
  int query_lastAtMost(int l, int r, int v) { return qu7(l, r, 0, stok, 0, v); }

  int query_firstPSAtLeast(int l, int r, int v) { return qu8(l, r, 0, stok, 0, v); }
};
