vector<int> z_function(string s) { // Note how z[0] is defined
  if(s.empty()) return {};
  int n = s.size();
  vector<int> z(n, 0);
  int l=0, r=0;
  z[0]=n;
  for(int i=1; i<n; i++) {
    if(i<r) z[i] = min(r-i, z[i-l]);
    while(i+z[i] < n && s[i+z[i]] == s[z[i]]) z[i]++;
    if(i+z[i] > r) l=i, r=i+z[i];
  }
  return z;
}
