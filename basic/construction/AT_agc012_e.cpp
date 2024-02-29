/**
 * @date: 2024.02.15
 * @problem: AT_agc012_e
 * @tags: 动态规划, 状态压缩动态规划
 */

#include<bits/stdc++.h>
using namespace std;

int n,x[200001],cntv,v[19];
int l[19][200001],r[19][200001];
int L[1<<18],R[1<<18];
bool answer[200001];

int main(){
    scanf("%d%d",&n,v);
    for(int i=1;i<=n;i++)scanf("%d",x+i);
    while(v[cntv])v[cntv+1]=v[cntv]/2,cntv++;
    for(int i=0;i<=cntv;i++){
        l[i][1]=1,r[i][n]=n;
        for(int j=2;j<=n;j++)
            if(x[j]-x[j-1]<=v[i])l[i][j]=l[i][j-1];
            else l[i][j]=j;
        for(int j=n-1;j>=1;j--)
            if(x[j+1]-x[j]<=v[i])r[i][j]=r[i][j+1];
            else r[i][j]=j;
    }
    {
        int total=0,x=1;
        while(x<=n)x=r[0][x]+1,total++;
        if(total>cntv+1){
            for(int i=1;i<=n;i++)puts("Impossible");
            return 0;
        }
    }
    for(int status=0;status<(1<<cntv);status++){
        L[status]=n+1,R[status]=0;
        for(int i=1;i<=cntv;i++)
            if(status&(1<<i-1)){
                L[status]=min(L[status],l[i][L[status^(1<<i-1)]-1]);
                R[status]=max(R[status],r[i][R[status^(1<<i-1)]+1]);
            }
    }
    for(int x=1,y;x<=n;x=y+1){
        y=r[0][x];
        for(int s=0;s<(1<<cntv);s++){
            int t=((1<<cntv)-1)^s;
            if(R[s]>=x-1&&L[t]<=y+1)answer[x]=true;
        }
    }
    for(int i=1;i<=n;i++)
        if(answer[l[0][i]])puts("Possible");
        else puts("Impossible");
    return 0;
}
