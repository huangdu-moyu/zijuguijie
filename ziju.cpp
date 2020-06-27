#include "ziju.h"
#include "mainwindow.h"

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

node split(string s)
{
//	cout<<s<<endl;
    string tp="";
    int m=s.length();
    node k;
    bool fg=0;
    for(int i=0;i<m;i++)
    {
        if(i==m-1||s[i]=='(')
        {
            k.len++;
            k.f[k.len]=tp;
            k.b[k.len]=fg;
            tp="";
            fg=0;
            string tt="";
            for(int j=i+1;j<m;j++)
            {
                if(j==m-1||s[j]==')'||s[j]==',')
                {
                    k.l[k.len]++;
                    k.ff[k.len][k.l[k.len]]=tt;
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
        }
        else if(s[i]=='~')
        {
            fg=1;
        }
        else if(s[i]=='|')
        {
            continue;
        }
        else
        {
            tp=tp+s[i];
        }
    }
//	prt(k);
    return k;
}

int check(node a,node b)
{
//	prt(a);prt(b);
    for(int i=1;i<=a.len;i++)
    {
        for(int j=1;j<=b.len;j++)
        {
            if(a.f[i]==b.f[j])
            {
                if(a.b[i]==b.b[j])
                {
                    continue;
                }
                int fl=1;
                for(int k=1;k<=a.l[i];k++)
                {
                    if(a.ff[i][k]!=b.ff[j][k])
                    {
                        if(a.ff[i][k][0]=='x'||b.ff[j][k][0]=='x')
                        {
                            fl=2;
                        }
                        else
                        {
                            fl=0;
                            break;
                        }
                    }
                }
                //cout<<fl<<"smlds\n";
                if(fl==0)
                {
                    continue;
                }
                else
                {
                    return fl;
                }
            }
        }
    }
    return 0;
}

node merge(node a,node b,int fl)
{
//	prt(a);prt(b);
    if(fl==2)
    {
        node c;
        for(int i=1;i<=a.len;i++)
        {
            for(int j=1;j<=b.len;j++)
            {
                if(a.f[i]==b.f[j])
                {
                    if(a.b[i]==b.b[j])
                    {
                        continue;
                    }
                    for(int k=1;k<=a.l[i];k++)
                    {
                        if(a.ff[i][k]!=b.ff[j][k])
                        {
                            if(a.ff[i][k][0]=='x')
                            {
                                string tp=a.ff[i][k],tpp=b.ff[j][k];
                                ss1=tp;
                                ss2=tpp;
                                c=a;
                                for(int ii=1;ii<=c.len;ii++)
                                {
                                    for(int jj=1;jj<=c.l[ii];jj++)
                                    {
                                        if(c.ff[ii][jj]==tp)
                                        {
                                            c.ff[ii][jj]=tpp;
                                        }
                                    }
                                }
                                return merge(c,b,1);
                            }
                            if(b.ff[j][k][0]=='x')
                            {
                                string tpp=a.ff[i][k],tp=b.ff[j][k];
                                ss1=tp;
                                ss2=tpp;
                                c=b;
                                for(int ii=1;ii<=c.len;ii++)
                                {
                                    for(int jj=1;jj<=c.l[ii];jj++)
                                    {
                                        if(c.ff[ii][jj]==tp)
                                        {
                                            c.ff[ii][jj]=tpp;
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
        node c;
        int f1=0,f2=0;
        for(int i=1;i<=a.len;i++)
        {
            for(int j=1;j<=b.len;j++)
            {
                if(a.f[i]==b.f[j])
                {
                    if(a.b[i]!=b.b[j])
                    {
                        int fl=1;
                        for(int k=1;k<=a.l[i];k++)
                        {
                            if(a.ff[i][k]!=b.ff[j][k])
                            {
                                fl=0;
                                break;
                            }
                        }
                        if(fl==0)
                        {
                            continue;
                        }
                        else
                        {
                            f1=i;
                            f2=j;
                            goto XX;
                        }
                    }
                }
            }
        }
        XX:
            for(int i=1;i<=a.len;i++)
            {
                if(i!=f1)
                {
                    c.len++;
                    c.f[c.len]=a.f[i];
                    c.b[c.len]=a.b[i];
                    c.l[c.len]=a.l[i];
                    for(int j=1;j<=a.l[i];j++)
                    {
                        c.ff[c.len][j]=a.ff[i][j];
                    }
                }
            }
            for(int i=1;i<=b.len;i++)
            {
                if(i!=f2)
                {
                    c.len++;
                    c.f[c.len]=b.f[i];
                    c.b[c.len]=b.b[i];
                    c.l[c.len]=b.l[i];
                    for(int j=1;j<=b.l[i];j++)
                    {
                        c.ff[c.len][j]=b.ff[i][j];
                    }
                }
            }
            return c;
    }
}

string change(node x)
{
    string tp="";
    for(int i=1;i<=x.len;i++)
    {
        if(x.b[i])
        {
            tp=tp+"~";
        }
        tp=tp+x.f[i];
        tp=tp+"(";
        for(int j=1;j<=x.l[i];j++)
        {
            tp=tp+x.ff[i][j];
            tp=tp+(j==x.l[i]?")":",");
        }
        if(i!=x.len)
        {
            tp=tp+"|";
        }
    }
    return tp;
}
bool checkans(node x)
{
    if(x.len!=1)
    {
        return 0;
    }
    if(x.b[1]!=0||x.l[1]!=1)
    {
        return 0;
    }
    string tp="ANSWER";
    if(x.f[1]==tp)
    {
        return 1;
    }
    return 0;
}

void dfs(int x)
{
    qq[++tt]=x;
    if(x<=10)
    {
        return;
    }
    dfs(ff1[x]);
    dfs(ff2[x]);
}

void solve()
{
    while(!q.empty())
    {
        string s=q.front().first;
        int num=q.front().second;
        q.pop();
        node t=split(s);
        if(t.len!=1)
        {
            q.push(make_pair(s,num));
            continue;
        }
        //bool flag=0;
        for(int i=1;i<=n;i++)
        {
            node tp=split(ch[i]);
            int tpp=0;
        //	cout<<s<<" "<<ch[i]<<endl;
            if((tpp=check(t,tp))&&!fgg[i][num])
            {
                node k=merge(t,tp,tpp);
                ch[++n]=change(k);
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
                    return;
                }
                q.push(make_pair(ch[n],n));
                fgg[i][num]=fgg[num][i]=1;
            //	fgg[i]=1;
                break;
            }
        }
        q.push(make_pair(s,num));
    }
}
