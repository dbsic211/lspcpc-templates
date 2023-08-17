// min COST max flow
// O(Fm log m) where F denotes the max flow


struct flow_graph {
  struct edge {
    int to, cost, flow, revid; // reverse edge id in adjacency list
  };
  vector<vector<edge> > adj, adj2;
  bool computed = 0;
  int mc, mf;
  int n, s, t;
  public:
  void init(int n_, int s_, int t_) {
    n = n_;
    s = s_;
    t = t_;
    adj.resize(n + 10);
  }
  void addedge(int u, int v, int cost, int flow) {
    int au = adj[u].size();
    int av = adj[v].size();
    adj[u].push_back({v, cost, flow, av});
    adj[v].push_back({u, -cost, 0, au});
  }
  void eval() {
    computed = 1;
    mc = mf = 0;
    int h[n+1];
    for(int i=1; i<=n; i++) h[i] = 0;
    while(1) {
      int dist[n+1];
      pair<int, int> pre[n+1];
      bool vis[n+1];
      priority_queue<pair<int, int>, vector<pair<int, int> > ,greater<pair<int, int> > > pq;
      for(int i=1; i<=n; i++) {
        dist[i] = 1e15;
        vis[i] = 0;
      }
      dist[s] = 0;
      pq.push({0, s});
      while(pq.size()) {
        pair<int, int> t = pq.top(); pq.pop();
        if(!vis[t.second]) {
          vis[t.second] = 1;
          int idx = 0;
          for(edge x: adj[t.second]) {
            if(!vis[x.to] && x.flow > 0 && dist[x.to] > dist[t.second] + x.cost + h[t.second] - h[x.to]) {
              dist[x.to] = dist[t.second] + x.cost + h[t.second] - h[x.to];
              pre[x.to] = {t.second, idx};
              pq.push({dist[x.to], x.to});
            }
            idx++;
          }
        }
      }
      if(dist[t] == 1e15) break;

      int e = 1e15; // amount of flow
      int cur = t;
      while(cur != s) {
        int pv = pre[cur].first;
        int bc = pre[cur].second; // pv -> cur
        int lo = adj[pv][bc].revid; // cur -> pv
        e = min(e, adj[pv][bc].flow);
        cur = pv;
      }
      cur = t;
      while(cur != s) {
        int pv = pre[cur].first;
        int bc = pre[cur].second; // pv -> cur
        int lo = adj[pv][bc].revid; // cur -> pv
        adj[pv][bc].flow -= e;
        adj[cur][lo].flow += e;
        cur = pv;
      }
      mc += (dist[t] - (h[s] - h[t])) * e;
      mf += e;
     // cout << e << " " << (dist[t] - (h[s] - h[t])) << "\n";
      for(int i=1; i<=n; i++) h[i] += dist[i];
    }
  }
  int mincost() {
    if(!computed) eval();
    return mc;
  }
  int maxflow() {
    if(!computed) eval();
    return mf;
  }
};
