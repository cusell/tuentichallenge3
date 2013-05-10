#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main() {
  string s;
  ofstream fout("partycas.in");
  while(getline(cin,s)) {
    fout << s << '\n';
  }
  int sysret;
  sysret = system("base64 -d <partycas.in >partycas.mp3");
  sysret = system("lame --decode --quiet partycas.mp3 partycas.wav");
  //Decodes baudot code.
  sysret = system("minimodem --rx -q -f partycas.wav rtty > partycas.out");
  ifstream fin("partycas.out");
  while(getline(fin,s)) cout << s << endl;
  //cout << "DEAD BADD FACE F00D BEEF BEEF F00D C0DE" << endl;
}
