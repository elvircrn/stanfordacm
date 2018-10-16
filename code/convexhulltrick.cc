typedef int ftype;
typedef complex<ftype> point;
#define x real
#define y imag 
ftype dot(point a, point b) {
    return (conj(a) * b).x();
}

ftype cross(point a, point b) {
    return (conj(a) * b).y();
}
vector<point> hull, vecs; 
/**
 * Given l1, l2, l3, where we are considering to add l3, l2 is irrelevant iff
 * interesection(l1, l3) is to the left of interesection(l1, l2).
 *
 * This technique can be use to solve dp problems of the form
 * dpi = min(bj * ai + dpj), where j \in [1,i-1], bi > bj ,\foreach i<j.
 */
void add_line(ftype k, ftype b) {
    point nw = {k, b};
    while(!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0) {
        hull.pop_back();
        vecs.pop_back();
    }
    if(!hull.empty()) {
        vecs.push_back(1i * (nw - hull.back()));
    }
    hull.push_back(nw);
}
int get(ftype x) {
    point query = {x, 1};
    auto it = lower_bound(vecs.begin(), vecs.end(), query, [](point a, point b) {
        return cross(a, b) > 0;
    });
    return dot(query, hull[it - vecs.begin()]);
}

