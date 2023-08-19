int bigmod(int b,int p,int m){
    b%=m;
    if (!b) return 0;
    int ans=1;
    while (p){
        if (p&1LL) ans=ans*b%m;
        p>>=1LL;
        b=b*b%m;
    }
    return ans;
}
const int mod=998244353;
const int g=3;
int prec_f[1000010],prec_finv[1000010],prec_inv[1000010];
void init(){
    prec_f[0]=prec_f[1]=prec_inv[0]=prec_inv[1]=prec_finv[0]=prec_finv[1]=1;
    for (int i=2; i<1000010; i++){
        prec_f[i]=prec_f[i-1]*i%mod;
        prec_inv[i]=prec_inv[mod%i]*(mod-mod/i)%mod;
        prec_finv[i]=prec_finv[i-1]*prec_inv[i]%mod;
    }
}
vector <int> rev,roots;
void dft(vector <int> &a){
    int n=a.size();
    int b=__builtin_ctz(n)-1;
    rev.clear();
    rev.resize(n);
    for (int i=0; i<n; i++) rev[i]=rev[i>>1LL]>>1LL|(i&1LL)<<b;
    roots={0,1};
    if (n>2){
        roots.resize(n);
        b=1;
        while ((1LL<<b)<n){
            int e=bigmod(g,(mod-1)>>(b+1),mod);
            for (int i=1LL<<(b-1); i<(1LL<<b); i++){
                roots[2*i]=roots[i];
                roots[2*i+1]=roots[i]*e%mod;
            }
            b++;
        }
    }
    for (int i=0; i<n; i++){
        if (rev[i]<i) swap(a[i],a[rev[i]]);
    }
    for (int k=1; k<n; k<<=1LL){
        for (int i=0; i<n; i+=2*k){
            for (int j=0; j<k; j++){
                int u=a[i+j],v=a[i+j+k]*roots[j+k]%mod;
                a[i+j]=(u+v)%mod;
                a[i+j+k]=(u-v+mod)%mod;
            }
        }
    }
}
void idft(vector <int> &a){
    int n=a.size();
    reverse(a.begin()+1,a.end());
    dft(a);
    int inv=bigmod(n,mod-2,mod);
    for (int i=0; i<n; i++) a[i]=a[i]*inv%mod;
}
vector <int> mul(vector <int> a,vector <int> b){
    int n=a.size(),m=b.size();
    int tot=n+m-1;
    int sz=(1ll<<(__lg(tot*2-1)));
    a.resize(sz); b.resize(sz);
    dft(a); dft(b);
    for (int i=0; i<sz; i++) a[i]=a[i]*b[i]%mod;
    idft(a);
    while (a.size()>1&&!a.back()) a.pop_back();
    return a;
}
vector <int> inv(vector <int> a){
    int n=a.size();
    if (n==1) return {bigmod(a[0],mod-2,mod)};
    vector <int> f0;
    for (int i=0; i<(n+1)/2; i++) f0.pb(a[i]);
    f0=inv(f0);
    vector <int> g=mul(mul(f0,f0),a);
    vector <int> ret(n);
    for (int i=0; i<n; i++){
        if (i<(n+1)/2) ret[i]=2*f0[i]%mod;
        ret[i]=(ret[i]+mod-g[i])%mod;
    }
    return ret;
}
vector <int> ln(vector <int> a){
    int n=a.size();
    if (n==1) return {0};
    vector <int> ap(n-1);
    for (int i=1; i<n; i++) ap[i-1]=i*a[i]%mod;
    ap=mul(ap,inv(a));
    vector <int> ret(n,0);
    for (int i=0; i<n-1; i++) ret[i+1]=prec_inv[i+1]%mod*ap[i]%mod;
    return ret;
}
vector <int> exp(vector <int> a){
    int n=a.size();
    if (n==1) return {1};
    vector <int> f0;
    for (int i=0; i<(n+1)/2; i++) f0.push_back(a[i]);
    f0=exp(f0);
    vector <int> l=f0;
    l.resize(n);
    l=ln(l);
    for (int&i:l) i=(mod-i)%mod;
    vector <int> v=a;
    a[0]++;
    for (int i=0; i<n; i++) a[i]=(a[i]+l[i])%mod;
    a=mul(a,f0);
    a.resize(n);
    return a;
}
