/**
 * @date: 2024.02.15
 * @problem: CF1924E, AT_arc114_e
 * @tags: 数学, 组合数学, 概率期望
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

int inv[2000001];

int main(){
    inv[0]=inv[1]=1;
    for(int i=2;i<=2000000;i++)
        inv[i]=mod-1ll*(mod/i)*inv[mod%i]%mod;
    int T; scanf("%d",&T);
    while(T--){
        int n,m; long long k;
        scanf("%d%d%lld",&n,&m,&k);
        long long answer=1ll*n*m>=k;
        for(int i=1;i<n;i++)
            if(1ll*i*m>=k)answer+=inv[i+m-1];
        answer%=mod;
        for(int j=1;j<m;j++)
            if(1ll*n*j>=k)answer+=inv[n+j-1];
        answer%=mod;
        for(int i=2;i<=n+m-2;i++){
            // 1<=x<=n-1, 1<=y<=m-1
            // x+y=i, x*y>=k
            // 1<=y<=m-1 => 1<=i-x<=m-1 => i-m+1<=x<=i-1
            // x*(i-x)>=k => x^2-i*x+k<=0
            long long delta=1ll*i*i-4*k;
            if(delta<0)continue;
            int minn=max(1,max(i-m+1,(int)ceil((i-sqrt(delta))/2)));
            int maxn=min(n-1,min(i-1,int((i+sqrt(delta))/2)));
            if(minn>maxn)continue;
            answer+=1ll*inv[i]*inv[i-1]%mod*2%mod*(maxn-minn+1)%mod;
        }
        printf("%lld\n",answer%mod);
    }
    return 0;
}
