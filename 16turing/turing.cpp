#include <iostream>
#include <vector>
using namespace std;

/*
 * Solution sketch:
 * Realized all inputs only contained # separators and 01.
 * Checked valid values (actually reach "end") for all possible values of.
 * #5bits#
 * #5bits#5bits#
 * #5bits#5bits#5bits#
 * #5bits#5bits#5bits#
 * #5bits#10bits#
 * 
 * Given a set of blocs with a_i bits, n>1:
 * #a0#a1#a2#..#an#
 * ans = a0*(a1+a2+..+an)
 * Representend in a0 bits.
 * There is never overflow (would never reach "end").
 * 
 * In case n=1, solution = first_block-1 in a0 bits.
 */

typedef long long ll;


//Int to binary.
string itob(ll x, int bits) {
  string ans = "";
  while(x>0 or bits>0) {
    ans=char((x&1)+'0') + ans;
    x/=2;
    --bits;
  }
  return ans;
}

ll btoi(string& s) {
  int n = s.size();
  ll resultado = 0;
  for (int i = 0; i < n; ++i) {
    resultado *= 2LL;
    resultado += s[i]-'0';
  }
  return resultado;
}

//Saves the split in vsplit and returns the bits of the first block.
//Pre: vsplit is empty.
int split(string& s, vector<ll>& vsplit) {
  string w = "";
  int firstbits = -1;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i]=='#') {
      if (w.size() > 0) {
        if (firstbits == -1) firstbits = w.size(); // Size of first block.
        vsplit.push_back(btoi(w));
      }
      w = "";
    }
    else w+=s[i];
  }
  return firstbits;
}

int main() {
  string s;
  while(cin>>s) {
    vector<ll> vsplit(0);
    int firstbits = split(s, vsplit);
    int n = vsplit.size();
    //if n==1, the only valid string is #00...01#, which generates #00..00#
    if (n==1) cout << "#" << itob(vsplit[0]-1, firstbits) << "#" << endl;
    else {
      ll resultado = vsplit[0];
      ll suma = 0;
      for (int i =1; i < n; ++i) suma+=vsplit[i];
      resultado*=suma;
      cout << "#" << itob(resultado, firstbits) << "#" << endl;
    }
  }
}
