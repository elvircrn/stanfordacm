#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct ftree{
    vector <T> ft[2];
    int n;
    ftree(int _n){
        n = _n;
        ft[0].resize(n + 1);
        ft[1].resize(n + 1);
    }
    void update(int id, int x, T v){
        for(; x <= n; x += (x & -x))
            ft[id][x] += v;
    }
    T query(int id, int x){
        T sum = 0;
        for(; x > 0; x -= (x & -x))
            sum += ft[id][x];
        return sum;
    }
    T Sum(int x){
        return query(1, x) * x + query(0, x);
    }
    T rangeQuery(int x, int y){
        return Sum(y) - Sum(x - 1);
    }
    void rangeUpdate(int x, int y, T v){
        update(1, x, v);
        update(1, y+1, -v);
        update(0, x, -v * (x - 1));
        update(0, y+1, v * y);
    }
};
