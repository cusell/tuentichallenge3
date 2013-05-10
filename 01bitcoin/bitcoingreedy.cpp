//Greedy implementation - Complexity O(n)
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

typedef long long ll;
typedef vector<ll> Vll; //Daily value

const ll INF = 1000000000000000000LL;

int main() {
  int t; cin >> t;
  while(t--) {
    ll eur,btc = 0; cin >> eur;
    stringstream ss;
    string s;
    getline(cin,s); //Read last line endl
    getline(cin,s); //Read whole line
    ss << s;
    ll x;
    Vll v(0);
    while(ss>>x) v.push_back(x); //Save input into vector
    int n = int(v.size());
    for (int i=0;i<n;++i) {
      //If it's a local minimum, buy all bitcoins.
      if ((i-1<0 or v[i-1] >= v[i]) and (i+1>=n or v[i] <=v[i+1])) {
        btc+=eur/v[i];
        eur%=v[i];
      }
      //If it's a local maximum, sell all bitcoins.
      else if ((i-1<0 or v[i-1] <= v[i]) and (i+1>=n or v[i] >=v[i+1])) {
        eur+=btc*v[i];
        btc=0;
      }
      if(i+1==n) eur+=btc*v[i]; //The last day, sell all BTC no matter what.
    }
    cout << eur << endl;
  }
}
