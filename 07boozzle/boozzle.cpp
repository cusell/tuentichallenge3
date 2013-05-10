//Assumes boozzle-dict.txt is in the same directory.
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

typedef vector<int> Vi;
typedef vector<char> Vc;
typedef vector<Vi> Mi;
typedef vector<Vc> Mc;
typedef pair<int,int> P;

//Adjacent directions
const int di[8] = { -1, 0, 1, 0, -1, 1, 1, -1 };
const int dj[8] = { 0, 1, 0, -1, 1, 1, -1, -1 };
const int INF = 1000000000;

Vi sc; //score for each character
Mc T; //Given panel
Mi Tkind, Tval; //Kind and value of each cell multiplier.
int w, n, m;


/*Returns the word score (S(c1)*CM(c1) + ... S(cn)*CM(cn)) * max(WM(c1),...,WM(cn))
* s: searched string
* used[i][j]: if cell i,j has been pressed
* p: position in the string
* (i,j): position of the current cell in the panel.
* sum: (S(c1)*CM(c1) + ... S(cn)*CM(cp)) until the current state.
* mxw: max(WM(c1),...,WM(cp)) until the current state.
*/
int wordscore(string& s, Mi& used, int p, int i, int j, int sum, int mxw) {
  int r = s.size();
  if (p==r) return sum*mxw;
  else {
    int ans=-INF;
    for (int d = 0; d < 8; ++d) {
      int ni = i+di[d];
      int nj = j+dj[d];
      if (ni>=0 and nj>=0 and ni<n and nj<m and T[ni][nj]==s[p] and !used[ni][nj]) {
        int nsum=sum, nw=mxw;
        if (Tkind[ni][nj]==1) { //CM multiplier
          nsum+=sc[s[p]-'A']*Tval[ni][nj];
        }
        else { //WM multiplier
          nsum+=sc[s[p]-'A'];
          nw=max(nw, Tval[ni][nj]);
        }
        used[ni][nj]=1;
        ans=max(ans, wordscore(s, used, p+1, ni, nj, nsum, nw));
        used[ni][nj]=0;
      }
    }
    return ans;
  }
}

//Maximum score in the given panel for string s, or -INF if it can't be found.
int StringScore(string& s) {
  int r = s.size();
  if (1+r>w) return -INF; //Not able to press it
  int ans=0;
  bool can=0;
  Mi used(n,Vi(m,0));
  //Start the recursive function wordscore() in every possible cell (i,j).
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (T[i][j]==s[0]) {
    int nsum=0, nw=1;
    if (Tkind[i][j]==1) { //CM multiplier
      nsum+=sc[s[0]-'A']*Tval[i][j];
    }
    else { //WM multiplier
      nsum+=sc[s[0]-'A'];
      nw=max(nw, Tval[i][j]);
    }
    used[i][j]=1;
    int ret = wordscore(s, used, 1, i, j ,nsum, nw); //p=0 already checked
    used[i][j]=0;
    if (ret>ans) {
      can=true;
      ans=ret;
    }
  }
  if (can) return ans+r;
  return -INF;
}

int main() {
  int t; cin >>t;
  while (t--) {
    //Scores for each character.
    sc = Vi(26,0);
    char z, let, sep;
    int val;
    cin >> z;
    while (cin>>z>>let>>z >> z >> val >> sep) {
      sc[let-'A'] = val;
      if (sep=='}') break;
    }
    cin >> w >> n >> m;
    T = Mc (n,Vc(m,'#'));
    Tkind = Mi (n,Vi(m,0));
    Tval =  Mi (n,Vi(m,0));
    
    for (int i = 0;i < n; ++i) for (int j = 0; j < m; ++j) {
      cin >> T[i][j];
      //kind: 1 => CM multiplier, 2 => WM multiplier
      cin >> z; Tkind[i][j]=z-'0';
      cin >> z; Tval[i][j]=z-'0';
    }
    ifstream fin;
    fin.open("boozzle-dict.txt"); //Assumes boozzle-dict.txt exists.
    string s;
    Vi pts, pes;
    while(fin>>s) {
      int ret = StringScore(s);
      if (ret>0) {
        pts.push_back(ret);
        pes.push_back(int(s.size())+1);
      }
    }
    
    //Knapsack with weights "pes" and values "pts"
    int k = pts.size();
    //Doing the dynamic programming with only last two rows of the matrix.
    Vi dplast(w+1,0),dp(w+1,0);
    for (int i = 0; i < k; ++i) {
      dp = Vi(w+1,0);
      for (int j = 0;j < w+1; ++j) {
        if (j>=pes[i]) dp[j] = max(dplast[j], dplast[j-pes[i]] + pts[i]);
        else dp[j] = dplast[j];
      }
      dplast=dp;
    }
    //Gets the maximum value for some of the possible costs.
    int mx=0;
    for (int i = 0; i < w+1; ++i) mx=max(mx,dp[i]);
    cout << mx << endl;
  }
}
