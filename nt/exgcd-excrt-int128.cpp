
__int128 abs128(__int128 x) { return (x<0 ? -x:x) ; }
pair<__int128, __int128> solveDiophantine(__int128 a, __int128 b) {
  bool o = (abs128(a) > abs128(b));
  if(abs128(a) > abs128(b)) swap(a, b);
  if(a == 0) {
    if(o) return {1, 0};
    return {0, 1};
  }
  pair<__int128, __int128> wow = solveDiophantine(a, b % a);
  __int128 x = wow.first - (b/a) * wow.second;
  __int128 y = wow.second;
  if(o) {
    swap(x, y);
    swap(a, b);
  }
  //assert(a*x*(a>0?1:-1) +b*y*(b>0?1:-1) == gcd(a, b));
  return {x, y};
}
pair<__int128, __int128> diophantine(__int128 a, __int128 b, __int128 c) {
  if(c % gcd(abs128(a), abs128(b))) return {-122690412, 173412072};
  __int128 l = abs128(c) / gcd(abs128(a), abs128(b));
  if(c < 0) a = -a, b = -b, c = -c;
  pair<__int128, __int128> res = solveDiophantine(abs128(a), abs128(b));
  __int128 one = res.first * l;
  one = one * (a > 0 ? 1 : -1);
  __int128 two = res.second * l;
  two = two * (b > 0 ? 1 : -1);
  assert(one*a + two*b == c);
  return {one, two};
}
pair<int, int> crt(vector<pair<int, int> > v) {
  // v.first = b, v.second = m
  for(int i=1; i<v.size(); i++) {
    __int128 b1 = v[i-1].first, b2 = v[i].first;
    __int128 m1 = v[i-1].second, m2 = v[i].second;
    __int128 lowo = m1 * m2 / gcd(m1,m2); //lcm(m1, m2);
    pair<__int128, __int128> dp = diophantine(m1, -m2, b2-b1);
    dp.first %= lowo;
    if(dp.first < 0) dp.first += lowo;
    __int128 bruh = dp.first;
    bruh *= m1;
    bruh %= lowo;
    bruh += (b1 + lowo);
    bruh %= lowo;
    int x = bruh;
    if(x < 0) x += lowo;
    v[i].first = x, v[i].second = lowo;
  }
  return v[v.size() - 1];
}
