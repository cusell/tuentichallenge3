//Backtracking + memoization implementation - Complexity O(3^n)
//Memoization guarantees to only visit each state once.
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> Pl;
typedef pair<int, Pl> PP;

//Global vector and map to be accessible without needing to pass by reference.
vector<ll> v; //Daily value
map<PP, ll> memo; //Memoization of backtracking states.

ll GetProfit(int p, ll eur, ll btc) {
  if (p==v.size()) return eur;
  PP m = PP(p,Pl(eur,btc));
  if (memo.count(m)) return memo[m];
  ll ans = 0;
  //v[p] can't be zero, that would yield to infinity revenue
  ans = GetProfit(p + 1, eur, btc); //ignore price
  ans = max(ans, GetProfit(p + 1, eur%v[p], btc + eur/v[p])); //spend all in btc
  ans = max(ans, GetProfit(p+1, eur + btc*v[p], 0)); //sell all
  return memo[m] = ans;
}

//BTC donations are welcome :-): 15cXuPdHPXod24xfsweuuJjSxSg5KgLL65

int main() {
  int t; cin >> t;
  while (t--) {
    memo.clear();
    int n; cin >> n;
    stringstream ss;
    string s;
    getline(cin,s); //Read last line endl
    getline(cin,s); //Read whole line
    ss << s;
    ll x;
    v = vector<ll>(0);
    while(ss>>x) v.push_back(x); //Save input into vector
    cout << GetProfit(0, n, 0) << endl;
  }
}
