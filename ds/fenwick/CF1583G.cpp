/**
 * @date: 2024.07.04
 * @problem: CF1583G
 * @tags: 数据结构, 树状数组
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

int n,m,f[200001];
pair<int,int> a[200001],b[200001];
inline bool cmp(pair<int,int> x,pair<int,int> y){
    return x.second<y.second;
}

struct BIT{
    int v[400001];
    int lowbit(int x){
        return x&-x;
    }
    void add(int x,int val){
        for(;x<=n*2;x+=lowbit(x))v[x]+=val,v[x]%=mod;
    }
    int query(int x){
        long long ret=0;
        for(;x;x-=lowbit(x))ret+=v[x];
        return ret%mod;
    }
}T1,T2;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i].first,&a[i].second);
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        int x; scanf("%d",&x);
        b[i]=a[x];
    }
    sort(a+1,a+1+n,cmp);
    sort(b+1,b+1+m,cmp);
    for(int i=1;i<=n;i++){
        f[i]=(T1.query(a[i].second)-T1.query(a[i].first)+1+mod)%mod;
        T1.add(a[i].first,f[i]);
    }
    long long answer=0;
    for(int i=n,j=m;i>=1;i--){
        if(j&&b[j]==a[i])T2.add(a[i].first,1),j--;
        if(T2.query(a[i].first-1)<T2.query(n*2))answer+=f[i];
    }
    printf("%lld\n",answer%mod);
    return 0;
}
