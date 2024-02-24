/**
 * @date: 2024.02.24
 * @problem: P3369, BZOJ3224, LOJ104
 * @tags: 模板, 数据结构, 平衡树
 */

#include<bits/stdc++.h>
using namespace std;

mt19937 mt_rand(random_device{}());

struct Treap{
    struct Node{
        int value,weight;
        int size,lc,rc;
    }node[100001];
    int cntNode;

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
        if(!id)return 0;
        if(node[id].value>=val)
            return getPrevious(node[id].lc,val);
        int ret=getPrevious(node[id].rc,val);
        if(!ret)return node[id].value;
        else return ret;
    }
    int getNext(int id,int val){
        if(!id)return 0;
        if(node[id].value<=val)
            return getNext(node[id].rc,val);
        int ret=getNext(node[id].lc,val);
        if(!ret)return node[id].value;
        else return ret;
    }
}_;

int main(){
    int q,root=0;
    scanf("%d",&q);
    while(q--){
        int op,x;
        scanf("%d%d",&op,&x);
        if(op==1)_.insert(root,x);
        if(op==2)_.remove(root,x);
        if(op==3)printf("%d\n",_.calcRank(root,x)+1);
        if(op==4)printf("%d\n",_.getByRank(root,x));
        if(op==5)printf("%d\n",_.getPrevious(root,x));
        if(op==6)printf("%d\n",_.getNext(root,x));
    }
    return 0;
}
