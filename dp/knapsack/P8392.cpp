/**
 * @date: 2024.05.05
 * @problem: P8392, LOJ3776
 * @tags: 背包, 贪心, 二进制分组
 */

#include<bits/stdc++.h>
using namespace std;

int m;
long long s,now,_a[601],*a=_a+300,_used[601],*used=_used+300;
pair<int,int> item[20000]; int cntItem;
long long _dp[2][180001],*dp[2]={_dp[0]+90000,_dp[1]+90000};

int main(){
    scanf("%d%lld",&m,&s);
    for(int i=-m;i<=m;i++){
        scanf("%lld",a+i);
        if(i<=0)now+=a[i]*i,used[i]=a[i];
    }
    for(int i=1;i<=m;i++){
        long long tmp=min((s-now)/i,a[i]);
        now+=tmp*i,used[i]+=tmp;
    }
    for(int i=-m;i<0;i++){
        long long tmp=min((s-now)/-i,a[i]);
        now+=tmp*-i,used[i]-=tmp;
    }
    if(s-now>m)return puts("impossible"),0;
    for(int i=-m;i<=m;i++){
        if(i==0)continue;
        int sum=min(a[i]-used[i],1ll*m*m);
        for(int k=1;k<=sum;k<<=1)
            sum-=k,item[++cntItem]={i*k,k};
        if(sum>0)item[++cntItem]={i*sum,sum};
        sum=min(used[i],1ll*m*m);
        for(int k=1;k<=sum;k<<=1)
            sum-=k,item[++cntItem]={-i*k,-k};
        if(sum>0)item[++cntItem]={-i*sum,-sum};
    }
    memset(_dp,0xc0,sizeof _dp);
    dp[0][0]=0;
    for(int i=1;i<=cntItem;i++)
        for(int j=m*m;j>=-m*m;j--){
            dp[i&1][j]=dp[(i-1)&1][j];
            if(abs(j-item[i].first)<=m*m)
                dp[i&1][j]=max(dp[i&1][j],dp[(i-1)&1][j-item[i].first]+item[i].second);
        }
    long long answer=dp[cntItem&1][s-now];
    for(int i=-m;i<=m;i++)answer+=used[i];
    if(answer<-1e9)puts("impossible");
    else printf("%lld\n",answer);
    return 0;
}
