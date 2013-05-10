#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef vector<int> Vi;
typedef vector<Vi> Mi;
typedef vector<double> Vd;
typedef vector<Vd> Md;

const double INF = 1e50;

Mi G;
Md Gd;
Vd dist;

//Relax edge (u,v) with cost cost.
bool relax(int u, int v, double cost) {
  if (dist[u] != INF and dist[v] > dist[u] + cost) {
    dist[v] = dist[u] + cost;
    return true;
  } return false;
}

//Returns true if there's a negative cycle
bool bellmanford(int s) {
  int n = G.size();
  dist = Vd(n,INF);
  dist[s] = 0;
  for (int k = 0; k < n-1; ++k) {
    bool change = false;
    for (int i = 0; i < n; ++i) for (int j = 0; j < G[i].size(); ++j) {
      if (relax(i,G[i][j], Gd[i][j])) change = true;
    }
    if (!change) break;
  }
  //If a relax is still available, there's a negative cycle.
  for (int i = 0; i < n; ++i) for (int j = 0; j < G[i].size(); ++j) {
    if (relax(i, G[i][j], Gd[i][j])) return true;
  }
  return false;
}

int main(){
  int t; cin >> t;
  int n, m;
  while (t--) {
    cin >> n >> m;
    ++n; //Add the extra node
    Gd = Md(n);
    G = Mi(n);
    for (int i = 0; i <m; ++i) {
      int a, b;
      double c; //Statement doesn't say it's going to be integer.
      cin >> a >> b >> c;
      G[a].push_back(b);
      if (c!=0) Gd[a].push_back(-log(1.+c/100.));
      else Gd[a].push_back(0);
      //1+c/100 converts [-20%, +20%] to [0.8, 1.2]
      //log to maximize the product
    }
    //Edge from extra node to all for reachability.
    for (int i = 0; i < n-1; ++i) {
      G[n-1].push_back(i);
      Gd[n-1].push_back(0);
    }
    if (bellmanford(n-1)) cout << "True" << endl;
    else cout << "False" << endl;
  }
}
