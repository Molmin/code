/**
 * @date: 2024.07.04
 * @problem: P5278
 * @tags: 数据结构, 线段树, set
 */

#include<bits/stdc++.h>
using namespace std;

int n,q,a[300001],pre[300001];
map<int,int> mp; int cntval;
set<int> S[600001];

struct SegmentTree{
    struct Node{
        int l,r;
        int minn,maxn,maxpre,gcd;
        friend Node operator+(const Node L,const Node R){
            return{
                L.l,R.r,
                min(L.minn,R.minn),max(L.maxn,R.maxn),
                max(L.maxpre,R.maxpre),__gcd(L.gcd,R.gcd)
            };
        }
    }node[1200001];
    
    void pushup(int id){
        node[id]=node[id<<1]+node[id<<1|1];
    }

    void build(int id,int l,int r){
        node[id].l=l,node[id].r=r;
        if(l==r)return;
        int mid=l+r>>1;
        build(id<<1,l,mid);
        build(id<<1|1,mid+1,r);
    }

    void updateOne(int id,int pos,int val){
        if(node[id].l==node[id].r){
            node[id].minn=val,node[id].maxn=val;
            return;
        }
        int mid=node[id].l+node[id].r>>1;
        if(pos<=mid)updateOne(id<<1,pos,val);
        else updateOne(id<<1|1,pos,val);
        pushup(id);
    }
    void updateDiff(int id,int pos,int val){
        if(node[id].l==node[id].r){
            node[id].gcd=val;
            return;
        }
        int mid=node[id].l+node[id].r>>1;
        if(pos<=mid)updateDiff(id<<1,pos,val);
        else updateDiff(id<<1|1,pos,val);
        pushup(id);
    }
    void updatePrev(int id,int pos,int val){
        if(node[id].l==node[id].r){
            node[id].maxpre=val;
            return;
        }
        int mid=node[id].l+node[id].r>>1;
        if(pos<=mid)updatePrev(id<<1,pos,val);
        else updatePrev(id<<1|1,pos,val);
        pushup(id);
    }

    Node query(int id,int l,int r){
        if(l<=node[id].l&&node[id].r<=r)
            return node[id];
        int mid=node[id].l+node[id].r>>1;
        if(r<=mid)return query(id<<1,l,r);
        if(mid<l)return query(id<<1|1,l,r);
        return query(id<<1,l,r)+query(id<<1|1,l,r);
    }
}_;

void recalcPrev(int x){
    auto it=S[mp[a[x]]].lower_bound(x);
    pre[x]=it==S[mp[a[x]]].begin()?0:*--it;
    _.updatePrev(1,x,pre[x]);
}

int main(){
    scanf("%d%d",&n,&q);
    _.build(1,1,n);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
        if(!mp[a[i]])mp[a[i]]=++cntval;
        _.updateOne(1,i,a[i]);
        _.updateDiff(1,i,abs(a[i]-a[i-1]));
        S[mp[a[i]]].insert(i);
    }
    for(int i=1;i<=n;i++)recalcPrev(i);
    int cntYes=0;
    while(q--){
        int op;
        scanf("%d",&op);
        if(op==1){
            int x,y;
            scanf("%d%d",&x,&y);
            x^=cntYes,y^=cntYes;
            if(!mp[y])mp[y]=++cntval;
            S[mp[a[x]]].erase(x);
            auto it=S[mp[a[x]]].upper_bound(x);
            if(it!=S[mp[a[x]]].end())recalcPrev(*it);
            a[x]=y;
            S[mp[a[x]]].insert(x);
            it=S[mp[a[x]]].upper_bound(x);
            if(it!=S[mp[a[x]]].end())recalcPrev(*it);
            recalcPrev(x);
            _.updateOne(1,x,a[x]);
            _.updateDiff(1,x+1,abs(a[x+1]-a[x]));
            _.updateDiff(1,x,abs(a[x]-a[x-1]));
        }
        else{
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            l^=cntYes,r^=cntYes,k^=cntYes;
            SegmentTree::Node node=_.query(1,l,r);
            if(k==0||l==r){
                if(node.minn==node.maxn)puts("Yes"),cntYes++;
                else puts("No");
                continue;
            }
            bool flag=true;
            if(node.minn+1ll*(r-l)*k!=node.maxn)flag=false;
            if(node.maxpre>=l)flag=false;
            if(_.query(1,l+1,r).gcd!=k)flag=false;
            if(flag)puts("Yes"),cntYes++;
            else puts("No");
        }
    }
    return 0;
}
