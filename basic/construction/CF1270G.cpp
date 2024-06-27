/**
 * @date: 2024.06.09
 * @problem: CF1270G
 * @tags: 构造, 图论
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[1000001];
bool vis[1000001];

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",a+i),a[i]=i-a[i],vis[i]=false;
        int u=1;
        while(!vis[u])vis[u]=true,u=a[u];
        vector<int> vec;
        vec.push_back(u),u=a[u];
        while(u!=vec[0])vec.push_back(u),u=a[u];
        printf("%d\n",(int)vec.size());
        for(int i :vec)printf("%d ",i);
        printf("\n");
    }
    return 0;
}
