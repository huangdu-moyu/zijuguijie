#include "clause.h"
#include "mainwindow.h"

Solver::Solver()
{
    clear();
}



Clause Solver::split(const string& s)
{
//	cout<<s<<endl;
    string tmp="";
    size_t m=s.length();
    Clause k;
    bool is_neg=false;
    for(size_t i=0;i<m;i++)
    {
        if(s[i]==' ')
        {
            continue;
        }
        if(i==m-1||s[i]=='(')
        {
            Word u;
            u.predicate=tmp;
            u.is_neg=is_neg;
            tmp="";
            is_neg=0;
            string tt="";
            for(size_t j=i+1;j<m;j++)
            {
                if(j==m-1||s[j]==')'||s[j]==',')
                {
                    u.paras.push_back(tt);
                    /*
                    k.ff[k.len][k.l[k.len]]=tt;
                    k.l[k.len]++;*/
                    tt="";
                    if(s[j]==')'||j==m-1)
                    {
                        i=j;
                        break;
                    }
                }
                else
                {
                    tt=tt+s[j];
                }
            }
            k.words.push_back(u);
        }
        else if(s[i]=='~')
        {
            is_neg=true;
        }
        else if(s[i]=='|')
        {
            continue;
        }
        else
        {
            tmp+=s[i];
        }
    }
    return k;
}

//检查两个子句是否可归结
int Solver::check(const Clause& a,const Clause& b)
{
//	prt(a);prt(b);

    for(const Word& u:a.words)
    {
        for(const Word& v:b.words)
        {
            if(u.predicate==v.predicate &&
                    u.paras.size()==v.paras.size() &&
                    u.is_neg!=v.is_neg )
            {
                int flag=1;
                for(size_t k=0;k<u.paras.size();k++)
                {
                    if(u.paras[k]!=v.paras[k])
                    {
                        if(u.paras[k][0]=='x'||v.paras[k][0]=='x') //小写字母x开头表示变量
                        {
                            flag=2;
                        }
                        else
                        {
                            flag=0;
                            break;
                        }
                    }
                }
                //cout<<fl<<"smlds\n";
                if(flag==0)
                {
                    continue;
                }
                else
                {
                    return flag;
                }
            }
        }
    }
    return 0;
}

Clause Solver::merge(const Clause& a,const Clause& b,int fl)
{
//	prt(a);prt(b);
    //使用了变量的情况
    if(fl==2)
    {
        Clause c;
        for(const Word& u:a.words)
        //for(int i=0;i<a.len;i++)
        {
            for(const Word& v:b.words)
            //for(int j=0;j<b.len;j++)
            {
                if(u.predicate==v.predicate &&
                        u.paras.size()==v.paras.size() &&
                        u.is_neg!=v.is_neg)
                {
                    for(size_t k=0;k<u.paras.size();k++)
                    //for(int k=0;k<a.l[i];k++)
                    {
                        if(u.paras[k]!=v.paras[k])
                        {
                            if(u.paras[k][0]=='x')
                            {
                                string paraU=u.paras[k],paraV=v.paras[k];
                                ss1=paraU;
                                ss2=paraV;
                                c.words=a.words;
                                for(Word& w:c.words)
                                {
                                    for(string& para:w.paras)
                                    {
                                        if(para==paraU)
                                        {
                                            para=paraV;
                                        }
                                    }
                                }
                                return merge(c,b,1);
                            }
                            if(v.paras[k][0]=='x')
                            {
                                string paraU=u.paras[k],paraV=v.paras[k];
                                ss1=paraV;
                                ss2=paraU;
                                c.words=b.words;
                                for(Word& w:c.words)
                                {
                                    for(string& para:w.paras)
                                    {
                                        if(para==paraV)
                                        {
                                            para=paraU;
                                        }
                                    }
                                }
                                return merge(a,c,1);
                            }
                        }
                    }
                }
            }
        }
        return c;
    }
    else
    {
        Clause c;
        for(const Word& u:a.words)
        {
            for (const Word &v : b.words)
            {
                if (u.predicate == v.predicate &&
                    u.paras.size() == v.paras.size() &&
                    u.is_neg != v.is_neg)
                {
                    bool is_equal = true;
                    for (size_t k = 0; k < u.paras.size(); k++)
                    {
                        if (u.paras[k] != v.paras[k])
                        {
                            is_equal = false;
                            break;
                        }
                    }
                    if (is_equal)   //消去该项
                    {
                        for(size_t i=0;i<a.words.size();i++)
                        {
                            if(&a.words[i]!=&u)
                            {
                                c.words.push_back(a.words[i]);
                            }
                        }
                        for(size_t i=0;i<b.words.size();i++)
                        {
                            if(&b.words[i]!=&v)
                            {
                                c.words.push_back(b.words[i]);
                            }
                        }
                        return c;
                    }
                }
            }
        }
        return c;
    }
}

string Solver::change(const Clause& x)
{
    string res="";
    for(size_t i=0;i<x.words.size();i++)
    {
        if(x.words[i].is_neg)
        {
            res+="¬";
        }
        res+=x.words[i].predicate;
        res+="(";
        for(size_t j=0;j<x.words[i].paras.size();j++)
        {
            res+=x.words[i].paras[j];
            res+=(j==x.words[i].paras.size()-1?")":",");
        }
        if(i!=x.words.size()-1)
        {
            res+="∨";
        }
    }
    return res;
}
bool Solver::checkans(const Clause& x)
{
    if(x.words.size()!=1)
    {
        return 0;
    }
    return x.words[0].predicate=="ANSWER"&&x.words[0].is_neg==false;
}

void Solver::dfs(size_t x)
{
    resClauses.push_back(x);
    if(clausePool[x].isBase)
    {
        return;
    }
    dfs(clausePool[x].parentNo[0]);
    dfs(clausePool[x].parentNo[1]);
}

vector<string> Solver::getresult()
{
    map<size_t,size_t> orderInResult;

    sort(resClauses.begin(), resClauses.end());
    resClauses.resize(
                static_cast<size_t>(
                    unique(resClauses.begin(),resClauses.end())-resClauses.begin()
                    )
                );
    vector<string> res;
    string str;

    for(size_t i=0;i<resClauses.size();i++)
    {
        orderInResult[resClauses[i]]=i+1;
    }

    for(size_t i=0;i<resClauses.size();i++)
    {
        size_t u=resClauses[i];
        str = "  " + to_string(i+1) + ":  " + change(clausePool[u]);
        if (!clausePool[u].isBase)
        {
            str += " (";
            str += to_string(orderInResult[clausePool[u].parentNo[0]]);
            str += ")+(";
            str += to_string(orderInResult[clausePool[u].parentNo[1]]);
            str += ")";
            if (clausePool[u].usedVar)
            {
                str += "    "+clausePool[u].replaceName + "/" + clausePool[u].varName;
            }
        }
        res.push_back(str);
    }
    return res;
}

vector<string> Solver::solve(const vector<string> &clauses)
{
    init(clauses);
    //使用宽度优先搜索，从单子句出发归结
    while(!q.empty())
    {
        //string s=q.front().first;
        //size_t num=q.front().second;
        size_t num=q.front();
        const Clause& t=clausePool[q.front()];
        q.pop();
        if(t.words.size()!=1)
        {
            continue;
        }
        //bool flag=0;
        for(size_t i=0;i<clausePool.size();i++)
        {
            if(i==num||merged[i][num])
            {
                continue;
            }
            const Clause& tp=clausePool[i];
            int status=0;
            /* status==0:无法合并
             * status==1:可以合并，没有出现变量
             * status==2:使用了变量*/
            if((status=check(t,tp)))
            {
                Clause k=merge(t,tp,status);
                k.parentNo[0]=i;
                k.parentNo[1]=static_cast<size_t>(num);

                if(status==2)
                {
                    k.usedVar=true;
                    k.varName=ss1;
                    k.replaceName=ss2;
                }
                //flag=1;
                clausePool.push_back(k);

                if(checkans(k))
                {
                    dfs(clausePool.size()-1);
                    return getresult();
                }
                q.push(clausePool.size()-1);
                merged[i][num]=merged[num][i]=1;
                break;
            }
        }
        q.push(num);
    }
    return vector<string>();
}

void Solver::clear()
{
    clausePool.clear();
    resClauses.clear();
    memset(merged, 0, sizeof(merged));
    ss1 = "";
    ss2 = "";


    queue<size_t> empty;
    swap(empty, q);
}

void Solver::init(const vector<string> &clauses)
{
    for(size_t i=0;i<clauses.size();i++)
    {
        clausePool.push_back(split(clauses[i]));
        clausePool.rbegin()->isBase=true;
        q.push(i);
    }
}
