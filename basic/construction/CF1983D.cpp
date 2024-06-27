/**
 * @date: 2024.06.10
 * @problem: CF1983D
 * @tags: 构造
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,a[251][251],r[251],c[251];
bool visr[250*250+1],visc[250*250+1];
queue<pair<int,int>> Q;

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
            r[i]=max(r[i],a[i][j]);
            c[j]=max(c[j],a[i][j]);
        }
    for(int i=1;i<=n;i++)visr[r[i]]=true;
    for(int j=1;j<=m;j++)visc[c[j]]=true;
    int x=0,y=0;
    for(int i=n*m;i>=1;i--){
        if(visr[i])x++;
        if(visc[i])y++;
        if(visr[i]||visc[i])a[x][y]=i;
        else a[Q.front().first][Q.front().second]=i,Q.pop();
        if(visr[i])for(int j=y-1;j;j--)Q.emplace(x,j);
        if(visc[i])for(int j=x-1;j;j--)Q.emplace(j,y);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            printf("%d%c",a[i][j]," \n"[j==m]);
    return 0;
}
