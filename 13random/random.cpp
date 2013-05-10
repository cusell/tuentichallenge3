//Let q be the number of queries and n the number of input numbers.
//Complexity: O(n*log(n) + q*log(n))
#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef long long ll;
typedef vector<ll> Vl;
typedef map<ll, ll> M;

Vl T;
int n,sz;
const ll INF = 1000000000000000000LL;

//[a,b) node interval
//[x,y) query interval
ll getval(int p, int a, int b, int x, int y) {
    if (b<=x or a>=y) return -INF;
    if (a>=x and b<=y) return T[p];
    return max(getval(2*p, a,(a+b)/2,x,y), getval(2*p+1, (a+b)/2,b,x,y));
}

//Returns max(v[x], .., v[y]). [x,y]
ll getval(int x, int y) {
  return getval(1,0,sz,x,y+1);
}

//Sets the position p to value val.
void set(int p, ll val) {
    p+=sz;
    T[p]=val;
    for(p/=2;p>0;p/=2) T[p]=max(T[2*p],T[2*p+1]);
}

void createTree(Vl& v) {
  n = v.size();
  sz=1;
  while (sz<n) sz*=2;
  T = Vl(2*sz,0);
  //Could be done in O(n) instead of O(n logn)
  //but it suffices by far for 10^6
  for (int i=0;i<n;++i) set(i,v[i]);
}

int main() {
  int t; cin >> t;
  for (int cas=1;cas<=t;++cas) {
    int vn, m;
    cin >> vn >>m;
    Vl v(vn);
    for (int i = 0; i < vn; ++i) cin >> v[i];
    v.push_back(INF); ++vn;
    M sig, ant, ini, fi, mv;
    //Pre: v increasing!
    
    Vl vlen(0);
    int beg=0, prenum=-1;
    for (int i=1;i<vn;++i) { //uses the last INF>all
      if (v[i]>v[i-1]) {
        int k = v[i-1];
        vlen.push_back(i-beg);
        mv[k] = int(vlen.size())-1; //where is his maximum on the vlen vector
        ant[k] = prenum;
        if (v[i]==INF)  sig[k]=-1;
        else sig[k] = v[i];
        ini[k] = beg;
        fi[k]=i-1;
        prenum=k;
        beg=i;
      }
    }
    createTree(vlen);
    
    cout << "Test case #" << cas << endl;
    int a, b;
    while(m--) {
      cin >> a >> b;
      --a; --b;
      ll ans=-INF,ret;
      ll x = sig[v[a]], y = ant[v[b]];
      //Get the repeated numbers strictly inside the interval
      if (v[a]!=v[b] and x!=-1 and x!=v[b] and
          y!=-1 and y!=v[a]) {
        ret = getval(mv[x], mv[y]);
        ans=max(ans, ret);
      }
      //Get the split repeated sequences on the extremes.
      ans=max(ans,fi[v[a]]-a+1);
      ans=max(ans,b-ini[v[b]]+1);
      cout << ans << endl;
    }
  }
}
