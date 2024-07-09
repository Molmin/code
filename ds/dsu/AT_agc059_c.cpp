/**
 * @date: 2024.07.04
 * @problem: AT_agc059_c
 * @tags: 数据结构, 并查集, 组合数学, 组合计数
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

int n,m,pos[401][401];
int id(int x,int y){
    return (x-1)*n+y;
}

int fa[160001];
int find(int x){
    if(fa[x]==x)return x;
    else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx!=fy)fa[fx]=fy;
}

int main(){
    scanf("%d",&n);
    m=n*(n-1)/2;
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        pos[x][y]=pos[y][x]=i;
        fa[id(x,y)]=id(x,y),fa[id(y,x)]=id(y,x);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++){
                if(i==j||j==k||k==i)continue;
                if(pos[i][j]>max(pos[i][k],pos[k][j])){
                    merge(id(i,k),id(j,k));
                    merge(id(k,i),id(k,j));
                }
            }
    int answer=1;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            if(find(id(i,j))==find(id(j,i)))
                return puts("0"),0;
            if(find(id(i,j))==id(i,j))answer=answer*2ll%mod;
        }
    printf("%d\n",answer);
    return 0;
}
