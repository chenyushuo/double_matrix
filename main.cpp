#include "matrix.h"

#include <bits/stdc++.h>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    Matrix A(n, m, nullptr);
    cin >> A;

    cin >> n;
    RowVector B(n, nullptr);
    //ColVector B(n, nullptr);
    cin >> B;
    RowVector C = B * A;
    //ColVector C = A * B;
    //cin >> n >> m;
    //Matrix B(n, m, nullptr);
    //cin >> B;
    //Matrix C = A * B;
    //cout << A << endl;
    //cout << B << endl;
    cout << C << endl;
    return 0;
}