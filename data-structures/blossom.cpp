// Not blossom algorithm
// 陌上花開
struct blossom {
  struct bit {
    vector<int> v;
    int stok;

    void resize(int k) {
      stok = k + 5;
      v.resize(stok);
    }
    void add(int x, int val) {
      for(;x<stok;x+=x&-x) v[x] += val;
    }
    int sum(int x) {
      int s = 0;
      for(;x;x-=x&-x) s += v[x];
      return s;
    }
  };
  vector<int> ans, compress;
  int maxt = 0;
  struct point {
    int x, y, t, v, id;
    // (x, y, t) are the three dimensions, v is the value to add
    // id = 0 for "points"
    // id != 1 for "queries", id = 1 for add and id = -1 for subtract
    // can be modified
  };
  vector<point> points;

  void cdq(int l, int r) {
    if(l == r) {
      return;
    }
    int m = (l + r) >> 1;
    cdq(l, m);
    cdq(m+1, r);
    // mergesort by y-coordinate while doing 2-ptr
    vector<point> neworder;
    int j = l-1;
    vector<int> tt;
    for(int i=l; i<=r; i++) tt.push_back(points[i].t);
    sort(tt.begin(), tt.end());
    int totn = 1;
    compress[tt[0]] = 1;
    for(int i=1; i<tt.size(); i++) {
      if(tt[i] != tt[i-1]) {
        totn++;
        compress[tt[i]] = totn;
      }
    }
    bit newbit;
    newbit.resize(totn);
    for(int i=m+1; i<=r; i++) {
      while(j+1 <= m && points[j+1].y <= points[i].y) {
        neworder.push_back(points[j+1]);
        if(points[j+1].id == 0) {
          newbit.add(compress[points[j+1].t], points[j+1].v);
        }
        j++;
      }
      neworder.push_back(points[i]);
      if(points[i].id != 0) {
        int res = newbit.sum(compress[points[i].t]);
        ans[points[i].t] += res * points[i].id;
      }
    }
    while(j+1 <= m) {
      neworder.push_back(points[j+1]);
      j++;
    }
    for(int i=l; i<=r; i++) points[i] = neworder[i-l];
  }
  public:
  static bool diagonal1(point one, point two) { 
    if(one.x == two.x) return one.t < two.t; 
    else return one.x < two.x; 
  }
  void add_point(int x, int y, int t, int v) {
    points.push_back({x, y, t, v, 0});
    maxt = max(maxt, t);
  }
  void add_query(int l1, int r1, int l2, int r2, int t) {
    assert(l1 <= l2 && r1 <= r2);
    points.push_back({l2, r2, t, 0, 1});
    points.push_back({l1 - 1, r2, t, 0, -1});
    points.push_back({l2, r1 - 1, t, 0, -1});
    points.push_back({l1 - 1, r1 - 1, t, 0, 1});
    maxt = max(maxt, t);
  }
  void compile() {
    ans.resize(maxt + 5);
    compress.resize(maxt + 5);
    sort(points.begin(), points.end(), diagonal1);
    cdq(0, points.size() - 1);
  }
  vector<int> get_answers() { // Get answers to all sum query
    vector<int> good;
    for(int i=1; i<=maxt; i++) good.push_back(ans[i]);
    return good;
  }
};
