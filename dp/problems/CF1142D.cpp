/**
 * @date: 2024.01.29
 * @problem: CF1142D
 * @tags: 动态规划, 数学
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[100001];
string s;
int dp[100001][11];
// dp[i][j] means the number of numbers that 
//   meet the requirements of the question
//   and ending with label i and ranking module 11 as j.

int main(){
    cin>>s;
    n=s.size();
    for(int i=1;i<=n;i++)a[i]=s[i-1]-'0';
    long long answer=0;
    for(int i=1;i<=n;i++){
        if(a[i])dp[i][a[i]]++;
        for(int j=0;j<=10;j++)answer+=dp[i][j];
        if(i==n)continue;
        for(int j=a[i+1]+1;j<=10;j++)
            dp[i+1][(10+a[i+1]+j*(j-1)/2)%11]+=dp[i][j];
    }
    printf("%lld\n",answer);
    return 0;
}
