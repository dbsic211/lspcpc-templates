//https://www.luogu.com.cn/problem/P5367
#include "bits/stdc++.h"
using namespace std;
#define int long long
const int MAXN = 1e6 + 10;
const int MOD = 998244353;
int bit[MAXN];
void add(int x, int v) {
  for(;x<MAXN;x+=x&-x) bit[x]+=v;
}
int sum(int x) {
  int s=0;
  for(;x;x-=x&-x) s+=bit[x];
  return s;
}
int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin>>n;
  int p[n+1];
  for(int i=1;i<=n;i++)cin>>p[i];
  int fac[n+1];
  fac[0]=1;
  for(int i=1;i<=n;i++)fac[i]=(fac[i-1]*i)%MOD;
  int ans=1;
  for(int i=1;i<=n;i++){
    int rk=p[i]-sum(p[i]);
    ans+=fac[n-i]*(rk-1);
    add(p[i],1);
    ans%=MOD;
  }
  cout<<ans<<"\n";
}
