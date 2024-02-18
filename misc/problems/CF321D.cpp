/**
 * @date: 2024.02.17
 * @problem: CF321D
 * @tags: 思维, 数学, 组合数学
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,a[34][34];
bool b[34][34];
int get(int x,int y){
    return b[x][y]?-a[x][y]:a[x][y];
}

int solve(int x,int y,int v){
    b[x][y]=v,b[x+m][y]=b[x][y]^b[m][y];
    b[x][y+m]=b[x][y]^b[x][m],b[x+m][y+m]=b[x][y+m]^b[m][y+m];
    return get(x,y)+get(x+m,y)+get(x,y+m)+get(x+m,y+m);
}

int solveColumn(int x,int v){
    b[m][x]=v,b[m][x+m]=b[m][m]^b[m][x];
    int sum=get(m,x)+get(m,x+m);
    for(int i=1;i<m;i++)
        sum+=max(solve(i,x,0),solve(i,x,1));
    return sum;
}

int main(){
    scanf("%d",&n),m=n+1>>1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
    int answer=-3e6;
    for(int status=0;status<(1<<m);status++){
        for(int i=1;i<=m;i++)b[i][m]=status&(1<<i-1);
        for(int i=1;i<m;i++)b[i+m][m]=b[m][m]^b[i][m];
        int sum=0;
        for(int i=1;i<=n;i++)sum+=get(i,m);
        for(int i=1;i<m;i++)
            sum+=max(solveColumn(i,0),solveColumn(i,1));
        answer=max(answer,sum);
    }
    printf("%d\n",answer);
    return 0;
}
