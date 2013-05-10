#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

//Given an input, returns the output using the other programs.
int main() {
  string s;
  ofstream fout("islandqr.in");
  bool primera=1;
  string w;
  while(getline(cin,s)) {
    if (primera) {
      primera=false;
      w=s;
    }
    fout << s << '\n';
  }
  int sysret;
  sysret = system("./island < islandqr.in >islandqr.draw");
  sysret = system("python draw.py <islandqr.draw");
  stringstream ss;
  ss << w;
  int numcases;
  ss >> numcases;
  sysret = system("cat /dev/null > qrans.out");
  for (int i = 0; i < numcases;++i) {
    stringstream st;
    st << i;
    st >> s;
    string qrcall = "zbarimg -q island-"+s+".png >> qrans.out";
    sysret = system(qrcall.c_str());
  }
  ifstream fin("qrans.out");
  while(getline(fin,s)) {
    s = s.substr(8,s.size()-8); //remove "QR-Code:"
    cout << s << endl;
  }
}
