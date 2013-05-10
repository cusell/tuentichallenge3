//IMPORTANT: In the submit phase, I received a partial input that may
//have caused problems. Please run again.
//Only received 13/30 cases, and the 14-th partially.
//Complexity O(n*m*log(n*m)) for grid of size n x m.
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
using namespace std;

typedef vector<char> Vc;
typedef vector<Vc> Mc;
typedef vector<double> Vd;
typedef vector<Vd> Md;
typedef pair<int,int> P;
typedef pair<double,P> dP; //Using pairs to avoid creating < operator.

const double INF = 1e9;
int di[4]={-1,0,1,0};
int dj[4]={0,-1,0,1}; //NWSE

int m,n;
double zs, zt; //Statement does not specify if it's integer.
Mc T; //Given grid.
Md dist; //Distance to each element in the grid.

double Dijkstra(int i0, int j0) {
  if (T[i0][j0]=='O') return 0; //You never start on the end.
  priority_queue<dP> q;
  q.push(dP(0,P(i0,j0)));
  dist[i0][j0]=0;
  
  while(!q.empty()) {
    double c = -q.top().first;
    int i = q.top().second.first;
    int j = q.top().second.second;
    q.pop();
    //End reached -> by Dijkstra it's with the minimum distance.
    if (T[i][j]=='O') return c;
    //If the cost is higher than the best we've got, skip.
    if (c > dist[i][j]) continue;
    //Explore adjacent directions
    for (int d = 0; d < 4; ++d) {
      int ni = i;
      int nj = j;
      int r = 0;
      //Slide until a wall stops us.
      while (ni>=0 and nj>=0 and ni<n and nj<m and T[ni][nj]!='#') {
        ni+=di[d];
        nj+=dj[d];
        ++r;
      }
      //Crashed. One step back.
      ni-=di[d];
      nj-=dj[d];
      --r;
      //If the direction doesn't move us at all, skip.
      if (r==0) continue;
      //Calculating the new time given the distance and constant.
      double ndist = c + zt + double(r)/zs;
      if (ndist < dist[ni][nj]) {
        dist[ni][nj] = ndist;
        q.push(dP(-ndist,P(ni,nj)));
      }
    }
  }
  return -1; //Can't get there.
}

int main() {
  int t; cin >> t;
  while (t--) {
    cin >> m >> n;
    cin >> zs >> zt; //speed, time to start
    T = Mc(n,Vc(m,'@'));
    int i0=-1,j0=-1;
    for (int i=0;i<n;++i) for (int j=0;j<m;++j) {
      cin >> T[i][j];
      if (T[i][j]!='X' and T[i][j]!='#' and T[i][j]!='O' and T[i][j]!='.') {
        //interpuncts need another char (2 bytes)
        cin >> T[i][j];
        T[i][j]='.';
      }
      if (T[i][j]=='X') {
        i0=i;
        j0=j;
      }
    }
    dist = Md(n,Vd(m,INF));
    cout << int(Dijkstra(i0,j0)+0.5) << endl; //Round the output to the nearest integer.
  }
}
