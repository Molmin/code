/**
 * @date: 2024.03.15
 * @problem: CF1936D
 * @tags: 数据结构, 线段树, 位运算, 贪心
 */

#include<bits/stdc++.h>
using namespace std;
const int INF=2e9;

int n,q,v,a[200001],b[200001];

int maxn[200001][19],lg[200001];
inline int queryMax(int l,int r){
    int k=lg[r-l+1];
    return max(maxn[l][k],maxn[r-(1<<k)+1][k]);
}

struct SegmentTree{
    struct Node{
        int l,r;
        int answer,lpos[30],rpos[30];
        inline void update(int val){
            for(int k=29;k>=0;k--){
                lpos[k]=((val>>k)&1)?l:n+1;
                rpos[k]=((val>>k)&1)?r:0;
            }
            answer=val>=v?a[l]:INF;
        }
    }node[800001];

    inline friend Node operator+(Node lc,Node rc){
        Node result;
        result.l=lc.l,result.r=rc.r;
        result.answer=min(lc.answer,rc.answer);
        for(int i=0;i<30;i++){
            result.lpos[i]=min(lc.lpos[i],rc.lpos[i]);
            result.rpos[i]=max(lc.rpos[i],rc.rpos[i]);
        }
        int l=lc.r,r=rc.l;
        bool flag=true;
        for(int i=29;i>=0;i--){
            if((v>>i)&1){
                if(lc.rpos[i]<result.l&&rc.lpos[i]>result.r){flag=false; break;}
                if(lc.rpos[i]<result.l){r=max(r,rc.lpos[i]);continue;}
                if(rc.lpos[i]>result.r){l=min(l,lc.rpos[i]);continue;}
                int lres=queryMax(l,max(r,rc.lpos[i]));
                int rres=queryMax(min(lc.rpos[i],l),r);
                if(lres==rres)l=min(l,lc.rpos[i]),r=max(r,rc.lpos[i]);
                else if(lres<rres)r=max(r,rc.lpos[i]);
                else l=min(l,lc.rpos[i]);
            }
            else{
                if(lc.rpos[i]>=result.l)result.answer=min(result.answer,queryMax(min(l,lc.rpos[i]),r));
                if(rc.lpos[i]<=result.r)result.answer=min(result.answer,queryMax(l,max(r,rc.lpos[i])));
            }
        }
        if(flag)result.answer=min(result.answer,queryMax(l,r));
        return result;
    }

    inline void pushup(int id){
        node[id]=node[id<<1]+node[id<<1|1];
    }

    void build(int id,int l,int r){
        node[id].l=l,node[id].r=r;
        if(l==r){
            node[id].update(b[l]);
            return;
        }
        int mid=l+r>>1;
        build(id<<1,l,mid);
        build(id<<1|1,mid+1,r);
        pushup(id);
    }

    void updateOne(int id,int pos,int val){
        if(node[id].l==node[id].r){
            node[id].update(val);
            return;
        }
        int mid=node[id].l+node[id].r>>1;
        if(pos<=mid)updateOne(id<<1,pos,val);
        else updateOne(id<<1|1,pos,val);
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

int main(){
    lg[0]=-1;
    for(int i=1;i<=200000;i++)
        lg[i]=lg[i>>1]+1;
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++)
            scanf("%d",a+i),maxn[i][0]=a[i];
        for(int k=1;k<=18;k++)
            for(int i=1;i+(1<<k)-1<=n;i++)
                maxn[i][k]=max(maxn[i][k-1],maxn[i+(1<<k-1)][k-1]);
        for(int i=1;i<=n;i++)
            scanf("%d",b+i);
        _.build(1,1,n);
        scanf("%d",&q);
        while(q--){
            int op,x,y;
            scanf("%d%d%d",&op,&x,&y);
            if(op==1)_.updateOne(1,x,y);
            else{
                int answer=_.query(1,x,y).answer;
                if(answer==INF)answer=-1;
                printf("%d ",answer);
            }
        }
        printf("\n");
    }
    return 0;
}
