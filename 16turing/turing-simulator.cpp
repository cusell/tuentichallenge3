#include <iostream>
#include <fstream>
#include <map>
using namespace std;
typedef pair<char, int> P;
typedef pair<char, P> Inst;
typedef long long ll;

Inst m[6][35]; //0..32, 33start, 34 end

/*
 * State: start, end, [0,32]
 * Valid content: 01#$%_
 */

int getstatenum(string s) {
  if (s=="start") return 33;
  else if(s=="end") return 34;
  else {
    s.replace(s.begin(),s.begin()+5,""); //remove state
    int x = 0;
    for (int i=0;i<s.size();++i) {
      x*=10;
      x+=s[i]-'0';
    }
    return x;
  }
}

pair<P, Inst> addline(string& s) {
  int n = s.size();
  P state = P('.', 0);
  Inst inst = Inst('.',P('.',0));
  int chunk = 0;
  string inist="", gost="";
  for (int i=0;i<s.size();++i) {
    if (s[i]==',' or s[i]==':') ++chunk;
    else {
      if (chunk==0) inist+=s[i];
      else if(chunk==1) state.first=s[i];
      else if(chunk==2) inst.first=s[i];
      else if(chunk==3) inst.second.first=s[i];
      else if(chunk==4) gost+=s[i];
    }
  }
  state.second = getstatenum(inist);
  inst.second.second = getstatenum(gost);
  return make_pair(state, inst);
}

//Pre: It's a character in 01#$%_
inline char val(char c) {
  if (c=='0') return 0;
  else if(c=='1') return 1;
  else if(c=='#') return 2;
  else if(c=='$') return 3;
  else if (c=='%') return 4;
  else return 5; //'_'
}

int main() {
  for (int i = 0; i < 6; ++i) for (int j = 0; j < 35; ++j) {
    m[i][j] = Inst('@',P('@',0));
  }
  //contains the script of the problem statement.
  ifstream fin("code.txt");
  string code;
  while(getline(fin,code)) {
    pair<P, Inst> line = addline(code);
    m[val(line.first.first)][line.first.second] = line.second;
  }
  
  int i, st, newst, endst;
  endst = getstatenum("end");
  string s, origs;
  while(cin>>s) {
    origs = s;
    i = 0;
    st = getstatenum("start");
    int last=0;
    while(i>=0 and m[val(s[i])][st].first!='@' and st != endst) {
      Inst inst = m[val(s[i])][st];
      char cwrite = inst.first;
      char move = inst.second.first;
      newst = inst.second.second;
      s[i] = cwrite;
      if (move=='L') --i;
      else if(move=='R') {
        if (i+1>=s.size()) s+='_';
        ++i;
      }
      st = newst;
    }
    //Intentionally remove trailing _
    //Guaranteed "end".
    //if (st==endst) {
    i=int(s.size())-1;
    while(i>=0 and s[i]=='_') --i;
    for (int j = 0; j <= i; ++j) cout << s[j];
    cout << endl;
  }
}
