/**
 * @date: 2024.02.18
 * @problem: CF1801E
 * @tags: 图论, 并查集, 倍增
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

long long power(long long x,long long y=mod-2){
    if(y==0)return 1;
    long long tmp=power(x,y>>1);
    tmp=tmp*tmp%mod;
    if(y&1)tmp=tmp*x%mod;
    return tmp;
}

int n,l[200001],r[200001];
vector<int> son[200001];
long long answer=1;

int dep[200001],fa[200001][19];
int f[200001],f2[19][400001];
void init(int id,int father){
    dep[id]=dep[father]+1;
    fa[id][0]=father;
    for(int k=1;k<=18;k++)
        fa[id][k]=fa[fa[id][k-1]][k-1];
    f[id]=id;
    for(int k=0;k<=18;k++)
        f2[k][id]=id,f2[k][id+n]=id+n;
    for(int v :son[id])init(v,id);
}

inline int jump(int u,int dis){
    for(int k=18;k>=0;k--)
        if(dis&(1<<k))u=fa[u][k];
    return u;
}

inline int getlca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    for(int k=18;k>=0;k--)
        if(dep[u]-dep[v]>=(1<<k))
            u=fa[u][k];
    if(u==v)return u;
    for(int k=18;k>=0;k--)
        if(fa[u][k]!=fa[v][k])
            u=fa[u][k],v=fa[v][k];
    return fa[u][0];
}

int find(int id,int *fa){
    if(fa[id]==id)return id;
    else return fa[id]=find(fa[id],fa);
}

inline void merge(int x,int y){
    int fx=find(x,f),fy=find(y,f);
    if(fx==fy)return;
    answer=answer*power(max(r[fx]-l[fx]+1,0))%mod;
    answer=answer*power(max(r[fy]-l[fy]+1,0))%mod;
    f[fy]=fx;
    l[fx]=max(l[fx],l[fy]),r[fx]=min(r[fx],r[fy]);
    answer=answer*max(r[fx]-l[fx]+1,0)%mod;
}

void merge(int x,int y,int k){
    int fx=find(x,f2[k]),fy=find(y,f2[k]);
    if(fx==fy)return;
    if(k==0)merge(x,y);
    else{
        f2[k][fy]=fx;
        merge(x,y,k-1);
        merge(fa[x][k-1],fa[y][k-1],k-1);
    }
}

void mergeReverse(int x,int y,int k){
    int fx=find(x,f2[k]),fy=find(y,f2[k]);
    int extx=find(x+n,f2[k]),exty=find(y+n,f2[k]);
    if(fx==exty)return;
    if(k==0)merge(x,y);
    else{
        f2[k][exty]=fx;
        f2[k][find(y,f2[k])]=find(x+n,f2[k]);
        mergeReverse(x,fa[y][k-1],k-1);
        mergeReverse(fa[x][k-1],y,k-1);
    }
}

int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        int f; scanf("%d",&f);
        son[f].push_back(i);
    }
    init(1,0);
    for(int i=1;i<=n;i++){
        scanf("%d%d",l+i,r+i);
        answer=answer*(r[i]-l[i]+1)%mod;
    }
    int m; scanf("%d",&m);
    while(m--){
        int u1,v1,u2,v2,len;
        scanf("%d%d%d%d",&u1,&v1,&u2,&v2);
        int lca1=getlca(u1,v1);
        int lca2=getlca(u2,v2);
        if(dep[u1]-dep[lca1]>dep[u2]-dep[lca2])
            swap(u1,u2),swap(v1,v2),swap(lca1,lca2);
        len=dep[u1]-dep[lca1];
        for(int k=18;k>=0;k--)
            if(len&(1<<k)){
                merge(u1,u2,k);
                u1=fa[u1][k],u2=fa[u2][k];
            }
        len=dep[v2]-dep[lca2];
        for(int k=18;k>=0;k--)
            if(len&(1<<k)){
                merge(v1,v2,k);
                v1=fa[v1][k],v2=fa[v2][k];
            }
        len=dep[v1]-dep[lca1]+1;
        for(int k=18;k>=0;k--)
            if(len&(1<<k)){
                len-=1<<k,u1=jump(v1,len);
                mergeReverse(u1,u2,k);
                u2=fa[u2][k];
            }
        printf("%lld\n",answer);
    }
    return 0;
}
