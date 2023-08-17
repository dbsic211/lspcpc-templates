struct bipartite_graph {
  vector<vector<int> > adj;
  int n, m;
  bool done_init = 0;
  void init(int lsize, int rsize) {
    n = lsize, m = rsize;
    adj.resize(n+4);
    done_init = 1;
  }
  void addedge(int lnode, int rnode) {
    if(!done_init) {
      cout << "bipartite_graph error: called addedge() before init()\n"; exit(0);
    }
    adj[lnode].push_back(rnode);
  }
  vector<int> occupied;
  vector<bool> vis;
  bool run(int node) {
    if(vis[node]) return 0;
    vis[node] = 1;
    for(int x: adj[node]) {
      if(!occupied[x] || run(occupied[x])) {
        occupied[x] = node; return 1;
      }
    }
    return 0;
  }
  int max_matching() {
    int answer = 0;
    if(!done_init) {
      cout << "bipartite_graph error: called addedge() before init()\n"; exit(0);
    }
    occupied.resize(m+4);
    vis.resize(n+4);
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=n; j++) vis[j] = 0;
      answer += run(i);
    }
    return answer;
  }
};
