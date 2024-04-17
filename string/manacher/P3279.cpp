/**
 * @date: 2024.04.07
 * @problem: P3279, BZOJ3325
 * @tags: 字符串, manacher, 数据结构, 并查集, 贪心
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[200002],f[200002];
vector<int> diff[100001];
char ch[100001]; bool vis[200];

int fa[100001];
int find(int id){
    if(fa[id]==id)return id;
    else return fa[id]=find(fa[id]);
}
inline void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx!=fy)fa[fx]=fy;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i*2),fa[i]=i;
    for(int i=1;i<n;i++)
        scanf("%d",a+i*2+1);
    int pos=1,maxr=1; f[1]=1;
    for(int i=2;i<=2*n+1;i++){
        if(i<=maxr)f[i]=min(f[pos*2-i],maxr-i+1);
        else f[i]=1;
        while(f[i]<=a[i]){
            if(!((i-f[i])&1))merge((i-f[i])>>1,(i+f[i])>>1);
            f[i]++;
        }
        if(1<=i-f[i]&&i+f[i]<=2*n+1){
            int u=(i-f[i]+1)>>1,v=(i+f[i]+1)>>1;
            diff[u].push_back(v);
            diff[v].push_back(u);
        }
        if(i+f[i]-1>maxr)maxr=i+f[i]-1,pos=i;
    }
    for(int i=1;i<=n;i++){
        if(ch[find(i)])continue;
        memset(vis,false,sizeof vis);
        for(int j :diff[i])vis[ch[find(j)]]=true;
        char c='a'; while(vis[c])c++;
        ch[find(i)]=c;
    }
    for(int i=1;i<=n;i++)
        printf("%c",ch[find(i)]);
    printf("\n");
    return 0;
}
