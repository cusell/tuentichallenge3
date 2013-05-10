#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;
typedef long double ld;

ll fraction_ceil(ll a, ll b) {
  return floor(ld(a)/ld(b)+1)+1;
}

int main() {
  int t; cin >> t;
  while(t--) {
    ll w, h, s, c, g;
    cin >> w >> h >> s >> c >> g;
    //Each second, w extra enemies.
    if (w*s<=g) cout << -1 << endl; //If I can buy w archers -> forever alive!
    else{
      ll ans=0;
      for (ll arc=0;arc<=w and arc*s<=g;++arc) { //How many archers.
        //Number of Crematoriums.
        ll numb = (g-s*arc)/c;
        //Seconds before creamtorium is used.
        ll k = fraction_ceil(w*(h-1), w-arc);
        ans=max(ans, (numb+1)*(k-1));
      }
      cout << ans << endl;
    }
  }
}
