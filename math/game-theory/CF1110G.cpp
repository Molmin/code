/**
 * @date: 2024.05.04
 * @problem: CF1110G
 * @tags: 博弈论, 图论
 */

#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> E[2000001];
char col[500001];
vector<int> deg[2000001];

inline void addEdge(int u,int v){
    E[u].push_back(v),E[v].push_back(u);
}

int solve(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    scanf("%s",col);
    for(int i=n;i>=1;i--){
        if(col[i-1]=='N')continue;
        n+=3;
        addEdge(n,i);
        addEdge(n,n-1);
        addEdge(n,n-2);
    }
    for(int i=1;i<=n;i++){
        if(E[i].size()>=4)return puts("White"),n;
        int cnt=0; for(int v :E[i])cnt+=E[v].size()>=2;
        if(E[i].size()==3&&cnt>=2)return puts("White"),n;
        deg[(int)E[i].size()].push_back(i);
    }
    assert(deg[3].size()<=2);
    if(deg[3].size()<=1)return puts("Draw"),n;
    function<int(int,int,int,int)> dfs=[&](int id,int target,int from,int dis){
        if(id==target)return dis;
        int ret=0x7fffffff;
        for(int v :E[id])
            if(v!=from)ret=min(ret,dfs(v,target,id,dis+1));
        return ret;
    };
    int dis=dfs(deg[3][0],deg[3][1],0,0);
    if(dis&1)puts("Draw");
    else puts("White");
    return n;
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        int n=solve();
        for(int i=1;i<=n;i++)
            E[i].clear(),deg[i].clear();
    }
    return 0;
}
