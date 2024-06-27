/**
 * @date: 2024.06.10
 * @problem: CF1379E
 * @tags: 构造, 图论
 */

#include<bits/stdc++.h>
using namespace std;

int n,k,answer[100001];

int main(){
    scanf("%d%d",&n,&k);
    int maxk=max((n-3)/2,0);
    if(n%2==0||k>maxk)return puts("NO"),0;
    if(n==9&&k==2)return puts("NO"),0;
    if(__builtin_popcount(n+1)==1&&k==1)return puts("NO"),0;
    if(__builtin_popcount(n+1)>1&&k==0)return puts("NO"),0;
    puts("YES");
    int t=max(0,k-1)<<1;
    for(int i=1;i<t;i+=2)
        answer[i]=max(0,i-2),answer[i+1]=i;
    answer[t+1]=max(0,t-1);
    for(int i=t+2;i<=n;i++)
        answer[i]=(i-t>>1)+t;
    if(__builtin_popcount(n-t+1)==1&&k!=0)answer[n-1]=answer[n]=2;
    for(int i=1;i<=n;i++)
        printf("%d%c",answer[i]," \n"[i==n]);
    return 0;
}
