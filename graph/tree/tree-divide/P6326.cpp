/**
 * @date: 2024.02.24
 * @problem: P6326, BZOJ4182
 * @tags: 图论, 点分治, 动态规划, 背包
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,w[501],c[501],d[501],answer;

struct Edge{
    int to,nxt;
}edge[1001];
int cntEdge,head[501];
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

bool cut[501];
int root,siz[501],maxSize[501];
void findRoot(int id,int father,int n){
    siz[id]=1,maxSize[id]=0;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father||cut[v])continue;
        findRoot(v,id,n);
        siz[id]+=siz[v];
        maxSize[id]=max(maxSize[id],siz[v]);
    }
    maxSize[id]=max(maxSize[id],n-siz[id]);
    if(!root||maxSize[id]<maxSize[root])root=id;
}

int cntdfn,dfn[501],rnk[501],endAt[501];
void init(int id,int father){
    siz[id]=1,dfn[id]=++cntdfn,rnk[cntdfn]=id;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father||cut[v])continue;
        init(v,id);
        siz[id]+=siz[v];
    }
    endAt[id]=cntdfn;
}

int dp[502][4001];
void solve(int id){
    cntdfn=0; init(id,0);
    memset(dp[cntdfn+1],0,sizeof dp[cntdfn+1]);
    for(int i=cntdfn;i>=1;i--){
        memset(dp[i],0,sizeof dp[i]);
        vector<pair<int,int> > vec;
        int pos=rnk[i],cnt=d[pos]-1;
        for(int k=1;k<=cnt;k<<=1)
            vec.push_back({k*w[pos],k*c[pos]}),cnt-=k;
        if(cnt)vec.push_back({cnt*w[pos],cnt*c[pos]});
        for(int j=m;j>=c[pos];j--)
            dp[i][j]=dp[i+1][j-c[pos]]+w[pos];
        for(pair<int,int> item :vec)
            for(int j=m;j>=item.second;j--)
                dp[i][j]=max(dp[i][j],dp[i][j-item.second]+item.first);
        for(int j=0;j<=m;j++)
            dp[i][j]=max(dp[i][j],dp[endAt[pos]+1][j]);
    }
    answer=max(answer,dp[1][m]);
    cut[id]=true;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(cut[v])continue;
        root=0; findRoot(v,0,siz[v]);
        solve(root);
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(head,0,sizeof head);
        memset(cut,false,sizeof cut);
        cntEdge=answer=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",w+i);
        for(int i=1;i<=n;i++)
            scanf("%d",c+i);
        for(int i=1;i<=n;i++)
            scanf("%d",d+i);
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        root=0; findRoot(1,0,n);
        solve(root);
        printf("%d\n",answer);
    }
    return 0;
}
