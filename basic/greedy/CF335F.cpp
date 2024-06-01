/**
 * @date: 2024.05.31
 * @problem: CF335F
 * @tags: 贪心, 反悔贪心, 数据结构, 优先队列
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[500001];
int c[500001],t[500001],cnt;
priority_queue<int> Q;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    sort(a+1,a+1+n);
    for(int i=n;i>=1;i--){
        if(i==n||a[i]!=a[i+1])c[++cnt]=a[i];
        t[cnt]++;
    }
    int sum=0;
    long long answer=0;
    for(int i=1;i<=cnt;i++){
        answer+=1ll*c[i]*t[i];
        int shouldBuy=t[i]-max(min(sum-2*(int)Q.size(),t[i]),0);
        queue<int> handlePush;
        for(int j=1;j<=shouldBuy;j+=2){
            if(Q.empty())break;
            int x=-Q.top(); Q.pop();
            if(c[i]<=x){
                handlePush.push(x);
                if(c[i]*2>=x&&j+1<=shouldBuy)handlePush.push(c[i]*2-x);
            }
            else{
                for(int k=j;k<=j+1&&k<=shouldBuy;k++)
                    handlePush.push(c[i]);
            }
        }
        while(!handlePush.empty())Q.push(-handlePush.front()),handlePush.pop();
        for(int j=1;j+shouldBuy<=t[i];j++)
            Q.push(-c[i]);
        sum+=t[i];
    }
    while(!Q.empty())answer+=Q.top(),Q.pop();
    printf("%lld\n",answer);
    return 0;
}
