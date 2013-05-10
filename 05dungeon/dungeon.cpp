#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <sstream>
#include <map>
using namespace std;

typedef vector<int> Vi;
typedef vector<Vi> Mi;
typedef pair<int,int> P;
typedef pair<P,P> PP;
typedef pair<PP, set<int> > State; //Use pairs to avoid creating a < operator.

int di[4]={-1,0,1,0};
int dj[4]={0,-1,0,1}; //NWSE
//opposed direction to d is (d+2)%4

Mi T; //Input table
Vi gemv; //Value of i-th gem.
//Arribar a i,j amb direccio d

int n, m; //Size of the table
const int INF = 1000000000;


map<State, int> dist; //Maximum value of the state nodes from the initial state.

//Seconds left, current position (i0,j0), current orientation, visited gems.
//Current orientation: d0=0..3 arrays directions, d0 = 4 not oriented.
//Dijkstra with the State graph. In worst case, 3^20, way faster in average.
int Dijkstra(int seg, int i0, int j0, int d, set<int> vist) {
  if (seg==0) return 0;
  if (T[i0][j0]!=-1) vist.insert(T[i0][j0]);
  State st = State(PP(P(seg,i0),P(j0,d)),vist);
  
  //Will only visit (i0,j0) where there are gems or initial pos.
  priority_queue<pair<int,State> > q;
  q.push(make_pair(0,st));
  if (T[i0][j0]!=-1) dist[st] = gemv[T[i0][j0]]; //I start on a gem.
  else dist[st] = 0; //Empty initial
  
  int ans=0;
  while(!q.empty()) {
    int myval = q.top().first;
    st = q.top().second; q.pop();
    //If I pop a node with a higher distance than the best calculated, ignore it.
    if (myval < dist[st]) continue;
    int zseg = st.first.first.first;
    //Prune: Even if all the cells left were 5, I wouldn't get a higher maximum.
    if (zseg*5+myval <=ans) continue;
    //If there are no movements left.
    if (zseg==0) {
      ans=max(ans,dist[st]);
      continue;
    }
    int zi0 = st.first.first.second;
    int zj0 = st.first.second.first;
    int zd = st.first.second.second;
    set<int> zvist = st.second;
    int zf = dist[st];
    //Visit all adjacent nodes (possible moves).
    //Don't go backwards unless it's the first move.
    for (int zz = 0; zz < 4; ++zz) if (zd==4 or (zd+2)%4!=zz){
      int nseg=zseg-1;
      int ni = zi0+di[zz];
      int nj = zj0+dj[zz];
      //If the new cell is inside the table.
      if (ni>=0 and nj>=0 and ni<n and nj<m) {
        int ret=0;
        bool added=0;
        //If there's a non-visited gem.
        if (T[ni][nj]!=-1 and not zvist.count(T[ni][nj])) {
          added=1;
          zvist.insert(T[ni][nj]);
          ret=gemv[T[ni][nj]];
        }
        //Generate new state.
        State noust = State(PP(P(nseg,ni),P(nj,zz)),zvist);
        if (ret+zf>dist[noust]) {
          dist[noust] = ret+zf;
          q.push(make_pair(ret+zf,noust));
        }
        if (added) zvist.erase(T[ni][nj]);
      }
    }
  }
  return ans;
}

int main() {
  int t; cin >> t;
  while(t--) {
    dist.clear();
    char c;
    cin >> m >> c >> n; //T[n][m]
    T = Mi(n,Vi(m,-1));
    int j0,i0; //T[i0][j0]
    cin >> j0 >> c >> i0;
    int z,g;
    cin >> z >> g;
    string s;
    getline(cin,s); //Read last line endl
    getline(cin,s); //Information to be parsed.
    s+="#";
    stringstream ss;
    ss << s;
    int ii,jj,vv;
    gemv = Vi(0);
    while (ss >> jj >> c >> ii >> c>> vv >> c) {
      T[ii][jj]=int(gemv.size());
      gemv.push_back(vv);
    }
    set<int> buit;
    cout << Dijkstra(z, i0, j0, 4, buit) << endl;
  }
}
