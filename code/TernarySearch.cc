#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Ne radi ako ima "ravnih" dijelova
int find_max(const vector<int> &v) {

    int low = 0, high = v.size() - 1;

    while (high - low > 1) {

        int mid = (high + low) / 2;

        if (v[mid] < v[mid + 1]) {
            low = mid;
        } else if (v[mid] > v[mid + 1]) {
            high = mid;
        } 
    }

    return max(v[low], v[high]);
}

int main() {

    int n;
    cin >> n;
    vector<int> v(n);

    for (auto &i : v)
        cin >> i;

    cout << find_max(v);
}
