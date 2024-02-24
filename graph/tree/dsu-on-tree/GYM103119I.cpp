/**
 * @date: 2024.02.23
 * @problem: GYM103119I
 * @tags: 数学, 博弈论, Nim 游戏, 图论, 树上启发式合并
 */

#include<bits/stdc++.h>
using namespace std;

int m,n=1,a[20002],b[20002];
int fa[20002],answer[20002];
vector<int> qid[20002];

struct Edge{
    int to,nxt;
}edge[20001];
int cntEdge,head[20002];
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int siz[20002],heavy[20002];
void init(int id){
    siz[id]=1,heavy[id]=-1;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        init(v);
        siz[id]+=siz[v];
        if(siz[v]>siz[heavy[id]])
            heavy[id]=v;
    }
}

int top[20002];
void decomposition(int id,int col){
    top[id]=col;
    if(heavy[id])decomposition(heavy[id],col);
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==heavy[id])continue;
        decomposition(v,v);
    }
}

int dp[16][1<<16],g[1<<16];
void dfs(int id,int cnt,int val){
    for(int i :qid[id])answer[i]=dp[cnt][val];
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==heavy[id])continue;
        for(int j=0;j<(1<<16);j++)
            dp[cnt+1][j]=dp[cnt][j];
        for(int j=0;j<(1<<16);j++)
            dp[cnt+1][j^a[v]]=min(dp[cnt+1][j^a[v]],dp[cnt][j]+b[v]);
        dfs(v,cnt+1,val^a[v]);
    }
    if(heavy[id]){
        for(int j=0;j<(1<<16);j++)g[j]=0x3fffffff;
        for(int j=0;j<(1<<16);j++)
            g[j^a[heavy[id]]]=min(g[j^a[heavy[id]]],dp[cnt][j]+b[heavy[id]]);
        for(int j=0;j<(1<<16);j++)
            dp[cnt][j]=min(dp[cnt][j],g[j]);
        dfs(heavy[id],cnt,val^a[heavy[id]]);
    }
}

int main(){
    scanf("%d",&m);
    for(int i=1,now=1;i<=m;i++){
        string op; cin>>op;
        if(op=="ADD"){
            addEdge(now,++n);
            fa[n]=now,now=n;
            scanf("%d%d",a+now,b+now);
        }
        else now=fa[now];
        qid[now].push_back(i);
    }
    init(1);
    decomposition(1,0);
    for(int i=1;i<(1<<16);i++)dp[0][i]=0x3fffffff;
    dfs(1,0,0);
    for(int i=1;i<=m;i++)
        printf("%d\n",answer[i]);
    return 0;
}
