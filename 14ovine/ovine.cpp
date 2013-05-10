#include <iostream>
#include <vector>
using namespace std;

/*
 * Since the given input were famous quotes:
 * - Aproximated strings with ovineaprox.cpp
 * - Looked for the quotes.
 * - Forced a matching to see if all match.
 * - Used the longest one given in the input.
 */

const string sok = "Some humans would do anything to see if it was possible to do it. If you put a large switch in some cave somewhere, with a sign on it saying 'End-of-the-World Switch. PLEASE DO NOT TOUCH', the paint wouldn't even have time to dry.";
const string sci = "46fb200144df180dba5c8f52481c0ef515d9e963d0008b859c121b51ee8d0ca8e98b01d89a841257a1559174765d8ea95b9e69aaf014624eb5be51c415cfc5854aaa6c18b929b496e71a721303846856ae31c6d24529f4a9c19ef46a75819ea156598893e644f2c7f7ae39381b0184b5c937f8473a3800842e822014c4e8a94cc36373e81a6ee94632678625f2a5ff2eeb4eeae42d4190791cfd8fcc5f8dec2c2c5547fd63ebcb8a3c56303b4976dff9502d30e85955ed128114eb094b1667bb7da282be7ed7f1873d8e8c31d18ef24a48e990db46f5a591ecbc33704380a1b9b8babcdb4fe3";
//sizes 230, 460

inline int val(char c) {
  if (c>='0' and c<='9') return c-'0';
  return c-'a'+10;
}

int main() {
  vector<int> vkey;
  int M = sok.size();
  //Calculate the key for the given ok string, and cipher string (sok, sci).
  for (int i = 0; i < M; ++i) {
    for (int key=0;key<16*16;++key) {
      char c = char((val(sci[2*i])*16+val(sci[2*i+1]))^key);
      if (c==sok[i]) vkey.push_back(key);
    }
  }

  string s;
  while(cin>>s) {
    int n = s.size();
    string ans="";
    //if input is larger than the largest example, I can't solve it.
    //And the key doesn't look like it follows a pattern...
    for (int i=0;i<n/2;++i) if (i<vkey.size()) {
      ans += char((val(s[2*i])*16+val(s[2*i+1]))^vkey[i]);
    }
    cout << ans << endl;
  }
}
