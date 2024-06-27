/**
 * @date: 2024.06.08
 * @problem: BZOJ3517
 * @tags: 思维
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[1001][1001];
int s1[1001],s2[1001];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            char ch; scanf(" %c",&ch);
            a[i][j]=ch-'0';
            s1[i]^=a[i][j],s2[j]^=a[i][j];
        }
    int cnt=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cnt+=a[i][j]^s1[i]^s2[j];
    printf("%d\n",min(cnt,n*n-cnt));
    return 0;
}
