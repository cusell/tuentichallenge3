#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll MAX = 1LL<<31;
char v[MAX];

int main() {
  memset(v,0,sizeof(v));
  int x,y,z;
  ifstream fin;
  cerr << "Opening..." << endl;
  fin.open("integers", ios::binary);
  fin.seekg(0,fin.end);
  ll mida = fin.tellg();
  fin.seekg(0,fin.beg);
  cerr << "Reading " << mida << "..." << endl;
  ll tot=0;
  
  int K =(1LL<<25)-1;
  //Prints every few million operations. Used so & operation can be used and the
  //progress tracking doesn't slow the program too much.
  
  while (not fin.eof()) {
    if ((tot&K)==0) {
      cerr << "Reading " << tot << "/" << mida << " = " << ld(tot)/mida << endl;
    }
    fin.read((char*)&x, sizeof(int));
    v[x]=1;
    tot+=4;
  }
  fin.close();
  cout << "{";
  for (ll i=0;i<MAX;++i) if (not v[i]) cout << i << ",";
  cout << "}" << endl;
}
