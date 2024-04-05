/**
 * @date: 2024.02.23
 * @problem: CF1252F
 * @tags: 树哈希, 树的重心
 */

#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
mt19937 mt_rand(random_device{}());
long long base[4001];

int n,deg[4001];

struct Edge{
    int to,nxt;
}edge[8001];
int cntEdge,head[4001];
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

bool cut[4001];
int siz[4001],maxSize[4001];
vector<int> root;
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
    if(maxSize[id]<=(n>>1))root.push_back(id);
}

void initSize(int id,int father){
    siz[id]=1;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father||cut[v])continue;
        initSize(v,id);
        siz[id]+=siz[v];
    }
}

ull calcHash(int id,int father){
    siz[id]=1;
    ull res=1;
    vector<pair<int,ull>> vec;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father||cut[v])continue;
        ull tmp=calcHash(v,id);
        siz[id]+=siz[v];
        vec.push_back({siz[v],tmp});
    }
    sort(vec.begin(),vec.end());
    for(pair<int,ull> i :vec)
        res=res*base[i.first]+i.second;
    return res;
}

inline bool check(int id){
    cut[id]=true;
    ull res=0;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        initSize(v,0);
        root.clear(); findRoot(v,0,siz[v]);
        ull maxn=0;
        for(int j :root)maxn=max(maxn,calcHash(j,0));
        if(!res)res=maxn;
        if(res!=maxn){
            cut[id]=false;
            return false;
        }
    }
    cut[id]=false;
    return true;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)base[i]=mt_rand();
    base[0]=1;
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
        deg[u]++,deg[v]++;
    }
    findRoot(1,0,n);
    vector<int> target=root;
    sort(target.begin(),target.end(),[&](int u,int v){
        return deg[u]>deg[v];
    });
    for(int v :target)if(check(v))
        return printf("%d\n",deg[v]),0;
    puts("-1");
    return 0;
}
