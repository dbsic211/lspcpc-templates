struct pam {
  vector<vector<int>>pam;
  vector<vector<int>>revfail;
  vector<int> oddrt,evenrt,fail,len,alleq,corr;
  vector<int>cnt;
  string s;//the string itself
  // Declare other variables here
  void init(int n) {
    pam.resize(n + 5);
    revfail.resize(n + 5);
    fail.resize(n + 5);
    len.resize(n + 5);
    alleq.resize(n + 5);
    corr.resize(n + 5);
    cnt.resize(n + 5);
    // Initialize other arrays here
  }
  void append(char c) {
    int i = s.size();
    s += c;
    if(i == 0) {
      fail[0] = -1;
      len[0] = 1;
      cnt[0] = 1;
      alleq[0] = 1;
      corr[0] = 0;
      oddrt.push_back(0);
      return;
    }
    int nxt=corr[i-1];
    while(nxt!=-1){
      if(alleq[nxt] && s[i]==s[i-1]) {
        bool done=0;
        for(int x:revfail[nxt]){
          if(s[x]==s[i] && len[x]==len[nxt]+1){
            cnt[x]++;
            corr[i]=x;
            done = 1; 
            break;
          }
        }
        if(done) break;
        fail[i]=nxt;
        revfail[nxt].push_back(i);
        len[i]=len[nxt]+1;
        alleq[i]=1;
        cnt[i]=1;
        corr[i]=i;
        break;
      }
      if(i-len[nxt]-1>=0 && s[i]==s[i-len[nxt]-1]) {
        bool done=0;
        for(int x:pam[nxt]){
          if(s[x]==s[i]){
            done=1;
            cnt[x]++;
            corr[i]=x;
            break;
          }
        }
        if(done)break;
        pam[nxt].push_back(i);
        corr[i]=i;
        cnt[i]=1;
        len[i]=len[nxt]+2;
        alleq[i]=alleq[nxt]&(s[i]==s[i-1]);
        int again=nxt;
        fail[i]=-1;
        while(fail[again]!=-1){
          again=fail[again];
          if(i-len[again]-1>=0 && s[i-len[again]-1]==s[i]){
            for(int x:pam[again]){
              if(s[x]==s[i]&&len[x]==len[again]+2){
                fail[i]=x;
                revfail[x].push_back(i);
                break;
              }
            }
            break;
          }
          if(alleq[again] && s[i]==s[i-1]){
            for(int x:revfail[again]){
              if(s[x]==s[i]&&len[x]==len[again]+1){
                fail[i]=x;
                revfail[x].push_back(i);
                break;
              }
            }
            break;
          }
        }
        if(fail[i]==-1){
          for(int x:oddrt){
            if(s[x]==s[i]){
              fail[i]=x;
              revfail[x].push_back(i);
              break;
            }
          }
        }
        break;
      }
      else nxt=fail[nxt];
    }
    if(nxt==-1){//single character
      bool done=0;
      for(int x: oddrt){
        if(s[x]==s[i]){
          corr[i]=x;
          cnt[x]++;
          done= 1;break;
        }
      }
      if(!done) {
        fail[i] = -1;
        len[i] = 1;
        alleq[i] = 1;
        cnt[i] = 1;
        corr[i] = i;
        oddrt.push_back(i);
      }
    }
    if(len[i] == 2) evenrt.push_back(i);
  }
  public:
  // The following dfs calculates the occurrences of each palindromic substring
  int ans = 0;
  void dfs(int node) {
    for(int x: revfail[node]) {
      dfs(x);
      cnt[node] += cnt[x];
    }
    ans = max(ans, cnt[node] * len[node]); 
  }
  int solve() {
    for(int x: oddrt) dfs(x);
    return ans;
  }
};
