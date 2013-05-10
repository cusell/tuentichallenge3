#include <iostream>
#include <vector>
using namespace std;

//from hexdump
//78 a3 65 55 ed f5 90 da 54 da 5c 68 c8 e1 75 d6 42 b7 7e 86 0a 17 92 65 0c ae 47 78 [f7 00 2e 73]

string cif = "78a36555edf590da54da5c68c8e175d642b77e860a1792650cae4778f7";

/*
 * From ASM:
    db 0A3h, 65h, 55h
    dd 0DA90F5EDh, 685CDA54h, 0D675E1C8h, 867EB742h, 6592170Ah
    dd 7847AE0Ch
    db 0F7h
*/

int val(char c) {
  if (c>='0' and c<='9') return c-'0';
  return c-'a'+10;
}

unsigned char val(char a, char b) {
  return (val(a)<<4)|val(b);
}

int main() {
  unsigned int v4, v7;
  vector<char> v;
  v7 = 1337;
  //XOR cipher. Get pair of hex values (byte by byte)
  for (int i=0;i<cif.size();i+=2) {
    v4 = 16807 * v7 % 0x7FFFFFF;
    v7 = 16807 * v7 % 0x7FFFFFF;
    v.push_back( (unsigned char)(v4) ^ val(cif[i],cif[i+1]) );
  }
  for (int i=0;i<v.size();++i) cout << v[i];
  cout << endl;
}
