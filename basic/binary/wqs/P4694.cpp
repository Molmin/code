/**
 * @date: 2024.01.29
 * @problem: P4694
 * @tags: WQS 二分, 贪心, 反悔贪心
 */

#include<bits/stdc++.h>
using namespace std;

int n,k,a[500001],b[500001];

pair<long long,int> calc(int mid){
    priority_queue<pair<long long,bool> > Q;
    long long answer=0;
    int total=0;
    for(int i=1;i<=n;i++){
        Q.push({-a[i],true});
        auto data=Q.top();
        if(b[i]-data.first-mid<0){
            answer+=b[i]-data.first-mid;
            if(data.second)total++;
            Q.pop();
            Q.push({b[i]-mid,false});
        }
    }
    return{answer,total};
}

int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    for(int i=1;i<=n;i++)
        scanf("%d",b+i);
    int l=0,r=2e9;
    while(l<r){
        int mid=(1ll*l+r+1)>>1;
        auto result=calc(mid);
        if(result.second<=k)l=mid;
        else r=mid-1;
    }
    printf("%lld\n",calc(l).first+1ll*l*k);
    return 0;
}
