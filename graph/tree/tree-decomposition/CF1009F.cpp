/**
 * @date: 2024.05.25
 * @problem: CF1009F
 * @tags: 图论, 树链剖分, 长链剖分, 动态规划, 树形动态规划
 */

#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> E[1000001];

int fa[1000001],maxlen[1000001],longest[1000001];
void init(int u,int father){
    fa[u]=father;
    for(int v :E[u]){
        if(v==father)continue;
        init(v,u);
        if(maxlen[v]>=maxlen[longest[u]])
            longest[u]=v,maxlen[u]=maxlen[v]+1;
    }
}

vector<int> dp[1000001];
int answer[1000001];
void decomposition(int u){
    if(!longest[u]){
        dp[u].push_back(1),answer[u]=0;
        return;
    }
    decomposition(longest[u]);
    swap(dp[u],dp[longest[u]]);
    dp[u].push_back(1);
    if(dp[u][answer[longest[u]]]==1)answer[u]=maxlen[u];
    else answer[u]=answer[longest[u]];
    for(int v :E[u]){
        if(v==fa[u]||v==longest[u])continue;
        decomposition(v);
        for(int i=maxlen[v];i>=0;i--){
            int target=maxlen[u]-(maxlen[v]-i+1);
            dp[u][target]+=dp[v][i];
            if(pair<int,int>(dp[u][target],target)>pair<int,int>(dp[u][answer[u]],answer[u]))
                answer[u]=target;
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    init(1,0);
    decomposition(1);
    for(int i=1;i<=n;i++)
        printf("%d\n",maxlen[i]-answer[i]);
    return 0;
}
