/**
 * @date: 2024.01.23
 * @problem: CF156D
 * @tags: 思维, 数学
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,k,mod,fa[100001],siz[100001];
int find(int id){
    if(fa[id]==id)return id;
    else return fa[id]=find(fa[id]);
}

int main(){
    scanf("%d%d%d",&n,&m,&mod);
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        int fu=find(u),fv=find(v);
        if(fu!=fv)fa[fu]=fv;
    }
    for(int i=1;i<=n;i++)siz[find(i)]++;
    long long answer=1;
    for(int i=1;i<=n;i++)
        if(find(i)==i)answer*=siz[i],answer%=mod,k++;
    if(k==1)return printf("%d\n",1%mod),0;
    for(int i=1;i<=k-2;i++)
        answer*=n,answer%=mod;
    printf("%lld\n",answer);
    return 0;
}
