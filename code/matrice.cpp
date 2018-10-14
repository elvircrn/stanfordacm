#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)

template<class T>
struct matrix {
    vector<vector<T>> mat;
    matrix() = delete;
    matrix(int n, int m=-1) {
        if (m == -1) {
            m = n;
        }
        mat.resize(n, vector<T>(m, T()));
    }
    explicit matrix(vector<vector<T>> x) : mat(move(x)) {};
    inline int n() const {return (int)mat.size();}
    inline int m() const {return (n() > 0)?mat[0].size():0;}
    const vector<T>& operator[] (int x) const {return mat.at(x);}
    vector<T>& operator[] (int x) {return mat.at(x);}
    matrix(const matrix& x) : mat(x.mat) {}
    matrix(matrix&& x) noexcept : mat(move(x.mat)) {}
    matrix operator+ (const matrix& x) const {
        if (n() != x.n() || m() != x.m()) throw "Nista ovo ne valja";
        matrix z(n(), m());
        REP(i, n())
            REP(j, m())
                    z[i][j] = mat[i][j] + x[i][j];
        return z;
    }
    matrix& operator+= (const matrix& x) {
        REP(i, n())
            REP(j, m())
                mat[i][j] += x[i][j];
        return *this;
    }
    matrix operator* (const matrix& x) const {
        if (m() != x.n()) throw "Nista ovo ne valja";
        matrix z(n(), x.m());
        REP(i, n())
            REP(j, x.m())
                REP(k, m())
                    // dodati modul ovdje ako treba
                    z[i][j] += mat[i][k]*x[k][j];
        return z;
    }
    matrix& operator*= (const matrix& x) {
        matrix b = *this * x;
        this->mat = move(b.mat);
        return *this;
    }
};

template<class T>
ostream& operator<<(ostream& os, const matrix<T>& dt) {
    REP(i, dt.n()) {
        REP(j, dt.m()) {
            os << dt[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

template<class T>
matrix<T> eye(int n, int m) {
    matrix<T> z(n, m);
    REP(i, n)
        if (i < m) z[i][i] = 1;
    return z;
}

template<class T>
matrix<T> fast_mul(matrix<T> a, ll step) {
    // paziti ovo 63
    matrix<T> tren = a, rez = eye<T>(a.n(), a.m());
    for (int j = 0; j < 63; j++) {
        if ((1ULL<<j) & step) {
            rez *= tren;
        }
        tren *= tren;
    }
    return rez;
}

int main() {
    matrix<ll> f({{1, 1}, {1, 0}});
    cout << fast_mul(f, 11);
    return 0;
}