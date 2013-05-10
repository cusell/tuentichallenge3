//Complexity: O(n log(n)) for string identification 
// and O(n) for topological sorting calculation (V=# of nodes)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

typedef vector<string> Vs;
typedef vector<int> Vi;
typedef vector<Vi> Mi;

bool IsTime(char c) {
  return (c=='.' or c=='<' or c=='>');
}

bool IsTime(string s) {
  if (s.size()>1) return false;
  return IsTime(s[0]);
}

Vi TopologicalSorting(Mi& G) {
  int n = int(G.size());
  Vi input_edges(n,0); //How many input edges does each node have.
  Vi topo(n,0); //The resulting topological sorting of the graph.
  Vi placed(n,0); //If each node has been already palced in the topo result.
  int pos = 0; //Current position in the topo result.
  
  //Count the number of input edges for each node.
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    if (G[i][j]) input_edges[j]++;
  }
  
  //Add to the queue the nodes with 0 input edges.
  queue<int> q;
  for (int i = 0; i < n; ++i) if (input_edges[i]==0) {
    q.push(i);
  }
  
  //Breath First Search adding nodes with 0 input edges
  //after the last step removal.
  while(!q.empty()) {
    int p = q.front();
    q.pop();
    if (placed[p]) continue;
    topo[pos++] = p;
    placed[p] = 1;
    for (int i = 0; i < n; ++i) if (G[p][i] > 0) {
      G[p][i]--;
      input_edges[i]--;
      if (input_edges[i]==0) q.push(i);
    }
  }
  //The topological sorting does not contain all the nodes.
  if (pos < n) {
    Vi empty(0);
    return empty;
  }
  return topo;
}


int main() {
  int t; cin >> t;
  string s;
  getline(cin,s); //kills endline
  while(t--) {
    //Assign an int identifier to each different string.
    map<string, int> id;
    getline(cin,s);
    //The reverse of the id map: the string corresponding to each id.
    Vs scene;
    int k=0;
    string w = "";
    Vs v;
    for (int i = 0;i < int(s.size()); ++i) {
      if (IsTime(s[i])) {
        if (w.size()) v.push_back(w);
        w="";
        v.push_back(string(1,s[i]));
      }
      else w+=s[i];
    }
    if (w.size()) v.push_back(w);
    for (int i = 0; i < v.size(); ++i) {
      if (not (IsTime(v[i]))){
        if (not id.count(v[i])) {
          id[v[i]]=k++;
          scene.push_back(v[i]);
        }
      }
    }
    //Total different scenes: k
    int lastdot=-1; //id of the last .scene 
    
    //1 - Create graph
    Mi G(k, Vi(k,0));
    for (int i = 0; i < v.size(); ++i) {
      if (not (IsTime(v[i]))){
        char kind = v[i-1][0];
        int j = id[v[i]];
        if (kind=='.') {
          if (lastdot!=-1) G[lastdot][j]=1;
          lastdot=j;
        }
        else if (kind=='<') {
          if (lastdot!=-1) G[j][lastdot]=1;
        }
        else if (kind=='>') {
           if (lastdot!=-1) G[lastdot][j]=1;
        }
      }
    }
    Mi origG = G;
    
    //2 - Find topological sorting
    Vi topo = TopologicalSorting(G); //topo = permutation of 0..k-1
    
    //3 - Check if the topological sorting is unique.
    //The topological is unique  <=> it is a hamiltonian path
    if (topo.size()<k) cout << "invalid" << endl; //There is no solution.
    else { //One or more solutions
      bool hamil = 1; //Boolean indicating if there is a hamiltonian path.
      for (int i=1;hamil and i<k;++i) {
        //If there are two consecutive nodes in the topogical sorting
        //without a direct edge on the graph, there is not a hamiltonian path.
        if (origG[topo[i-1]][topo[i]] == 0) {
          hamil = 0;
        }
      }
      if (not hamil) cout << "valid" << endl; //There are multiple solutions
      else { //There's just one solution
        for (int i = 0;i < int(scene.size()); ++i) {
          if (i>0) cout << ",";
          cout << scene[topo[i]];
        }
        cout << endl;
      }
    }
  }
}
