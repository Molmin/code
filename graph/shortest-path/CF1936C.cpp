/**
 * @date: 2024.03.15
 * @problem: CF1936C
 * @tags: 图论, 分层图, 差分, 最短路
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,c[400001],p[200001];
vector<int> a[400001];

vector<pair<int,int>> E[800001];
inline void addEdge(int u,int v,int w){
    E[u].push_back({v,w});
}
long long dis[800001];
bool vis[800001];

inline int getSymbol(int i,int j){
    return (i-1)*(m+1)+(j+1);
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",c+i);
        for(int i=1;i<=n*(m+1);i++)
            E[i].clear(),dis[i]=1e18,vis[i]=false;
        for(int i=1;i<=n;i++){
            a[i].resize(m+1);
            for(int j=1;j<=m;j++)
                scanf("%d",&a[i][j]);
        }
        for(int j=1;j<=m;j++){
            for(int i=1;i<=n;i++)p[i]=i;
            sort(p+1,p+1+n,[&](int x,int y){
                return a[x][j]<a[y][j];
            });
            for(int i=1;i<n;i++){
                int x=p[i],y=p[i+1];
                addEdge(getSymbol(x,j),getSymbol(y,j),0);
                addEdge(getSymbol(y,j),getSymbol(x,j),a[y][j]-a[x][j]);
            }
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                addEdge(getSymbol(i,0),getSymbol(i,j),0);
                addEdge(getSymbol(i,j),getSymbol(i,0),c[i]);
            }
        priority_queue<pair<long long,int>> Q;
        dis[getSymbol(1,0)]=0;
        Q.push({0,getSymbol(1,0)});
        while(!Q.empty()){
            int u=Q.top().second; Q.pop();
            if(vis[u])continue;
            vis[u]=true;
            for(pair<int,int> i :E[u]){
                int v=i.first,w=i.second;
                if(w+dis[u]<dis[v]){
                    dis[v]=w+dis[u];
                    Q.push({-dis[v],v});
                }
            }
        }
        printf("%lld\n",dis[getSymbol(n,0)]);
    }
    return 0;
}
