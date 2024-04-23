/**
 * @date: 2024.04.23
 * @problem: BZOJ3451
 * @tags: 多项式, 快速傅里叶变换, 图论, 点分治, 数学, 概率期望
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,modg=3;

int power(int x,int y=mod-2){
    if(y==0)return 1;
    int tmp=power(x,y>>1);
    tmp=1ll*tmp*tmp%mod;
    if(y&1)tmp=1ll*tmp*x%mod;
    return tmp;
}

inline void NTT(int *a,int len,int k=1){
    vector<int> rev;
    for(int i=0;i<len;i++)
        rev.push_back((i?rev[i>>1]:0)>>1|((i&1)?(len>>1):0));
    for(int i=0;i<len;i++)
        if(i<rev[i])swap(a[i],a[rev[i]]);
    for(int h=2;h<=len;h<<=1){
        int w=power(modg,(mod-1)/h);
        if(k==-1)w=power(w,h-1);
        for(int i=0;i<len;i+=h){
            int now=1;
            for(int j=i;j<i+(h>>1);j++,now=1ll*now*w%mod){
                int x=a[j],y=1ll*now*a[j+(h>>1)]%mod;
                a[j]=(x+y)%mod,a[j+(h>>1)]=(x-y+mod)%mod;
            }
        }
    }
    if(k==-1)for(int i=0,inv=power(len);i<len;i++)a[i]=1ll*a[i]*inv%mod;
}

int n;
vector<int> E[30001];

bool cut[30001];
int siz[30001],maxSize[30001],root;
void findRoot(int id,int father,int n){
    siz[id]=1,maxSize[id]=0;
    for(int v :E[id]){
        if(cut[v]||v==father)continue;
        findRoot(v,id,n);
        siz[id]+=siz[v];
        maxSize[id]=max(maxSize[id],siz[v]);
    }
    maxSize[id]=max(maxSize[id],n-siz[id]);
    if(!root||maxSize[id]<maxSize[root])root=id;
}

int cntlen[30000];
void init(int id,int father,int dep,vector<int> &cntdep){
    while(cntdep.size()<=dep)cntdep.push_back(0);
    cntdep[dep]++,siz[id]=1;
    for(int v :E[id]){
        if(cut[v]||v==father)continue;
        init(v,id,dep+1,cntdep);
        siz[id]+=siz[v];
    }
}

void solve(int id,int n){
    root=0; findRoot(id,0,n);
    cut[root]=true;
    vector<vector<int>> cntdep;
    vector<int> now(1,1);
    for(int v :E[root]){
        if(cut[v])continue;
        int id=cntdep.size();
        cntdep.push_back(vector<int>());
        init(v,root,1,cntdep[id]);
    }
    sort(cntdep.begin(),cntdep.end(),[&](vector<int> &x,vector<int> &y){
        return x.size()<y.size();
    });
    for(int i=0;i<cntdep.size();i++){
        int len=1; while(len<=cntdep[i].size()+now.size())len<<=1;
        vector<int> tmp(len,0);
        while(cntdep[i].size()<len)cntdep[i].push_back(0);
        while(now.size()<len)now.push_back(0);
        NTT(&cntdep[i][0],len);
        NTT(&now[0],len);
        for(int j=0;j<len;j++)tmp[j]=1ll*cntdep[i][j]*now[j]%mod;
        NTT(&cntdep[i][0],len,-1);
        NTT(&now[0],len,-1);
        NTT(&tmp[0],len,-1);
        for(int j=0;j<len;j++)now[j]+=cntdep[i][j],cntlen[j]+=tmp[j];
        while(!now.back())now.pop_back();
    }
    for(int v :E[root]){
        if(cut[v])continue;
        solve(v,siz[v]);
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v),u++,v++;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    solve(1,n);
    double answer=n;
    for(int i=1;i<n;i++)
        answer+=cntlen[i]*2/(1.0+i);
    printf("%.4lf\n",answer);
    return 0;
}
