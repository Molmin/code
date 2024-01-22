/**
 * @date: 2024.01.22
 * @problem: QOJ4829
 * @tags: 图论, 通信
 * @note: It can't be accepted
 */

#include<bits/stdc++.h>
using namespace std;
const int k=5;

int n,m;
set<pair<int,int> > S;
int deg[1001],x[1001];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        S.insert({u,v});
        S.insert({v,u});
        deg[u]++,deg[v]++;
    }
    for(int i=1;i<=n;i++)x[i]=i;
    sort(x+1,x+1+n,[&](int x,int y){return deg[x]>deg[y];});
    reverse(x+1,x+1+k);
    do{
        bool flag=true;
        for(int i=1;i<=k;i++)
            if(S.find({x[i],x[i==k?1:i+1]})==S.end())flag=false;
        if(flag)return printf("ok"),0;
    }while(next_permutation(x+1,x+1+k));
    sort(x+1,x+1+k);
    vector<pair<int,int> > vec;
    for(int i=1;i<=k;i++){
        int u=x[i],v=x[i==k?1:i+1];
        if(S.find({u,v})==S.end())vec.push_back({u,v});
    }
    printf("mark\n%d\n",(int)vec.size());
    for(pair<int,int> e :vec)
        printf("%d %d\n",e.first,e.second);
    return 0;
}
