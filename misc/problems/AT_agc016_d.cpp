/**
 * @date: 2024.01.23
 * @problem: AT_agc016_d
 * @tags: 思维, 操作问题
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[100002],b[100002],tmpa[100002],tmpb[100002];
int vals[200003],cntval;

int fa[100002],siz[100002];
int find(int id){
    if(fa[id]==id)return id;
    else return fa[id]=find(fa[id]);
}
inline void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx!=fy)fa[fx]=fy,siz[fy]+=siz[fx];
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),a[n+1]^=a[i];
    for(int i=1;i<=n;i++)
        scanf("%d",b+i),b[n+1]^=b[i];
    for(int i=1;i<=n+1;i++)
        vals[++cntval]=a[i],vals[++cntval]=b[i];
    for(int i=1;i<=n+1;i++)
        fa[i]=i,siz[i]=1;
    sort(vals+1,vals+1+cntval);
    cntval=unique(vals+1,vals+1+cntval)-vals-1;
    for(int i=1;i<=n+1;i++){
        tmpa[i]=a[i]=lower_bound(vals+1,vals+1+cntval,a[i])-vals;
        tmpb[i]=b[i]=lower_bound(vals+1,vals+1+cntval,b[i])-vals;
    }
    sort(tmpa+1,tmpa+1+n+1);
    sort(tmpb+1,tmpb+1+n+1);
    for(int i=1;i<=n+1;i++)
        if(tmpa[i]!=tmpb[i])return printf("-1\n"),0;
    int answer=0;
    for(int i=1;i<=n;i++){
        if(a[i]==b[i])continue;
        merge(a[i],b[i]);
        answer++;
    }
    for(int i=1;i<=n+1;i++)
        if(find(i)==i&&siz[i]>1)answer++;
    if(siz[find(a[n+1])]>1)answer--;
    printf("%d\n",answer);
    return 0;
}
