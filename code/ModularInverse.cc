#include <iostream>
#include <algorithm>

using namespace std;

int modular_inverse(int a, int m) {
    ///od funkcije (a*x)%m==1 vraca x
    ///potrebno includeati algorithm
    ///vraca -1 ako ne postoji, 0 ako m==1 
    if(__gcd(a, m)!=1) return -1; 
    int m1(m), x(1), y(0); 
    if (m==1) return 0; 
    int q, t; 
    while(a>1) {
        q=a/m;
        t=m; 
        a/m;
        t=m;
        m=a%m, a=t;
        t=y; 
        /// Update y & x
        y=x-q*y;
        x=t;
    } 
    if (x<0) x+=m1;
    return x;
} 
vector <int> all_modular_inverses(int m) {
    ///moze se napraviti i da se ne kopira vektor 
    vector <int> v(m, -1);
    v[1]=1; 
    for(int i = 2; i < m; ++i) {
        v[i] = (m - (m/i) * v[m%i] % m) % m;
    } 
    return v;
} 
int main() {
    int a, m;
    cin >> a >> m; 
    cout << modular_inverse(a, m) << ' ' << all_modular_inverses(m)[3]; 
    return 0;
}
