/**
 * @date: 2024.02.01
 * @problem: BZOJ2989, BZOJ4170
 * @tags: CDQ 分治
 */

#include<bits/stdc++.h>
using namespace std;

int n,q,a[60001];

struct Node{
    int x,y,z,qid,mul;
    inline bool operator<(Node tmp)const{
        if(x!=tmp.x)return x<tmp.x;
        if(y!=tmp.y)return y<tmp.y;
        return z<tmp.z;
    }
}nodes[350001];
int cntNode;

int ans[60001],cntQuery;

struct BIT{
    int v[60002];
    inline void add(int x,int y){
        for(;x<=q+1;x+=x&-x)v[x]+=y;
    }
    inline int query(int x){
        int ret=0;
        for(;x>=1;x-=x&-x)ret+=v[x];
        return ret;
    }
}_;

int ids[350001],cntids;

void cdq(int l,int r){
    if(l==r)return;
    int mid=l+r>>1;
    cntids=0;
    for(int i=l;i<=r;i++)
        ids[++cntids]=i;
    sort(ids+1,ids+1+cntids,[&](int x,int y){
        if(nodes[x].y!=nodes[y].y)return nodes[x].y<nodes[y].y;
        else return nodes[x].z<nodes[y].z;
    });
    for(int i=1;i<=cntids;i++){
        if(ids[i]<=mid&&!nodes[ids[i]].qid)
            _.add(nodes[ids[i]].z,1);
        else if(mid<ids[i]&&nodes[ids[i]].qid)
            ans[nodes[ids[i]].qid]+=nodes[ids[i]].mul*_.query(nodes[ids[i]].z);
    }
    for(int i=l;i<=r;i++)
        if(i<=mid&&!nodes[i].qid)
            _.add(nodes[i].z,-1);
    cdq(l,mid); cdq(mid+1,r);
}

int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
        nodes[++cntNode]={i-a[i],i+a[i],1,0,0};
    }
    for(int i=1;i<=q;i++){
        string op; int x,k;
        cin>>op;
        scanf("%d%d",&x,&k);
        if(op=="Modify"){
            a[x]=k;
            nodes[++cntNode]={x-k,x+k,i+1,0,0};
        }
        else{
            cntQuery++;
            nodes[++cntNode]={x-a[x]+k,x+a[x]+k,i+1,cntQuery,1};
            nodes[++cntNode]={x-a[x]-k-1,x+a[x]+k,i+1,cntQuery,-1};
            nodes[++cntNode]={x-a[x]+k,x+a[x]-k-1,i+1,cntQuery,-1};
            nodes[++cntNode]={x-a[x]-k-1,x+a[x]-k-1,i+1,cntQuery,1};
        }
    }
    sort(nodes+1,nodes+1+cntNode);
    cdq(1,cntNode);
    for(int i=1;i<=cntQuery;i++)
        printf("%d\n",ans[i]);
    return 0;
}
