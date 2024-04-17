/**
 * @date: 2024.04.07
 * @problem: UOJ176
 * @tags: 图论, 最小生成树, 位运算, 数据结构, 并查集, 贪心
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,a[100001];
bool vis[1<<18];
int fa[1<<18];
int find(int x){
    if(fa[x]==x)return x;
    else return fa[x]=find(fa[x]);
}

int main(){
    long long answer=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),answer+=vis[a[i]]*a[i],vis[a[i]]=true;
    for(int i=0;i<(1<<m);i++)fa[i]=i;
    for(int i=(1<<m)-1;i;i--){
        if(!vis[i]){
            int j=0; while(j<m&&!vis[i|(1<<j)])j++;
            if(j<m)fa[i]=fa[i|(1<<j)],vis[i]=true;
            else continue;
        }
        for(int j=0;j<m;j++)
            if(vis[i|(1<<j)]){
                int fx=find(i),fy=find(i|(1<<j));
                if(fx==fy)continue;
                fa[fy]=fx;
                answer+=i;
            }
    }
    printf("%lld\n",answer);
    return 0;
}
