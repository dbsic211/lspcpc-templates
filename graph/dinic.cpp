struct maxflow_graph { //maxflow without mincost :(
  int n, s, t;
  vector<vector<pair<int, int> > > adj;
  vector<vector<int> > comp;
  vector<int> dist;
  const int maxedgeflow = 3e9; // max flow for a single edge
  map<pair<int,int>, int> exist;

  void init(int n_, int s_, int t_) {
    n = n_, s = s_, t = t_; // node count, source node, sink node
    adj.resize(n + 5);
    dist.resize(n + 5);
    comp.resize(n + 5);
  }
  void addedge(int u, int v, int f) {
    // adding a single direction edge u->v with flow f
    if(exist[{u, v}]) {
      int uid = exist[{u, v}];
      adj[u][uid].second += f;
      return;
    }
    int us = adj[u].size(), vs = adj[v].size();
    exist[{u, v}] = us, exist[{v, u}] = vs;
    adj[u].push_back({v, f});
    comp[u].push_back(vs);
    adj[v].push_back({u, 0});
    comp[v].push_back(us);
  }
  int dfs(int node, int flow) {
    if(node == t) return flow;
    for(int i=0; i<adj[node].size(); i++) {
      if(dist[adj[node][i].first] == dist[node] + 1 && adj[node][i].second > 0) {
        int dd = dfs(adj[node][i].first, min(flow, adj[node][i].second));
        if(dd > 0) {
          adj[node][i].second -= dd;
          adj[adj[node][i].first][comp[node][i]].second += dd;
          return dd;
        }
      }
    }
    return 0;
  }
  int maxflow() {
    bool vis[n+1];
    for(int i=0; i<=n; i++) vis[i] = 0;
    for(int i=0; i<=n; i++) dist[i] = 1e9;
    dist[s] = 0;
    queue<int> lv;
    lv.push(s);
    while(lv.size()) {
      int f = lv.front(); lv.pop();
      if(!vis[f]) {
        vis[f] = 1;
        for(pair<int, int> x: adj[f]) {
          if(!vis[x.first] && dist[x.first] > dist[f] + 1 && x.second > 0) {
            dist[x.first] = dist[f] + 1;
            lv.push(x.first);
          }
        }
      }
    }
    if(dist[t] == 1e9) return 0;
    int answer = 0;
    while(1) {
      int d = dfs(s, maxedgeflow);
      if(!d) break;
      answer += d;
    }
    if(answer == 0) return 0;
    return answer + maxflow();
  }
};
