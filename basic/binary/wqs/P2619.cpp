/**
 * @date: 2024.01.28
 * @problem: P2619, BZOJ2654
 * @tags: WQS 二分
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,need;

struct Edge{
    int u,v,w,neww,col;
}edge[100001];

int fa[50001];
int find(int id){
    if(fa[id]==id)return id;
    else return fa[id]=find(fa[id]);
}

int cnt;
int kruskal(){
    sort(edge+1,edge+1+m,[&](Edge x,Edge y){
        if(x.neww!=y.neww)return x.neww<y.neww;
        else return x.col<y.col;
    });
    for(int i=1;i<=n;i++)fa[i]=i;
    cnt=0;
    int sum=0,totalEdge=0;
    for(int i=1;i<=m&&totalEdge<n-1;i++){
        int u=edge[i].u,v=edge[i].v;
        int fu=find(u),fv=find(v);
        if(fu==fv)continue;
        totalEdge++;
        cnt+=!edge[i].col;
        sum+=edge[i].neww;
        fa[fu]=fv;
    }
    return sum;
}

int main(){
    scanf("%d%d%d",&n,&m,&need);
    for(int i=1;i<=m;i++){
        int u,v,w,col;
        scanf("%d%d%d%d",&u,&v,&w,&col);
        edge[i]={u+1,v+1,w,0,col};
    }
    int l=-100,r=100,answer=-1;
    while(l<=r){
        int mid=l+r>>1;
        for(int i=1;i<=m;i++)
            if(!edge[i].col)edge[i].neww=edge[i].w+mid;
            else edge[i].neww=edge[i].w;
        int res=kruskal();
        if(cnt>=need)l=mid+1,answer=res-mid*need;
        else r=mid-1;
    }
    printf("%d\n",answer);
    return 0;
}
