//Complexity: O(n) where n are the number of nodes of the tree,
//or length of the string.
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node{
  char col; //w(white), b(black), p(recursive)
  int a,b,c,d; //index to the subtrees, or -1 if it doesn't have
  int dad; //index from it's parent, or -1 if it's the root
  Node () { //default constructor
    col='?';
    a=b=c=d=-1;
    dad=-1;
  }
};

vector<Node> createTree(string s) {
  vector<Node> v(0);
  Node nd0;
  v.push_back(nd0); //root node
  queue<int> q; //BFS creation
  q.push(0);
  while(!q.empty()) {
    int p = q.front(); q.pop();
    v[p].col = s[p];
    Node nd = nd0; nd.dad = p;
    
    if (s[p]=='p') {
      v[p].a = v.size();
      q.push(v.size());
      v.push_back(nd);
      
      v[p].b = v.size();
      q.push(v.size());
      v.push_back(nd);
      
      v[p].c = v.size();
      q.push(v.size());
      v.push_back(nd);
      
      v[p].d = v.size();
      q.push(v.size());
      v.push_back(nd);
    }
  }
  return v;
}

/*
 * f(0)
 * 
 * read a1,a2,a3,a4
 */

vector<Node> sumaTree(vector<Node> va, vector<Node> vb) {
  vector<Node> v(0);
  Node nd0;
  v.push_back(nd0); //root node
  
  vector<int> wa(0),wb(0);
  wa.push_back(0); wb.push_back(0);
  //wa[i] which "va" node is v[i] associated to
  //wb[i] which "vb" node is v[i] associated to
  
  queue<int> q;
  q.push(0);
  while(!q.empty()) {
    int p = q.front(); q.pop();
    Node nd = nd0; nd.dad = p;
    char ca = '?',cb='?';
    if (wa[p]!=-1) ca = va[wa[p]].col;
    if (wb[p]!=-1) cb = vb[wb[p]].col;
    //Both can't be -1 at the same time.
    
    if (ca=='b' or cb=='b') v[p].col='b';
    else if (ca=='w' and cb=='w') v[p].col='w';
    else if (ca=='?' and cb!='?') v[p].col=cb;
    else if (ca!='?' and cb=='?') v[p].col=ca;
    else if (ca=='?' and cb=='?') cerr << "woops.." << endl;
    else v[p].col='p';
    
    if (v[p].col=='p') { //Four child. For more, could be generalized.
      v[p].a = v.size();
      q.push(v.size());
      v.push_back(nd);
      if (wa[p]!=-1) wa.push_back(va[wa[p]].a);
      else wa.push_back(-1);
      if (wb[p]!=-1) wb.push_back(vb[wb[p]].a);
      else wb.push_back(-1);
      
      v[p].b = v.size();
      q.push(v.size());
      v.push_back(nd);
      if (wa[p]!=-1) wa.push_back(va[wa[p]].b);
      else wa.push_back(-1);
      if (wb[p]!=-1) wb.push_back(vb[wb[p]].b);
      else wb.push_back(-1);
      
      v[p].c = v.size();
      q.push(v.size());
      v.push_back(nd);
      if (wa[p]!=-1) wa.push_back(va[wa[p]].c);
      else wa.push_back(-1);
      if (wb[p]!=-1) wb.push_back(vb[wb[p]].c);
      else wb.push_back(-1);
      
      v[p].d = v.size();
      q.push(v.size());
      v.push_back(nd);
      if (wa[p]!=-1) wa.push_back(va[wa[p]].d);
      else wa.push_back(-1);
      if (wb[p]!=-1) wb.push_back(vb[wb[p]].d);
      else wb.push_back(-1);
    }
  }
  return v;
}

void simplifica(vector<Node>& v) {
  int n = v.size();
  for (int i=n-1;i>=0;--i) {
    if (v[i].col=='p') {
      char col;
      for (int op=0;op<2;++op) {
        if (op==0) col='b';
        else col='w';
        if (col == v[v[i].a].col and col == v[v[i].b].col and col == v[v[i].c].col and col == v[v[i].d].col) {
          v[i].col=col;
          v[v[i].a].col='.'; //deleted
          v[v[i].b].col='.'; //deleted
          v[v[i].c].col='.'; //deleted
          v[v[i].d].col='.'; //deleted
          
          v[i].a=v[i].b=v[i].c=v[i].d=-1;
        }
      }
    }
  }
}

int prof(vector<Node>& v, int p) {
  if (p<0) {
    cerr << "woop bad p<0" << endl;
    return 0;
  }
  if (v[p].col=='.') { //deleted node
    cerr << "shouldnt be here boy. Deleted node." << endl;
    return 0;
  }
  if (v[p].a==-1) return 1;
  int ans=0;
  ans=max(ans,1+prof(v,v[p].a));
  ans=max(ans,1+prof(v,v[p].b));
  ans=max(ans,1+prof(v,v[p].c));
  ans=max(ans,1+prof(v,v[p].d));
  return ans;
}

void pinta(vector<Node>& v, int p, int i0, int j0, int i1, int j1) {
  if (v[p].col=='b') cout << i0 << " " << j0 << " " << i1 << " " << j1 << endl;
  else if (v[p].col=='p') {
    int pi = (i0+i1)/2;
    int pj = (j0+j1)/2;
    pinta(v, v[p].b, i0, j0, pi, pj);
    pinta(v, v[p].d, pi, pj, i1, j1);
    
    pinta(v, v[p].a, pi, j0, i1, pj);
    pinta(v, v[p].c, i0, pj, pi, j1);
  }
}

int main() {
  int t; cin >> t;
  cout << t << endl; //Print number of cases for python drawer.
  while(t--) {
    string a, b;
    cin >> a >> b;
    
    vector<Node> va = createTree(a);
    vector<Node> vb = createTree(b);
    vector<Node> suma = sumaTree(va,vb);

    //pbbbb -> b
    //Not necessary, but algorithmically interesting and can
    //make the drawing slightly faster.
    simplifica(suma);
    
    //These commented lines print the simplified tree (p,w,b) of the sum.
    //for (int i=0;i<suma.size();++i) if (suma[i].col!='.') cout << suma[i].col;
    //cout << endl;
    pinta(suma, 0, 0, 0, 640, 640);
    cout <<"-1 -1 -1 -1" << endl; //case separator for python drawer
  }
}
