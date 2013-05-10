/*
value  id  key
4223  0  442
416   1  84
815   2  158
158   3  1615
164   4  2316
*/
#include <iostream>
using namespace std;

int T[5] = {4223, 416, 815, 158, 164};

int main() {
    int n;
    while (cin >> n) {
        if (n>=0 and n<5) cout << T[n] << endl;
        else cout << T[4] << endl;
        //T[4] actually got repeated for channel = -1!
        //even though the expected inputs were 0..4
    }
}

