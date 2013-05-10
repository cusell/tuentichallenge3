//It assumes the dictionary is in the same directory as the executable.
//Complexity: O(dictionary_size*log(dictionary_size) + output_size)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef vector<string> Vs;

int main() {
  ifstream fin;
  string filename,s,w;
  getline(cin,s); //#Dictionary file
  getline(cin,filename);
  fin.open(filename.c_str());
  
  map<string, Vs> dic;
  //Add all the words to the vector of the map with the sorted word.
  while(fin>>s) {
    w=s;
    sort(s.begin(),s.end());
    dic[s].push_back(w);
  }
  
  //Order each vector<string> once to not do it while processing the output.
  for(map<string, Vs>::iterator it=dic.begin();it!=dic.end();++it) {
    sort(it->second.begin(), it->second.end());
  }
  
  fin.close();
  getline(cin,s); //#Suggestion numbers
  int n; cin >> n;
  getline(cin,s); // //Read last line endl
  getline(cin,s); //#Find the suggestions
  for (int i = 0; i < n; ++i) {
    cin >> s; //Given input string s
    w = s;
    cout << s << " ->";
    sort(s.begin(),s.end());
    Vs v = dic[s];
    for (int j = 0; j < int(v.size()); ++j) if (v[j]!=w) {
      cout << " " << v[j];
    }
    cout << endl;
  }
}
