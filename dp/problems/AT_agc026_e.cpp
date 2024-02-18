/**
 * @date: 2024.02.18
 * @problem: AT_agc026_e
 * @tags: 字符串, 动态规划
 */

#include<bits/stdc++.h>
using namespace std;

int n,posa[3002],posb[3002],rnk[6001];
string s,dp[3002];

int main(){
    scanf("%d",&n),cin>>s,s=" "+s;
    int a=0,b=0;
    for(int i=1;i<=(n<<1);i++)
        if(s[i]=='a')rnk[i]=++a,posa[a]=i;
        else rnk[i]=++b,posb[b]=i;
    dp[n+1]="";
    rnk[2*n+1]=n+1,posa[n+1]=posb[n+1]=2*n+1;
    for(int i=n;i>=1;i--){
        if(posa[i]<posb[i]){
            int x=posb[i]; while(s[x]=='b')x++;
            dp[i]="ab"+dp[rnk[x]];
        }
        else{
            int l=posb[i]+1,r=posa[i];
            dp[i]="b";
            while(l<=r){
                if(s[l]=='b')r=max(r,posa[rnk[l]]);
                if(s[l]!='a'||posb[rnk[l]]>=posb[i])dp[i]+=s[l];
                l++;
            }
            dp[i]+=dp[rnk[r+1]];
        }
        if(dp[i+1]>dp[i])dp[i]=dp[i+1];
    }
    cout<<dp[1]<<endl;
    return 0;
}
