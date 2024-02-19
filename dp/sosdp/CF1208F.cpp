/**
 * @date: 2024.02.19
 * @problem: CF1208F
 * @tags: 动态规划, 高维前缀和, 位运算
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[1000001],minid[1<<21];
pair<int,int> f[1<<21];

inline pair<int,int> merge(pair<int,int> x,pair<int,int> y){
    int a[4]={x.first,x.second,y.first,y.second};
    sort(a,a+4);
    return {a[3],a[2]};
}

int main(){
    memset(minid,0x7f,sizeof minid);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i),f[a[i]]=merge(f[a[i]],{i,0});
        minid[a[i]]=min(minid[a[i]],i);
    }
    for(int k=0;k<=20;k++)
        for(int i=(1<<21)-1;i>=0;i--)
            if(!(i&(1<<k))){
                f[i]=merge(f[i],f[i|(1<<k)]);
                minid[i]=min(minid[i],minid[i|(1<<k)]);
            }
    int answer=0;
    for(int k=20;k>=0;k--){
        int target=answer|(1<<k);
        bool flag=minid[target]<f[0].second;
        for(int i=target;i;i=(i-1)&target)
            if(minid[target^i]<f[i].second)flag=true;
        if(flag)answer|=1<<k;
    }
    printf("%d\n",answer);
    return 0;
}
