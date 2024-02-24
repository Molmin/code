/**
 * @date: 2024.02.22
 * @problem: AT_joisc2019_e
 * @tags: 动态规划, 数据结构, 差分
 */

#include<bits/stdc++.h>
using namespace std;

int n,m;
long long a[1000001],b[1000001];
long long s[1000001],t[1000001];
int p[1000001],q[1000001];
vector<pair<int,long long> > vec[1000001];
map<int,long long> diff;

inline bool cmp(pair<int,long long> x,pair<int,long long> y){
    return x.second>y.second;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lld%lld%d",a+i,s+i,p+i),a[i]+=a[i-1];
    for(int i=1;i<=m;i++)
        scanf("%lld%lld%d",b+i,t+i,q+i),b[i]+=b[i-1];
    long long answer=0;
    for(int i=1;i<=n;i++){
        if(s[i]<a[i])continue;
        int pos=upper_bound(b+1,b+1+m,s[i]-a[i])-b,v=p[i];
        answer+=v; if(1<=pos&&pos<=m)vec[i].push_back({pos,-v});
    }
    for(int i=1;i<=m;i++){
        if(t[i]<b[i])continue;
        int pos=upper_bound(a+1,a+1+n,t[i]-b[i])-a,v=q[i];
        if(1<=pos&&pos<=n)vec[pos].push_back({i,v});
        else answer+=v;
    }
    diff[m+1]=1ll<<62;
    for(int i=1;i<=n;i++){
        sort(vec[i].begin(),vec[i].end(),cmp);
        for(pair<int,long long> j :vec[i]){
            auto it=diff.lower_bound(j.first);
            int x=j.first; long long v=j.second;
            while(v<0&&it!=diff.end()){
                x=(*it).first,v+=(*it).second;
                it=diff.erase(it);
            }
            diff[x]=diff[x]+v;
        }
    }
    for(pair<int,long long> v :diff)
        if(1<=v.first&&v.first<=m)answer+=v.second;
    printf("%lld\n",answer);
    return 0;
}
