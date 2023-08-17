int v[4] = {2, 13, 23, 120734269};
__int128 bm_(long long b, long long p, long long mod ) {
  if(p == 0) return 1 % mod;
  __int128 wfg = bm_(b, p >> 1, mod);
  if(p & 1) return (((wfg * wfg) % mod) * b) % mod;
  return (wfg* wfg) %mod;
}
bool isprime(int n) {
  if(n == 1) return 0;
  for(int i=0; i<4; i++) if(n == v[i]) return 1;
  if(n % 2 == 0) return 0;
  int d = n-1, r = 0;
  while(!(d & 1)) d >>= 1, r++;
  for(int k=0; k<4; k++) { // witness
    int a = v[k];
    int x = bm_(a, d, n);
    if(x == 1 || x == n-1) continue;
    bool cont = 0;
    for(int h=0; h<r-1; h++) {
      __int128 y = x;
      y *= y;
      y %= n;
      x = y;
      if(x == n-1) {
        cont = 1; break;
      }
    }
    if(cont) continue;
    return 0;
  }
  return 1;
}
