/**
 * @date: 2024.04.26
 * @problem: P3100, BZOJ3429
 * @tags: 思维
 */

#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[101][101],f[2][101][101];
bool vis[101][101];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            char c; scanf(" %c",&c);
            a[i][j]=(c=='S')+1;
        }
    int answer=0x7fffffff,cnt=0;
    while(true){
        int x,y,maxlen=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                for(int k=0;k<2;k++){
                    f[k][i][j]=min({f[k][i-1][j],f[k][i][j-1],f[k][i-1][j-1]})+1;
                    if(a[i][j]==k+1)f[k][i][j]=0;
                    if(f[k][i][j]>maxlen&&!vis[i][j])
                        x=i,y=j,maxlen=f[k][i][j];
                }
        vis[x][y]=true,answer=min(answer,maxlen),cnt++;
        for(int i=x-maxlen+1;i<=x;i++)
            for(int j=y-maxlen+1;j<=y;j++)a[i][j]=-1;
        int flag=true;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(a[i][j]!=-1)flag=false;
        if(flag||answer<=1)break;
    }
    printf("%d\n",answer);
    return 0;
}
