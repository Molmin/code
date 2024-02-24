/**
 * @date: 2024.02.24
 * @problem: P3380, BZOJ3196, LOJ106
 * @tags: 数据结构, 线段树, 平衡树
 */

#include<bits/stdc++.h>
using namespace std;

mt19937 mt_rand(random_device{}());

struct Node{
    int value,weight;
    int size,lc,rc;
}node[17*100000+1];
int cntNode;

struct Treap{
    int root=0;

    inline void pushup(int id){
        node[id].size=1+node[node[id].lc].size+node[node[id].rc].size;
    }

    inline void leftRotate(int &id){
        int x=node[id].rc;
        node[id].rc=node[x].lc;
        node[x].lc=id;
        node[x].size=node[id].size;
        pushup(id);
        id=x;
    }
    inline void rightRotate(int &id){
        int x=node[id].lc;
        node[id].lc=node[x].rc;
        node[x].rc=id;
        node[x].size=node[id].size;
        pushup(id);
        id=x;
    }

    void insert(int &id,int val){
        if(!id){
            id=++cntNode;
            node[id].size=1;
            node[id].value=val;
            node[id].weight=mt_rand();
            return;
        }
        node[id].size++;
        if(val>=node[id].value)insert(node[id].rc,val);
        else insert(node[id].lc,val);
        if(node[id].rc&&node[id].weight>node[node[id].rc].weight)leftRotate(id);
        if(node[id].lc&&node[id].weight>node[node[id].lc].weight)rightRotate(id);
        pushup(id);
    }
    void remove(int &id,int val){
        node[id].size--;
        if(node[id].value==val){
            if(!node[id].lc||!node[id].rc)
                id=node[id].lc?node[id].lc:node[id].rc;
            else if(node[node[id].lc].weight>=node[node[id].rc].weight){
                leftRotate(id);
                remove(node[id].lc,val);
            }
            else{
                rightRotate(id);
                remove(node[id].rc,val);
            }
            return;
        }
        if(node[id].value>=val)remove(node[id].lc,val);
        else remove(node[id].rc,val);
        pushup(id);
    }

    int calcRank(int id,int val){
        if(!id)return 0;
        if(node[id].value>=val)return calcRank(node[id].lc,val);
        else return node[node[id].lc].size+1+calcRank(node[id].rc,val);
    }
    int getByRank(int id,int rnk){
        if(rnk==node[node[id].lc].size+1)return node[id].value;
        if(rnk>node[node[id].lc].size+1)
            return getByRank(node[id].rc,rnk-node[node[id].lc].size-1);
        else return getByRank(node[id].lc,rnk);
    }

    int getPrevious(int id,int val){
        if(!id)return -2147483647;
        if(node[id].value>=val)
            return getPrevious(node[id].lc,val);
        int ret=getPrevious(node[id].rc,val);
        if(ret==-2147483647)return node[id].value;
        else return ret;
    }
    int getNext(int id,int val){
        if(!id)return 2147483647;
        if(node[id].value<=val)
            return getNext(node[id].rc,val);
        int ret=getNext(node[id].lc,val);
        if(ret==2147483647)return node[id].value;
        else return ret;
    }
};

struct SegmentTree{
    struct SegmentTreeNode{
        int l,r;
        Treap treap;
    }node[200001];

    void build(int id,int l,int r){
        node[id].l=l,node[id].r=r;
        if(l==r)return;
        int mid=l+r>>1;
        build(id<<1,l,mid);
        build(id<<1|1,mid+1,r);
    }

    void updateInsert(int id,int pos,int val){
        node[id].treap.insert(node[id].treap.root,val);
        if(node[id].l==node[id].r)return;
        int mid=node[id].l+node[id].r>>1;
        if(pos<=mid)updateInsert(id<<1,pos,val);
        else updateInsert(id<<1|1,pos,val);
    }
    void updateRemove(int id,int pos,int val){
        node[id].treap.remove(node[id].treap.root,val);
        if(node[id].l==node[id].r)return;
        int mid=node[id].l+node[id].r>>1;
        if(pos<=mid)updateRemove(id<<1,pos,val);
        else updateRemove(id<<1|1,pos,val);
    }

    int queryRank(int id,int l,int r,int val){
        if(l<=node[id].l&&node[id].r<=r)
            return node[id].treap.calcRank(node[id].treap.root,val);
        int mid=node[id].l+node[id].r>>1,ret=0;
        if(l<=mid)ret+=queryRank(id<<1,l,r,val);
        if(mid<r)ret+=queryRank(id<<1|1,l,r,val);
        return ret;
    }

    int queryPrevious(int id,int l,int r,int val){
        if(r<node[id].l||node[id].r<l)
            return -2147483647;
        if(l<=node[id].l&&node[id].r<=r)
            return node[id].treap.getPrevious(node[id].treap.root,val);
        return max(queryPrevious(id<<1,l,r,val),queryPrevious(id<<1|1,l,r,val));
    }
    int queryNext(int id,int l,int r,int val){
        if(r<node[id].l||node[id].r<l)
            return 2147483647;
        if(l<=node[id].l&&node[id].r<=r)
            return node[id].treap.getNext(node[id].treap.root,val);
        return min(queryNext(id<<1,l,r,val),queryNext(id<<1|1,l,r,val));
    }
}_;

int n,m,a[50001];

int main(){
    scanf("%d%d",&n,&m);
    _.build(1,1,n);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
        _.updateInsert(1,i,a[i]);
    }
    while(m--){
        int op,l,r,pos,k;
        scanf("%d",&op);
        if(op==3)scanf("%d%d",&pos,&k);
        else scanf("%d%d%d",&l,&r,&k);
        if(op==1)printf("%d\n",_.queryRank(1,l,r,k)+1);
        if(op==2){
            int L=0,R=1e8;
            while(L<R){
                int mid=L+R+1>>1;
                if(_.queryRank(1,l,r,mid)+1<=k)L=mid;
                else R=mid-1;
            }
            printf("%d\n",L);
        }
        if(op==3){
            _.updateRemove(1,pos,a[pos]);
            a[pos]=k;
            _.updateInsert(1,pos,a[pos]);
        }
        if(op==4)printf("%d\n",_.queryPrevious(1,l,r,k));
        if(op==5)printf("%d\n",_.queryNext(1,l,r,k));
    }
    return 0;
}
