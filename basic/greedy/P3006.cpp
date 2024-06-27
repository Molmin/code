/**
 * @date: 2024.06.08
 * @problem: P3006
 * @tags: 贪心, 数据结构, 优先队列, 并查集
 */

#include<bits/stdc++.h>
using namespace std;

int n,q;
int f[100001],lim[100001];
long long c[100001],v[100001];
vector<int> sons[100001];

int t[10001],query[10001];
long long answer[10001];

int fa[100001];
int find(int x){
    if(x==fa[x])return x;
    else return fa[x]=find(fa[x]);
}

int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=2;i<=n;i++){
        scanf("%d%lld%d",f+i,c+i,lim+i);
        sons[f[i]].push_back(i);
    }
    for(int i=1;i<=q;i++)
        scanf("%d",t+i),query[i]=i;
    sort(query+1,query+1+q,[&](int x,int y){return t[x]<t[y];});
    priority_queue<pair<long long,int>> Q;
    for(int i=1;i<=n;i++){
        v[i]=lim[i];
        for(int j :sons[i])v[i]-=lim[j];
        if(v[i]>0)Q.emplace(-c[i]/v[i],i);
    }
    int pos=1;
    while(!Q.empty()){
        long long end=-Q.top().first;
        while(pos<=q&&t[query[pos]]<=end){
            answer[query[pos]]=c[1]-1ll*v[1]*t[query[pos]];
            pos++;
        }
        int u=Q.top().second; Q.pop();
        if(find(u)!=u)continue;
        int fu=find(f[u]);
        c[fu]+=c[u],v[fu]+=v[u],fa[u]=fu;
        if(v[fu]>0)Q.emplace(-c[fu]/v[fu],fu);
    }
    while(pos<=q)answer[query[pos]]=c[1],pos++;
    for(int i=1;i<=q;i++)
        printf("%lld\n",answer[i]);
    return 0;
}
