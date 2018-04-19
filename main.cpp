#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cmath>
#include "liste.h"

using namespace std;

int main() {
    int n, m;
    Complex Zero(0, 0, 0, 0);
    Lista A;
    cin >> n >> m;
    Matrix B(n, m), C(n, m), D(n, m), E(n, m);
    cin >> B;
    cin >> C;
    D = B + C;
    E = B * C;
    D = D + E;
    D = D - C;
    cout << D;
    ///cout << B.Inv(n, B);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            Complex k;
            cin >> k;
            if(k == Zero) {
                continue;
            }
            A.push_back(k);
        }
    }
    for(Lista::Iterator it = A.front(); it != A.end(); it++)
        cout << *it << ' ';
    cout << '\n';
    return 0;
}
