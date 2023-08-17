pair<int, int> solveDiophantine(int a, int b) {
  bool o = (abs(a) > abs(b));
  if(abs(a) > abs(b)) swap(a, b);
  if(a == 0) {
    if(o) return {1, 0};
    return {0, 1};
  }
  pair<int, int> wow = solveDiophantine(a, b % a);
  int x = wow.first - (b/a) * wow.second;
  int y = wow.second;
  if(o) {
    swap(x, y);
    swap(a, b);
  }
  //assert(a*x*(a>0?1:-1) +b*y*(b>0?1:-1) == gcd(a, b));
  return {x, y};
}
pair<int, int> diophantine(int a, int b, int c) {
  if(c % gcd(abs(a), abs(b))) return {-122690412, 173412072};
  int l = abs(c) / gcd(abs(a), abs(b));
  if(c < 0) a = -a, b = -b, c = -c;
  pair<int, int> res = solveDiophantine(abs(a), abs(b));
  int one = res.first * l;
  one = one * (a > 0 ? 1 : -1);
  int two = res.second * l;
  two = two * (b > 0 ? 1 : -1);
  assert(one*a + two*b == c);
  return {one, two};
}
pair<int, int> crt(vector<pair<int, int> > v) {
  // v.first = b, v.second = m
  for(int i=1; i<v.size(); i++) {
    int b1 = v[i-1].first, b2 = v[i].first;
    int m1 = v[i-1].second, m2 = v[i].second;
    int lowo = lcm(m1, m2);
    pair<int, int> dp = diophantine(m1, -m2, b2-b1);
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
