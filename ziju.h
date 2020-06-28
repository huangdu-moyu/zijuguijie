#ifndef ZIJU_H
#define ZIJU_H
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<iomanip>
using namespace std;
typedef long long ll;

struct Word
{
    bool is_neg;
    string predicate;
    vector<string> paras;
};

struct Clause
{
    /*int len;
    string f[15];
    string ff[15][5];
    bool b[15];
    int l[15];*/
    vector<Word> words;
};




class Solver
{
private:
    int n;
    vector<string> ch;
    bool fgg[505][505];
    string ss1,ss2;

    int resClauses[505];
    size_t resClauseNumber;
    string kk1[505],kk2[505];
    bool bb[505];
    int ff1[505],ff2[505];
    queue<pair<string,int> >q;

    Clause split(const string& s);
    int check(const Clause& a,const Clause& b);
    Clause merge(const Clause& a,const Clause& b,int fl);
    string change(const Clause& x);
    bool checkans(const Clause& x);
    void dfs(int x);
    vector<string> getresult();
public:
    Solver();
    vector<string> solve();
    void clear();
    void init(const vector<string>& clauses);
};




/*
int n;
string ch[505];
bool fgg[505][505];
string ss1,ss2;

int qq[505];
int tt;
map<int,int>ha;
string kk1[505],kk2[505];
bool bb[505];
int ff1[505],ff2[505];
queue<pair<string,int> >q;

node split(string s);
int check(node a,node b);
node merge(node a,node b,int fl);
string change(node x);
bool checkans(node x);
void dfs(int x);
void solve();*/

#endif // ZIJU_H


