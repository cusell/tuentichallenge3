//Compile: g++ secret.cpp -o secret -O2 -lcrypto -lssl
#include <iostream>
#include <algorithm>
#include <set>
#include <openssl/md5.h>
#include <cstring>
#include <cstdio>
using namespace std;

//Any valid game and corresponding hash can work here.
const string game = "Tzo0OiJnYW1lIjozOntzOjExOiIAZ2FtZQBib2FyZCI7Tzo1OiJib2FyZCI6Mzp7czoxMjoiAGJvYXJkAGJvYXJkIjthOjM6e2k6MDthOjM6e2k6MDtiOjA7aToxO3M6MToiWCI7aToyO2I6MDt9aToxO2E6Mzp7aTowO3M6MToiTyI7aToxO3M6MToiWCI7aToyO2I6MDt9aToyO2E6Mzp7aTowO3M6MToiTyI7aToxO3M6MToiWCI7aToyO2I6MDt9fXM6MTM6IgBib2FyZAB3aW5uZXIiO3M6MToiWCI7czoxNDoiAGJvYXJkAHdpbkxpbmUiO3M6MjoifDEiO31zOjE1OiIAZ2FtZQBuZXh0UGllY2UiO3M6MToiTyI7czoxMToidmVyc2lvbkZpbGUiO3M6MzU6Ii9ob21lL3R0dC9kYXRhL21lc3NhZ2VzL3ZlcnNpb24udHh0Ijt9";
const string hash = "144e7fe305f8735b6a5e67f6520117c7";

string md5(string s) { //n = real size
    int m;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);
    MD5_Update(&c, s.c_str(), s.size());
    MD5_Final(digest, &c);

    for (m = 0; m < 16; ++m) {
        snprintf(&(out[m*2]), 16*2, "%02x", (unsigned int)digest[m]);
    }

    return out;
}

int main() {
  //The secret is generated once and then readed from the file.
  //Unless the file already existed with a different content before the first
  //execution, it will be 4 characters from TUENTI.
  //Compile: g++ secret.cpp -o secret -O2 -lcrypto -lssl
  //Secret: IETN
  string s = "TUENTI";
  sort(s.begin(),s.end()); //Too hard to do it manually!
  set<string> sac;
  //Of all the possible permutations, which one gives is that hash.
  do{
    sac.insert(s.substr(0,4));
  }while(next_permutation(s.begin(),s.end()));
  //192 possibilities
  for (set<string>::iterator it=sac.begin();it!=sac.end();++it) {
    string sec = (*it);
    if(md5(game+sec) == hash) cout << "Secret: " << sec << endl;
  }
}
