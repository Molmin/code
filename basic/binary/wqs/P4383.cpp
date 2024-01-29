/**
 * @date: 2024.01.29
 * @problem: P4383
 * @tags: WQS 二分
 */

#include<bits/stdc++.h>
using namespace std;

int n,k;

struct Edge{
    int to,nxt,w;
}edge[600001];
int cntEdge,head[300001];
inline void addEdge(int u,int v,int w){
    edge[++cntEdge]={v,head[u],w},head[u]=cntEdge;
}

int fa[300001];
void init(int id,int father){
    fa[id]=father;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father)continue;
        init(v,id);
    }
}

struct Status{
    long long sum;
    int total;
    inline bool operator<(const Status &x){
        if(sum==x.sum)return total>x.total;
        else return sum<x.sum;
    }
    inline Status operator+(const Status &x){
        return{sum+x.sum,total+x.total};
    }
    inline Status operator+(const int x){
        return{sum+x,total};
    }
}dp[300001][3];

inline void updateStatus(Status &x,Status y){
    if(x<y)x=y;
}

void dfs(int id,long long mid){
    dp[id][0]=dp[id][1]=dp[id][2]={0,0};
    updateStatus(dp[id][2],{-mid,1});
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==fa[id])continue;
        dfs(v,mid);
        updateStatus(dp[id][2],dp[id][2]+dp[v][0]);
        updateStatus(dp[id][2],dp[id][1]+dp[v][1]+edge[i].w+Status{-mid,1});
        updateStatus(dp[id][1],dp[id][1]+dp[v][0]);
        updateStatus(dp[id][1],dp[id][0]+dp[v][1]+edge[i].w);
        updateStatus(dp[id][0],dp[id][0]+dp[v][0]);
    }
    updateStatus(dp[id][0],dp[id][1]+Status{-mid,1});
    updateStatus(dp[id][0],dp[id][2]);
}

int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    init(1,0);
    long long l=-1e12,r=1e12;
    while(l<r){
        long long mid=l+r>>1;
        dfs(1,mid);
        if(dp[1][0].total==k+1){
            printf("%lld\n",dp[1][0].sum+mid*(k+1));
            return 0;
        }
        if(dp[1][0].total>k+1)l=mid+1;
        else r=mid;
    }
    dfs(1,l);
    printf("%lld\n",dp[1][0].sum+l*(k+1));
    return 0;
}
