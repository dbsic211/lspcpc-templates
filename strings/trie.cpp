struct Trie {
  int nodes = 0;
  vector<vector<pair<int,int> > >adj;
  vector<int>words,ends;
  string save;
  void u(int idx, int node) {
    if(idx==save.size()){
      words[node]++;
      ends[node]++;
      return;
    }
    for(pair<int,int>x:adj[node]){
      if(x.second==save[idx]){
        u(idx+1, x.first); 
        words[node]=ends[node];
        for(pair<int,int>y:adj[node]){
          words[node]+=words[y.first];
        }
        return;
      }
    }
    adj.push_back({});
    words.push_back(0);
    ends.push_back(0);
    adj[node].push_back({nodes, save[idx]});
    nodes++;
    u(idx+1, nodes-1);
    words[node]=ends[node];
    for(pair<int,int>y:adj[node]){
      words[node]+=words[y.first];
    }
  }
  int search(int idx, int node) {
    if(idx==save.size()) return words[node];
    for(pair<int,int> x:adj[node]){
      if(save[idx]==x.second) return search(idx+1, x.first);
    }
    return 0;
  }
  void insert(string s){
    save=s;
    if(nodes == 0) {
      nodes = 1;
      adj.push_back({});
      words.push_back(0);
      ends.push_back(0);
    }
    u(0, 0);
  }
  int countPrefix(string s){
    save=s;
    return search(0, 0);
  }
};
