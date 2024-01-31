/**
 * @date: 2024.01.31
 * @problem: CF1806F2, CF1806F1
 * @tags: 思维, 数学
 */

#include<bits/stdc++.h>
using namespace std;

int n,k;
long long m,a[1000001];
set<long long> S;
__int128 b[1000001]; int cntb;
__int128 presum[1000001],pregcd[1000001]={1};
int gcdUpdates[1000001],cntUpdates;

void print(__int128 answer){
    print(answer/10);
    printf("%d",int(answer%10));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        S.clear(),cntb=cntUpdates=0;
        scanf("%d%lld%d",&n,&m,&k);
        __int128 sum=0;
        for(int i=1;i<=n;i++){
            scanf("%d",a+i);
            if(S.find(a[i])==S.end())S.insert(a[i]);
            else b[++cntb]=a[i];
            sum+=a[i];
        }
        sort(b+1,b+1+cntb);
        for(int i=1;i<=cntb;i++)b[i]+=b[i-1];
        n=0; for(long long x :S)a[++n]=x;
        __int128 answer=0;
        for(int i=1;i<=n;i++){
            presum[i]=presum[i-1]+a[i];
            pregcd[i]=__gcd(pregcd[i-1],a[i]);
            if(pregcd[i]!=pregcd[i-1])gcdUpdates[++cntUpdates]=i;
            if(i<k&&k+1-i<=bcnt)answer=max(answer,sum-presum[i]+pregcd[i]-b[k+1-i]);
        }
        if(k<=cntb)answer=max(answer,sum-b[k]);
        gcdUpdates[cntUpdates+1]=n+1;
        for(int i=1;i<=cntUpdates;i++){
            __int128 maxn=-9e18;
            for(int j=gcdUpdates[i+1];j<=n;j++)
                maxn=max(maxn,(__int128)__gcd(pregcd[gcdUpdates[i]],a[j])-a[j]);
            for(int j=gcdUpdates[i];j<gcdUpdates[i+1];j++)
                if(j<k+1&&k-j<=cntb)answer=max(answer,sum+maxn-s[j]-b[k-j]);
        }
        print(answer);
        printf("\n");
    }
    return 0;
}
