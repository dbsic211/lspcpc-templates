int kth_powers(int n, int k) {
  // Calculates 1^k + 2^k + ... + n^k modulo MOD
  // Special thanks: https://codeforces.com/contest/622/submission/109747844
  int a[k+3], f[k+3], g[k+3];
  for(int i=0; i<=k+2; i++) a[i] = f[i] = g[i] = 0;
  for(int i=1;i<=k+2 && i<=n;i++) {
    a[i]=(a[i-1]+bm(i,k)) % MOD;
  }
  if(n<=k+2) return a[n];
  int ans = 0;
  int now; 
  now=f[0]=g[0]=1;
	for(int i=1;i<=k+2;i++) {
		now=now*(n-i)%MOD,f[i]=f[i-1]*i%MOD,g[i]=-g[i-1]*i%MOD;	
  }
	for(int i=1;i<=k+2;i++) {
		ans=(ans+a[i]*now%MOD*bm(n-i, MOD-2)%MOD*bm(f[i-1]*g[k+2-i]%MOD, MOD-2))%MOD;
  }
  return (ans + MOD) % MOD;
}
