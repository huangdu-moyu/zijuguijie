


#ifndef ZIJU_H
#define ZIJU_H
#pragma once
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<map>
#include<iomanip>
using namespace std;
typedef long long ll;

struct node
{
    int len;
    string f[15];
    string ff[15][5];
    bool b[15];
    int l[15];
    node()
    {
        len=0;
        for(int i=0;i<15;i++)
        {
            f[i].clear();
            for(int j=0;j<5;j++)
                ff[i][j].clear();
        }
        memset(b,0,sizeof(b));
        memset(l,0,sizeof(l));
    }
};



extern int n;
extern string ch[505];
extern bool fgg[505][505];
extern string ss1,ss2;

extern int qq[505];
extern int tt;
extern map<int,int>ha;
extern string kk1[505],kk2[505];
extern bool bb[505];
extern int ff1[505],ff2[505];
extern queue<pair<string,int> >q;

node split(string s);
int check(node a,node b);
node merge(node a,node b,int fl);
string change(node x);
bool checkans(node x);
void dfs(int x);
void solve();

#endif // ZIJU_H


