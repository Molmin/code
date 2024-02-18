/**
 * @date: 2024.02.17
 * @problem: CF1916F
 * @tags: 构造, 图论, Tarjan
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,n1,n2;

struct Edge{
    int to,nxt;
}edge[10001];
int cntEdge,head[2001];
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

bool vis[2001],cut[2001],selected[2001];
int cntdfn,dfn[2001],low[2001];
void tarjan(int id,int father){
    vis[id]=true;
    dfn[id]=low[id]=++cntdfn;
    bool iscut=false;
    int cnt=0;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father||selected[v])continue;
        if(!dfn[v]){
            tarjan(v,id);
            cnt++,low[id]=min(low[id],low[v]);
            if(low[v]>=dfn[id])iscut=true;
        }
        else if(vis[v])low[id]=min(low[id],dfn[v]);
    }
    cut[id]=iscut&&(father||cnt>1);
    vis[id]=false;
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        memset(selected,false,sizeof selected);
        scanf("%d%d%d",&n1,&n2,&m);
        n=n1+n2;
        cntEdge=0;
        memset(head,0,sizeof head);
        for(int i=1;i<=m;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        selected[1]=true;
        for(int t=2;t<=n1;t++){
            memset(vis,false,sizeof vis);
            memset(cut,false,sizeof vis);
            memset(dfn,0,sizeof dfn);
            memset(low,0,sizeof low);
            cntdfn=0;
            {
                int i=1; while(selected[i])i++;
                tarjan(i,0);
            }
            for(int i=1;i<=n;i++){
                if(selected[i]||cut[i])continue;
                bool flag=false;
                for(int j=head[i];j&&!flag;j=edge[j].nxt)
                    if(selected[edge[j].to])flag=true;
                if(flag){
                    selected[i]=true;
                    break;
                }
            }
        }
        for(int i=1;i<=n;i++)
            if(selected[i])printf("%d ",i);
        printf("\n");
        for(int i=1;i<=n;i++)
            if(!selected[i])printf("%d ",i);
        printf("\n");
    }
    return 0;
}
