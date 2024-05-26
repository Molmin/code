/**
 * @date: 2024.05.25
 * @problem: P5904, BZOJ4543, P3565, BZOJ3522, LOJ2431
 * @tags: 图论, 树链剖分, 长链剖分, 动态规划, 树形动态规划
 */

#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> E[100001];

int fa[100001],maxlen[100001],longest[100001];
void init(int u,int father){
    fa[u]=father;
    for(int v :E[u]){
        if(v==father)continue;
        init(v,u);
        if(maxlen[v]>maxlen[longest[u]])longest[u]=v;
    }
    maxlen[u]=maxlen[longest[u]]+1;
}

long long *f[100001],*g[100001],fval[200001],gval[200001],answer;
int usedcnt;
void decomposition(int u){
    if(longest[u]){
        f[longest[u]]=f[u]+1,g[longest[u]]=g[u]-1;
        decomposition(longest[u]);
    }
    f[u][0]=1,answer+=g[u][0];
    for(int v :E[u]){
        if(v==fa[u]||v==longest[u])continue;
        f[v]=fval+usedcnt,g[v]=gval+usedcnt+maxlen[v];
        usedcnt+=maxlen[v]*2;
        decomposition(v);
        for(int i=0;i<maxlen[v];i++){
            answer+=f[v][i]*g[u][i+1];
            if(i)answer+=f[u][i-1]*g[v][i];
        }
        for(int i=0;i<maxlen[v];i++){
            if(i)g[u][i-1]+=g[v][i];
            g[u][i+1]+=f[u][i+1]*f[v][i];
            f[u][i+1]+=f[v][i];
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    init(1,0);
    f[1]=fval,g[1]=gval+maxlen[1],usedcnt+=maxlen[1]*2;
    decomposition(1);
    printf("%lld\n",answer);
    return 0;
}
