struct two_sat { // 0-based ONLY
  vector<vector<int> >adj, rev;
  vector<int> sol, ord;
  vector<bool> vis;
  int n;
  void resize(int n_) {
    n = n_;
    adj.resize(2*n);
    ord.resize(2*n);
    sol.resize(n);
    vis.resize(2*n);
    rev.resize(2*n);
  }
  void append_constraint(int i, int a, int j, int b) {// BEWARE OF THE ORDER
    assert(min(i, j) >= 0 && max(i, j) < n);
    assert(min(a, b) >= 0 && max(a, b) < 2);
    //r[i] = a OR r[j] = b
    if(!a && !b) {
      adj[n+i].push_back(j);
      adj[n+j].push_back(i);
    }
    else if(!a) {
      adj[n+i].push_back(n+j);
      adj[j].push_back(i);
    }
    else if(!b) {
      adj[i].push_back(j);
      adj[n+j].push_back(n+i);
    }
    else {
      adj[i].push_back(n+j);
      adj[j].push_back(n+i);
    }
  }
  stack<int> topsort;
  void dfs1(int node) {
    vis[node] = 1;
    for(int x: adj[node]) {
      if(!vis[x]) dfs1(x);
    }
    topsort.push(node);
  }
  vector<int>cc;
  void dfs2(int node) {
    vis[node] = 1;
    for(int x: rev[node]) {
      if(!vis[x]) dfs2(x);
    }
    cc.push_back(node);
  }
  vector<int> assign_values() { // No solution: return empty array
    for(int i=0; i<2*n; i++) {
      for(int x: adj[i]) rev[x].push_back(i);
    }
    for(int i=0; i<2*n; i++) {
      if(!vis[i]) dfs1(i);
    }
    for(int i=0; i<2*n; i++) vis[i] = 0;
    int nxt = 0;
    while(topsort.size()) {
      int tt = topsort.top();
      topsort.pop();
      if(!vis[tt]) {
        cc.clear();
        dfs2(tt);
        for(int x: cc) ord[x] = nxt;
        nxt++;
      }
    }
    // if i and n+i are in the same scc, reject
    for(int i=0; i<n; i++) {
      if(ord[i] == ord[n+i]) return {};
      else if(ord[i] > ord[n+i]) sol[i] = 0;
      else sol[i] = 1;
    }
    return sol;
  }
};
