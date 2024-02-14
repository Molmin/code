/**
 * @date: 2024.02.14
 * @problem: GYM102268J
 * @tags: WQS 二分, 动态规划, 动态规划优化, 斜率优化
 */

#include<bits/stdc++.h>
using namespace std;
#define ll __int128

int n,k,a[100001];
ll sum[100001];

ll f[100001],x[100001],y[100001];
int minl[100001],maxl[100001];
int Q[100001],head,tail;
inline ll calc(int i,int j){
    return f[j]+(sum[i]-sum[j])*(sum[i]-sum[j]);
}
inline bool cross(int a,int b,int c){
    ll dx1=x[b]-x[a],dy1=y[b]-y[a];
    ll dx2=x[c]-x[b],dy2=y[c]-y[b];
    return dx1*dy2<=dx2*dy1;
}
void dp(ll mid){
    head=tail=1; Q[1]=0;
    for(int i=1;i<=n;i++){
        while(head<tail&&calc(i,Q[head])>calc(i,Q[head+1]))head++;
        int minn=minl[Q[head]],maxn=maxl[Q[head]];
        while(head<tail&&calc(i,Q[head])==calc(i,Q[head+1])){
            head++;
            minn=min(minn,minl[Q[head]]);
            maxn=max(maxn,maxl[Q[head]]);
        }
        f[i]=calc(i,Q[head])+mid;
        x[i]=sum[i],y[i]=f[i]+sum[i]*sum[i];
        minl[i]=minn+1,maxl[i]=maxn+1;
        while(head<tail&&cross(Q[tail-1],Q[tail],i))tail--;
        Q[++tail]=i;
    }
}

int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),sum[i]=sum[i-1]+a[i];
    ll l=0,r=sum[n]*sum[n];
    while(l<=r){
        ll mid=(l+r)/2;
        dp(mid);
        if(minl[n]<=k&&k<=maxl[n]){
            k--;
            vector<int> answer;
            for(int i=n-1,j=n;i>=1;i--){
                if(!(minl[i]<=k&&k<=maxl[i]&&calc(j,i)+mid==f[j]))continue;
                k--,answer.push_back(i),j=i;
            }
            sort(answer.begin(),answer.end());
            puts("Yes");
            for(int i :answer)printf("%d ",i);
            return 0;
        }
        if(minl[n]>k)l=mid+1;
        if(k>maxl[n])r=mid-1;
    }
    puts("No");
    return 0;
}
