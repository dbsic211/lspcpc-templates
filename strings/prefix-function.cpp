vector<int> prefix_function(vector<int> t) {
  int n = t.size(); vector<int> lps(n, 0);
  for(int i=1; i<n; i++) {
    int j = lps[i-1]; while(j > 0 && t[i] != t[j]) j = lps[j-1];
    lps[i] = (t[i] == t[j] ? j+1 : 0); 
  } return lps;
}
