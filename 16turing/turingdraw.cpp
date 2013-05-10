//turingsimple.cpp is a simpler code to read,
//but does not include extra optimizations.
//Optimitzations made it go from 3s to 0.1s
#include <iostream>
#include <fstream>
#include <map>
#include <unistd.h>
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

void draw(string& s, int st, int i) {
  cout << string(20,'\n');
  int a = i-25,b=i+25;
  cout << "State: ";
  if (st<33) cout << "state" << st;
  else if (st==33) cout << "start";
  else if (st==34) cout << "end";
  else cout << "???";
  cout << "\t" << i << "\t";
  Inst inst = m[val(s[i])][st];
  char cwrite = inst.first;
  char move = inst.second.first;
  int newst = inst.second.second;
  cout << cwrite << ", " << move << ", ";
  if (newst<33) cout << "state" << newst;
  else if (newst==33) cout << "start";
  else if (newst==34) cout << "end";
  else cout << "???";
  cout << endl;
  
  for (int j=a;j<=b;++j) {
    if (j!=i) cout << " ";
    else cout << "v";
  }
  cout << endl;
  
  for (int j=a;j<=b;++j) {
    if (j>=0 and j<s.size()) cout << s[j];
    else cout << "*";
  }
  cout << endl;
  cout.flush();
  usleep(1000000/2);
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
  string s;
  while(cin>>s) {
    i = 0;
    st = getstatenum("start");
    int last=0;
    ll it=0;
    while(i>=0 and m[val(s[i])][st].first!='@' and st != endst) {
      ++it;
      if (s.size()%1000==0 and s.size()!=last) {
        last=s.size();
        cerr << s.size() << " " << it << endl;
      }
      draw(s, st, i);
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
    i=int(s.size())-1;
    while(i>=0 and s[i]=='_') --i;
    for (int j = 0; j <= i; ++j) cout << s[j];
    cout << endl;
  }
}
