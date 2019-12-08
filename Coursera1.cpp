#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, m;   //n- сколько элементов в строке, m - сколько всего элементов
vector<int> a;
vector <bool> used;

void out()
{
    for (int i = 0; i < n; i++)
    {
        if (i)
            cout << " ";
        cout << a[i];
    }
    cout << endl;
}

void rec(int idx)
{
    if (idx == n)
    {
        out();
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        a[idx] = i;
        rec(idx + 1);
    } 
}

int main()
{
    //cin >> n >> m;
    m=4;   //всего 5 элементов
    vector <int> nn;
    //for (int i=0; i<m-1;i++) {
    //    n=;
    //}
    /*n=1;
    a = vector<int>(n);
    rec(0);
    n=2;
    a = vector<int>(n);
    rec(0);
    n=3;
    a = vector<int>(n);
    rec(0);*/
    n=4;
    a = vector<int>(n);
    rec(0);
    return 0;
}