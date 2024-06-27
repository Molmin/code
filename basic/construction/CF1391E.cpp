/**
 * @date: 2024.06.09
 * @problem: CF1391E
 * @tags: 构造, 图论
 */

#include<bits/stdc++.h>
using namespace std;

int n,m;
int fa[500001],dep[500001];
vector<int> E[500001],samedep[500001];
bool vis[500001];

void dfs(int u,int father){
    vis[u]=true,fa[u]=father;
    dep[u]=dep[father]+1;
    samedep[dep[u]].push_back(u);
    for(int v :E[u])if(v!=father&&!vis[v])dfs(v,u);
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            E[i].clear(),samedep[i].clear(),vis[i]=false;
        for(int i=1;i<=m;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            E[u].push_back(v);
            E[v].push_back(u);
        }
        dfs(1,0);
        if(samedep[(n+1)/2].empty()){
            int cnt=0;
            for(int i=1;i<=n;i++)
                cnt+=samedep[i].size()/2;
            printf("PAIRING\n%d\n",cnt);
            for(int i=1;i<=n;i++)
                for(int j=0;j+1<samedep[i].size();j+=2)
                    printf("%d %d\n",samedep[i][j],samedep[i][j+1]);
        }
        else{
            int u=samedep[(n+1)/2][0];
            printf("PATH\n%d\n",(n+1)/2);
            while(u!=1){
                printf("%d ",u);
                u=fa[u];
            }
            printf("1\n");
        }
    }
    return 0;
}
