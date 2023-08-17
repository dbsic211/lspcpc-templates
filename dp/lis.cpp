int lis(vector<int> a) {
  int n = a.size();
  int bucket[n+1];
  for(int i=1; i<=n; i++) bucket[i] = 1e18;
  int ans = 1;
  for(int x: a) {
    auto it = lower_bound(bucket + 1, bucket +n +1, x);
    int d = distance(bucket, it);
    ans = max(ans, d);
    bucket[d] = min(bucket[d], x);
  }
  return ans;
}
