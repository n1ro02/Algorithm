//
// Created by aree on 2025/5/4.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 自定义快速读入
template<typename T>
void read(T &x) {
    x = 0; char c = getchar();
    bool neg = false;
    while (c != '-' && !isdigit(c)) c = getchar();
    if (c == '-') { neg = true; c = getchar(); }
    while (isdigit(c)) { x = x * 10 + (c - '0'); c = getchar(); }
    if (neg) x = -x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // —— 代码从这里开始 ——


    return 0;
}
