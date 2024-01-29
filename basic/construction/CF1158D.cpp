/**
 * @date: 2024.01.29
 * @problem: CF1158D
 * @tags: 构造, 计算几何
 */

#include<bits/stdc++.h>
using namespace std;

int n,ans[2001];
bool vis[2001];
string s;

struct Point{
    int x,y;
    inline void read(){
        scanf("%d%d",&x,&y);
    }
    inline bool isInLeft(Point a){
        // check if vector a is to the left of this vector
        return 1ll*x*a.y-1ll*a.x*y>0;
    }
}a[2001];

inline bool checkLeft(Point x,Point y,Point z){
    // check if z is to the left of (x, y)
    return Point{y.x-x.x,y.y-x.y}.isInLeft({z.x-x.x,z.y-x.y});
}

int main(){
    scanf("%d",&n);
    cin>>s,s=" "+s;
    for(int i=1;i<=n;i++){
        a[i].read();
        if(!ans[1]||a[i].x<a[ans[1]].x)ans[1]=i;
    }
    vis[ans[1]]=true;
    for(int i=2;i<n;i++){
        for(int j=1;j<=n;j++){
            if(!vis[j]&&(!ans[i]||(s[i-1]=='L'&&checkLeft(a[ans[i-1]],a[j],a[ans[i]]))
                ||(s[i-1]=='R'&&checkLeft(a[ans[i-1]],a[ans[i]],a[j]))))ans[i]=j;
        }
        vis[ans[i]]=true;
    }
    for(int i=1;i<=n;i++)
        if(!vis[i])ans[n]=i;
    for(int i=1;i<=n;i++)
        printf("%d%c",ans[i]," \n"[i==n]);
    return 0;
}
