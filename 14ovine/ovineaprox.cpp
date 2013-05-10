#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

/*
 * Guess 1: XOR cipher
 * Check char by char which key (from 256) generates most a-zA-Z and spaces.
 * Guess succesful ;-)
 * */

int val(char c) {
  if (c>='0' and c<='9') return c-'0';
  return c-'a'+10;
}

//The output given by this program will be semi-readable, so the real sentences will still have to be found.
int main() {
  string s;
  vector<string> vs;
  int mxsize=0;
  while(cin>>s) {
    vs.push_back(s);
    mxsize = max(mxsize,int(s.size()));
  }
  int k = vs.size();
  
  int MAXCHAR = mxsize;
  vector<int> bestkey(MAXCHAR,0);
  for (int i=0;i<MAXCHAR;i+=2) { //for each byte
    int azkey=0;
    for (int key=0;key<16*16;++key) { //for each possible key
      int az=0;
      for (int j=0;j<k;++j) if (i<vs[j].size()){
        char c = char((val(vs[j][i])*16+val(vs[j][i+1]))^key);
        if ((c>='a' and c<='z') or (c>='A' and c<='Z') or c==' ') ++az;
      }
      if (az>azkey) { //gets the one that leaves more readable characters
        azkey=az;
        bestkey[i]=key;
      }
    }
  }
  for (int j=0;j<k;++j) {
    for (int i=0;i<MAXCHAR;i+=2) {
      char c = (val(vs[j][i])*16+val(vs[j][i+1]))^bestkey[i];
      cout << c;
    }
    cout << endl;
  }
}
