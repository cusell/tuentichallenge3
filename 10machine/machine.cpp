//Build using "make all" with the given Makefile.
//Uses openssl MD5 implementation.
#include <iostream>
#include <cstring>
#include <cstdio>
#include <openssl/md5.h>
#include <stdlib.h>
#include <vector>
using namespace std;

typedef vector<int> Vi;
typedef vector<Vi> Mi;
typedef pair<int,int> P;
typedef long long ll;
string s;
int n;
Mi memole,memori,memox,memoy; //memoization arrays

//Returns: (size of concatenation string before [], number of repetitions)
P split(int a, int b) {
  P ans = P(0,0);
  bool dig=0;
  for (int i = a; i <=b; ++i) {
    if (isdigit(s[i])) dig=1;
    if (dig) {
      ans.second*=10;
      ans.second+=s[i]-'0';
    }
    else ++ans.first; //add s[i]
  }
  return ans;
}


//Buffering optimization start
//It only calls MD5_Update when there are enough characters to write.
char *buffer;
const int BN = 1024*1024;
int bp; //position buffer

void clearbuffer(MD5_CTX& c) {
  MD5_Update(&c, buffer, bp);
  bp=0;
}

void update(MD5_CTX& c, const char *str, ll n) {
  if (bp+n<BN) {
    //memcpy(buffer+bp, str, (size_t)n);
    for (int i=0;i<n;++i) buffer[bp++]=str[i];
  }
  else {
    clearbuffer(c);
    MD5_Update(&c, str, n);
  }
}
//Buffering optimization end

//Pre: Before [, there's always a number.
//Updates MD5_CTX according to the interval [a,b] of the string.
void SubstringMD5(MD5_CTX& c, const char *str, int a, int b) {
  if (b<a) return;
  int le, ri, x, y;
  //Memoization optimization:
  //If it's the first time calculating this interval, calculate it.
  //Gets values le,ri (left and right positions of the brackets[]) 
  // and (x,y) the returning values from split().
  if (memox[a][b]==-1) {
    int i, ct=1; //[ = +1, ] = -1
    for (i=a;s[i]!='[' and i<=b;++i);
    P p = split(a,i-1);
    x = p.first;
    y = p.second;
    le=i;
    if (s[le]!='[') { //No opening bracket
      i=b+1;
      le=ri=-1;
    }
    ri=-1;
    //Looking for the corresponding closing bracket.
    for (i=le+1;i<=b and ct!=0;++i) {
      if (s[i]==']') --ct;
      else if (s[i]=='[') ++ct;
      if (ct==0) ri=i;
    }
    memole[a][b] = le;
    memori[a][b] = ri;
    memox[a][b] = x;
    memoy[a][b] = y;
  }
  else {
    le = memole[a][b];
    ri = memori[a][b];
    x = memox[a][b];
    y = memoy[a][b];
  }
  //Add the string before the brackets.
  update(c, str+a, x);
  
  if (le==-1) return; //No [ -> end now.
  //[le .... ri]
  //Add the content in the brackets y times.
  for (int j = 0; j < y; ++j) {
    SubstringMD5(c, str, le+1, ri-1);
  }
  //Keep solving whats after the current brackets.
  SubstringMD5(c, str, ri+1, b);
}

//Calculates all the MD5 hash.
string GetAllMD5(const char *str) {
  int m;
  MD5_CTX c;
  unsigned char digest[16];
  char *out = (char*)malloc(33);

  MD5_Init(&c);
  SubstringMD5(c, str, 0, n-1);
  clearbuffer(c);
  MD5_Final(digest, &c);

  for (m = 0; m < 16; ++m) {
    snprintf(&(out[m*2]), 16*2, "%02x", (unsigned int)digest[m]);
  }

  return out;
}


int main() {
  while(getline(cin,s)) {
    n = s.size();
    memole = memori = memox = memoy = Mi(n,Vi(n,-1));
    buffer = new char[BN];
    bp=0;
    cout << GetAllMD5(s.c_str()) << endl;
  }
}
