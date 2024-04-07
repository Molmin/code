/**
 * @date: 2024.04.07
 * @problem: CF888G
 * @tags: 数据结构, Trie, 贪心, 图论, 最小生成树
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[200001];

int root,cntNode,ch[200000*30+1][2],l[200000*30+1],r[200000*30+1];

void insert(int &id,int pos,int val,int k){
    if(!id)id=++cntNode;
    if(!l[id])l[id]=r[id]=pos;
    else l[id]=min(l[id],pos),r[id]=max(r[id],pos);
    if(k>=0)insert(ch[id][(val>>k)&1],pos,val,k-1);
}

int query(int id,int val,int k){
    if(k<0)return 0;
    if(ch[id][(val>>k)&1])return query(ch[id][(val>>k)&1],val,k-1);
    else return query(ch[id][!((val>>k)&1)],val,k-1)+(1<<k);
}

long long solve(int id,int k){
    if(!id||k<0||(!ch[id][0]&&!ch[id][1]))return 0;
    if(!ch[id][0])return solve(ch[id][1],k-1);
    if(!ch[id][1])return solve(ch[id][0],k-1);
    int minn=1<<30;
    for(int i=l[ch[id][0]];i<=r[ch[id][0]];i++)
        minn=min(minn,query(ch[id][1],a[i],k-1));
    return (minn|(1<<k))+solve(ch[id][0],k-1)+solve(ch[id][1],k-1);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
        insert(root,i,a[i],29);
    printf("%lld\n",solve(root,29));
    return 0;
}
