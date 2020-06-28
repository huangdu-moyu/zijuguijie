#include "ziju.h"
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
            res+="~";
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
            res+="|";
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

void Solver::dfs(int x)
{
    resClauses[resClauseNumber++]=x;
    if(x<10)
    {
        return;
    }
    dfs(ff1[x]);
    dfs(ff2[x]);
}

vector<string> Solver::getresult()
{
    sort(resClauses, resClauses + resClauseNumber);
    resClauseNumber=static_cast<size_t>(
                unique(resClauses,resClauses+resClauseNumber)-resClauses);
    vector<string> res;
    string str;
    for(size_t i=0;i<resClauseNumber;i++)
    {
        size_t u=static_cast<size_t>(resClauses[i]);
        str = "  " + to_string(i+1) + ":  " + ch[u];
        if (i > 9)
        {
            str += " (";
            str += to_string(ff1[i]+1);
            str += ")+(";
            str += to_string(ff2[i]+1);
            str += ")";
            //cout<<" "<<"("<<ha[ff1[i]]<<")+("<<ha[ff2[i]]<<")";
            if (bb[i])
            {
                str += "    "+kk2[i] + "/" + kk1[i];
                //cout<<"    "<<kk2[i]<<"/"<<kk1[i];
            }
        }
        res.push_back(str);
    }
    return res;
}

vector<string> Solver::solve()
{
    while(!q.empty())
    {
        string s=q.front().first;
        int num=q.front().second;
        Clause t=split(s);
        q.pop();
        if(t.words.size()!=1)
        {
            continue;
        }
        //bool flag=0;
        for(int i=0;i<n;i++)
        {
            Clause tp=split(ch[i]);
            int tpp=0;
        //	cout<<s<<" "<<ch[i]<<endl;
            if(i!=num&&!fgg[i][num]&&(tpp=check(t,tp)))
            {
                Clause k=merge(t,tp,tpp);
                ch.push_back(change(k));
        //		print(ch[n],n,t,i,tp,num,tpp);
                ff1[n]=i;
                ff2[n]=num;
                if(tpp==2)
                {
                    bb[n]=1;
                    kk1[n]=ss1;
                    kk2[n]=ss2;
                }
                //flag=1;
                if(checkans(k))
                {
                    dfs(n);

                    return getresult();
                }
                q.push(make_pair(*ch.rbegin(),n));
                fgg[i][num]=fgg[num][i]=1;
            //	fgg[i]=1;
                n++;
                break;
            }
        }
        q.push(make_pair(s,num));
    }
    return vector<string>();
}

void Solver::clear()
{
    n = 0;
    ch.clear();
    memset(fgg, 0, sizeof(fgg));
    ss1 = "";
    ss2 = "";

    //memset(resClauses, 0, sizeof(resClauses));
    resClauseNumber = 0;
    memset(kk1, 0, sizeof(kk1));
    memset(kk2, 0, sizeof(kk2));
    memset(bb, 0, sizeof(bb));
    memset(ff1, 0, sizeof(ff1));
    memset(ff2, 0, sizeof(ff2));

    queue<pair<string, int>> empty;
    swap(empty, q);
}

void Solver::init(const vector<string> &clauses)
{
    n=static_cast<int>(clauses.size());
    ch=clauses;
    for(int i=0;i<n;i++)
    {
        q.push(make_pair(ch[i], i));
    }
}
