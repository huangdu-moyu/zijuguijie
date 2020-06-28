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
    bool usedVar=false;
    string varName,replaceName;
};


const int maxClauseNumber=505;

class Solver
{
private:
    vector<Clause> clausePool;
    bool merged[maxClauseNumber][maxClauseNumber];
    string ss1,ss2;

    vector<size_t> resClauses;
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


#endif // ZIJU_H


