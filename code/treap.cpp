#include <bits/stdc++.h>
using namespace std;

typedef int T; //tip kljuca, promijeniti po potrebi

struct node{
    T key;
    int pr, cnt;
    node *l, *r;
    node(T _key, int _pr){ key = _key, pr = _pr, l = NULL, r = NULL, cnt = 1; }
};

typedef node* pnode;

//count(v) vraca broj kljuceva manjih ili jednakih v, O(log n)
//kthelem(k) vraca k-ti najmanji kljuc, O(log n)
//find(v) vraca da li je v u treapu, O(log n)
//split(t,key,l,r) splita treap t u treapove l,r gdje l.key <= key, key < r.key, O(log n)
//merge(t,l,r) spaja treapove l,r gdje l.key <= r.key u treap t, O(log n)
//insert(t,it) ubacuje item it u treap, O(log n)
//erase(t,v) brise item sa kljucem v iz treapa, O(log n)

struct treap{
    pnode root;
    treap(){ root = NULL; srand(time(NULL)); }
    int size(){ return cnt(root); }
    int cnt(pnode t){ return t ? t->cnt : 0; }
    void updcnt(pnode t){ if(t) t->cnt = 1 + cnt(t->l) + cnt(t->r); }

    int count(T v){ return count(root, v); }
    int count(pnode t, T v){
        if(!t) return 0;
        return t->key < v ? 1 + cnt(t->l) + count(t->r, v) : count(t->l, v);
    }

    T kthelem(int k){ return kthelem(root, 0, k); }
    T kthelem(pnode t, int c, int k){
        if(k == c + cnt(t->l) + 1) return t->key;
        else if(k < c + cnt(t->l) + 1) return kthelem(t->l, c, k);
        else return kthelem(t->r, c+cnt(t->l)+1, k);
    }

    bool find(T v){ return find(root, v); }
    bool find(pnode t, T v){
        if(!t) return false;
        else if(t->key == v) return true;
        else if(v < t->key) return find(t->l, v);
        else return find(t->r, v);
    }

    void split(pnode t, T key, pnode& l, pnode& r){
        if(!t) l = r = NULL;
        else if(key < t->key) split(t->l, key, l, t->l), r = t;
        else split(t->r, key, t->r, r), l = t;
        updcnt(t);
    }

    void merge(pnode& t, pnode l, pnode r){
        if(!l || !r) t = l ? l : r;
        else if(l->pr > r->pr) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r;
        updcnt(t);
    }

    void insert(T v){
        pnode it = new node(v, rand());
        insert(root, it);
    }
    void insert(pnode& t, pnode it){
        if(!t){
            t = it;
            return;
        }
        pnode l, r, tp;
        split(t, it->key, l, r);
        merge(tp, l, it);
        merge(t, tp, r);
    }

    void erase(T v){ erase(root, v); }
    void erase(pnode& t, T v){
        if(!t) return;
        pnode l, r, lp, rp;
        split(t, v, l, r);
        split(l, v-1, lp, rp);
        merge(t, lp, r);
    }
};
