/**
 * @date: 2024.02.15
 * @problem: QOJ7881, GYM104857H
 * @tags: 数学, 二分
 */

#include<bits/stdc++.h>
using namespace std;

long long mod,pos[10000001],f[10000001],g[10000001];
int cnt;

inline long long F(long long x){
    return f[upper_bound(pos+1,pos+1+cnt,x)-pos-1];
}
inline long long G(long long x){
    return g[upper_bound(pos+1,pos+1+cnt,x)-pos-1];
}

void init(long long n){
    priority_queue<long long,vector<long long>,greater<long long>> Q;
    pos[++cnt]=0;
    while(pos[cnt]<n){
        while(!Q.empty()&&Q.top()<=pos[cnt])Q.pop();
        long long v=Q.empty()?pos[cnt]+1:Q.top();
        if(v>n)break;
        while(!Q.empty()&&Q.top()<=v)Q.pop();
        pos[++cnt]=v;
        f[cnt]=max(v,G(v/2)+G(v/3)+G(v/5)+G(v/7));
        g[cnt]=max(v,F(v/2)+F(v/3)+F(v/4)+F(v/5));
        if(f[cnt]==f[cnt-1]&&g[cnt]==g[cnt-1])cnt--;
        if(v*2<=n)Q.push(v*2);
        if(v*3<=n)Q.push(v*3);
        if(v*4<=n)Q.push(v*4);
        if(v*5<=n)Q.push(v*5);
        if(v*7<=n)Q.push(v*7);
    }
}

int main(){
    int T;
    scanf("%lld %lld %d %lld",f+1,g+1,&T,&mod);
    init(1e15);
    while(T--){
        long long x; scanf("%lld\n",&x);
        printf("%lld %lld\n",F(x)%mod,G(x)%mod);
    }
    return 0;
}
