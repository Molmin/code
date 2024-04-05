/**
 * @date: 2024.03.24
 * @problem: P10085, QOJ8018
 * @tags: 构造, 倍增, bitset
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[2][1<<11][1<<11];

int main(){
    scanf("%d",&n);
    for(int i=0;i<(1<<n);i++)
        for(int j=0;j<(1<<n);j++)
            scanf("%d",&a[0][i][j]);
    int mask=(1<<n)-1;
    for(int k=n-2;k>=0;k--){
        for(int i=0;i<(1<<n);i++)
            for(int j=0;j<(1<<n);j++)
                a[1][i][j]=a[0][i][j],a[0][i][j]=0;
        for(int i=0;i<(1<<n);i++)
            for(int j=0;j<(1<<n);j++){
                a[0][i][j]^=a[1][i][j];
                a[0][(i-(1<<k)+(1<<n))&mask][j]^=a[1][i][j];
                a[0][(i+(1<<k))&mask][j]^=a[1][i][j];
                a[0][i][(j-(1<<k)+(1<<n))&mask]^=a[1][i][j];
                a[0][i][(j+(1<<k))&mask]^=a[1][i][j];
            }
    }
    int cnt=0;
    for(int i=0;i<(1<<n);i++)
        for(int j=0;j<(1<<n);j++)
            cnt+=a[0][i][j];
    printf("%d\n",cnt);
    for(int i=0;i<(1<<n);i++)
        for(int j=0;j<(1<<n);j++)
            if(a[0][i][j])printf("%d %d\n",i,j);
    return 0;
}
