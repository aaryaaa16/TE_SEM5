#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> ap;
    vector<int> bp;
    queue<int> res;
    int n = 9;
    int r = 11;
    ap.push_back(r);
    bp.push_back(r);
    int v[] = {23, 44, 13, 9, 4, 7, 6, 18};
    string p[] = {"L", "R", "LL", "LR", "RL", "RR", "RLL", "RLR"};
    int a = 13;
    int b = 18;
    int aindx;
    int bindx;
    for (int i = 0; i < 8; i++) {
        if (v[i] == a) {
            aindx = i;
            break;
        }
    }
    for (int i = 0; i < 8; i++) {
        if (v[i] == b) {
            bindx = i;
            break;
        }
    }
    string s = "";
    s += p[aindx].at(0);
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (v[i] == a) {
            break;
        }
        if (p[i] == s) {
            ap.push_back(v[i]);
            s += p[aindx].at(count++);
        }
    }
    for (int i = size(ap) - 1; i >= 0; i--) {
        res.push(ap[i]);
    }
    s = "";
    s += p[bindx].at(0);
    count = 0;
    for (int i = 0; i < 8; i++) {
        if (v[i] == b) {
            break;
        }
        if (p[i] == s) {
            bp.push_back(v[i]);
            s += p[bindx].at(count++);
        }
    }
    int temp = res.back();
    int start;
    for (int i = 0; i < size(bp); i++) {
        if (bp[i] == temp) {
            start = i;
            break;
        }
    }
    for (int i = start + 1; i < size(bp); i++) {
        res.push(bp[i]);
    }
    while (!res.empty()) {
        cout<<res.front()<<" ";
        res.pop();
    }
}