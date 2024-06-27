/**
 * @date: 2024.06.10
 * @problem: CF1396E
 * @tags: 构造, 图论, 树的重心
 * @note: 构造调整法好题
 */

#include<bits/stdc++.h>
using namespace std;

int n;
long long k,now;
set<int> E[100001];
bool vis[100001];

void removeEdge(int u,int v){
    E[u].erase(v),E[v].erase(u);
}

int siz[100001],maxsiz[100001],root;
void findRoot(int u,int father){
    siz[u]=1;
    for(int v :E[u]){
        if(v==father)continue;
        findRoot(v,u);
        siz[u]+=siz[v];
        maxsiz[u]=max(maxsiz[u],siz[v]);
    }
    maxsiz[u]=max(maxsiz[u],n-siz[u]);
    if(!root||maxsiz[u]<maxsiz[root])root=u;
}

int dep[100001],fa[100001];
void init(int u,int father){
    dep[u]=dep[father]+1;
    siz[u]=1,fa[u]=father;
    for(int v :E[u]){
        if(v==father)continue;
        init(v,u);
        siz[u]+=siz[v];
    }
}

set<pair<int,int>> lca[100001];
void listLCA(int u,int id){
    int cnt=0;
    for(int v :E[u]){
        if(v==fa[u])continue;
        cnt++,listLCA(v,id);
    }
    if(cnt)lca[id].insert({dep[u],u});
}

vector<int> target[100001];
void listTarget(int u,int id){
    if(!vis[u])target[id].push_back(u);
    for(int v :E[u]){
        if(v==fa[u])continue;
        listTarget(v,id);
    }
}

int main(){
    scanf("%d%lld",&n,&k);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        E[u].insert(v);
        E[v].insert(u);
    }
    findRoot(1,0);
    dep[0]=-1,init(root,0);
    long long minn=0,maxn=0;
    for(int i=1;i<=n;i++)
        if(i!=root)minn+=siz[i]&1,maxn+=siz[i];
    if(k<minn||k>maxn||(k&1)!=(minn&1))return puts("NO"),0;
    puts("YES");
    now=maxn;
    priority_queue<pair<int,int>> Q;
    for(int u :E[root]){
        Q.push({siz[u],u});
        listLCA(u,u);
    }
    while(true){
        int u=Q.top().second;
        if(now==k)break;
        Q.pop();
        if(siz[u]==1)break;
        siz[u]-=2;
        int x=(*lca[u].rbegin()).second;
        if(now-dep[x]*2>k){
            now-=dep[x]*2;
            vector<int> match;
            for(int v :E[x]){
                if(v!=fa[x])match.push_back(v);
                if(match.size()==2)break;
            }
            if(match.size()==1){
                vis[x]=vis[match[0]]=true;
                printf("%d %d\n",x,match[0]);
                removeEdge(x,match[0]);
                removeEdge(x,fa[x]);
                lca[u].erase({dep[x],x});
                if(E[fa[x]].size()==1)lca[u].erase({dep[fa[x]],fa[x]});
            }
            else{
                vis[match[0]]=vis[match[1]]=true;
                printf("%d %d\n",match[0],match[1]);
                removeEdge(x,match[0]);
                removeEdge(x,match[1]);
                if(E[x].size()==1)lca[u].erase({dep[x],x});
            }
        }
        else{
            int require=(now-k)/2,son=-1;
            for(int v :E[x])
                if(v!=fa[x]){
                    son=v; break;
                }
            while(dep[x]>require)x=fa[x];
            printf("%d %d\n",x,son);
            vis[x]=vis[son]=true,now=k;
        }
        if(siz[u])Q.push({siz[u],u});
    }
    for(int u :E[root])listTarget(u,u);
    while(Q.size()>=2){
        int x=Q.top().second; Q.pop();
        int y=Q.top().second; Q.pop();
        int u=target[x].back(),v=target[y].back();
        printf("%d %d\n",u,v);
        target[x].pop_back(),target[y].pop_back();
        siz[x]--,siz[y]--;
        if(siz[x])Q.push({siz[x],x});
        if(siz[y])Q.push({siz[y],y});
    }
    printf("%d %d\n",root,target[Q.top().second].back());
    return 0;
}
