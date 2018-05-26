#include "matrix.h"

#include <bits/stdc++.h>

using namespace std;

int main(){
    size_t n, m;
    cin >> n >> m;
    Matrix C(n, m);
    cin >> C;
    cout << Inverse(C) << endl;
    return 0;
}