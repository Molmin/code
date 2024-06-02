/**
 * @date: 2024.05.26
 * @problem: P3899, BZOJ3653
 * @tags: 图论, 树链剖分, 长链剖分
 */

#include<bits/stdc++.h>
using namespace std;

int n,q;
long long answer[300001];
vector<int> E[300001];
vector<pair<int,int>> queries[300001];

int fa[300001],siz[300001],dep[300001];
int maxlen[300001],longest[300001];
void init(int u,int father){
    fa[u]=father,dep[u]=dep[father]+1,siz[u]=1;
    for(int v :E[u]){
        if(v==father)continue;
        init(v,u);
        siz[u]+=siz[v];
        if(maxlen[v]>maxlen[longest[u]])longest[u]=v;
    }
    maxlen[u]=maxlen[longest[u]]+1;
}

long long dpval[600001],*dp[300001];
int usedcnt;
void decomposition(int u){
    if(longest[u]){
        dp[longest[u]]=dp[u]+1;
        decomposition(longest[u]);
    }
    for(int v :E[u]){
        if(v==fa[u]||v==longest[u])continue;
        dp[v]=dpval+usedcnt,usedcnt+=maxlen[v]+1;
        decomposition(v);
        for(int i=0;i<maxlen[v];i++)
            dp[u][i+1]+=dp[v][i];
    }
    dp[u][0]=dp[u][1]+siz[u]-1;
    for(pair<int,int> i :queries[u]){
        int qid=i.second,k=i.first;
        answer[qid]=dp[u][1]-(k+1<maxlen[u]?dp[u][k+1]:0)+(siz[u]-1ll)*min(dep[u]-1,k);
    }
}

int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    for(int i=1;i<=q;i++){
        int u,k;
        scanf("%d%d",&u,&k);
        queries[u].emplace_back(k,i);
    }
    init(1,0);
    dp[1]=dpval+1,usedcnt+=maxlen[1]+1;
    decomposition(1);
    for(int i=1;i<=q;i++)
        printf("%lld\n",answer[i]);
    return 0;
}
