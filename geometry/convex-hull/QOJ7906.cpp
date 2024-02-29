/**
 * @date: 2024.02.25
 * @problem: QOJ7906, GYM104901M
 * @tags: 计算几何, 凸包
 */

#include<bits/stdc++.h>
using namespace std;

int n;
pair<int,int> v[2001];
int s[2001],top;
bool vis[2001];

inline bool check(int x1,int y1,int x2,int y2){
    return 1ll*x2*y1>1ll*x1*y2;
}
inline bool check(int a,int b,int c){
    return check(
        v[b].first-v[a].first,v[b].second-v[a].second,
        v[c].first-v[b].first,v[c].second-v[b].second
    );
}

inline int getType(int x,int y){
    if(x>0&&y>=0)return 1;
    if(x<=0&&y>0)return 2;
    if(x<0&&y<=0)return 3;
    if(x>=0&&y<0)return 4;
}

int p[2001],cntp;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&v[i].first,&v[i].second);
    sort(v+1,v+1+n);
    s[++top]=1;
    for(int i=2;i<=n;i++){
        while(top>=2&&check(s[top-1],s[top],i))
            vis[s[top]]=false,top--;
        s[++top]=i,vis[i]=true;
    }
    int tmp=top;
    for(int i=n-1;i>=1;i--){
        if(vis[i])continue;
        while(tmp<top&&check(s[top-1],s[top],i))
            vis[s[top]]=false,top--;
        s[++top]=i,vis[i]=true;
    };
    top--;
    int answer=1;
    for(int i=1;i<=n;i++){
        if(vis[i])continue;
        cntp=0;
        for(int j=1;j<=n;j++)
            if(i!=j)p[++cntp]=j;
        sort(p+1,p+1+cntp,[&](int x,int y){
            int x1=v[x].first,y1=v[x].second;
            int x2=v[y].first,y2=v[y].second;
            x1-=v[i].first,x2-=v[i].first;
            y1-=v[i].second,y2-=v[i].second;
            if(getType(x1,y1)!=getType(x2,y2))
                return getType(x1,y1)<getType(x2,y2);
            return check(x2,y2,x1,y1);
        });
        if(vis[p[1]]&&vis[p[cntp]])answer++;
        for(int i=1;i<cntp;i++)
            if(vis[p[i]]&&vis[p[i+1]])answer++;
    }
    printf("%d\n",answer);
    return 0;
}
