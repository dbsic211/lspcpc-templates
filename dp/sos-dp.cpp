#include <bits/stdc++.h>
using namespace std;
int main() {
  int N;
  cin >> N;
  int a[(1<<N)];
  for(int i=0; i<(1<<N); i++) a[i] = 0;
  //Add weights to a[i]
  
  int f[(1<<N)];
  for(int i=0; i<(1<<N); i++) f[i] = a[i];
  for(int i=0; i<N; i++) {
    for(int j=0; j<(1<<N); j++) {
      if(j & (1<<i)) {
        f[j] += f[j ^ (1<<i)];
      }
    }
  }
}
