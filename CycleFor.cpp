#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // для использования exit()
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

int Factorial(int x) {
    if (x==0) return 1;
    return x*Factorial(x-1);
}


int main() {
    int n=4;
   // int m=Factorial(n-1);
    int m=64;
    int a[m][n];
    for (int i=0; i<m; i++) {
        a[i][0]=3;
    }

   int i=0;
    for (int i1=0; i1<n; i1++) {
        for (int i2=0; i2<n; i2++) {
            for (int i3=0; i3<n; i3++) {
                a[i][1]=i1;
                a[i][2]=i2;
                a[i][3]=i3;
                i++;
            }
        }
    }




    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++)
            cout<<a[i][j]<<" ";
        cout << endl;
    }

    return 0;
}