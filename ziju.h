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
    vector<Word> words;
    bool isBase=false;
    size_t parentNo[2];
};


const int maxClauseNumber=505;

class Solver
{
private:
    int n;
    vector<Clause> clausePool;
    bool merged[maxClauseNumber][maxClauseNumber];
    string ss1,ss2;

    vector<size_t> resClauses;
    //int resClauses[505];
    //size_t resClauseNumber;
    string kk1[505],kk2[505];
    bool bb[505];
    queue<size_t> q; //存放子句编号

    Clause split(const string& s);
    int check(const Clause& a,const Clause& b);
    Clause merge(const Clause& a,const Clause& b,int fl);
    string change(const Clause& x);
    bool checkans(const Clause& x);
    void dfs(size_t x);
    vector<string> getresult();
    void init(const vector<string>& clauses);
public:
    Solver();
    vector<string> solve(const vector<string>& clauses);
    void clear();

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


