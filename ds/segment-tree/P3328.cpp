/**
 * @date: 2024.07.04
 * @problem: P3328
 * @tags: 数据结构, 线段树, 矩阵, 矩阵乘法, 矩阵快速幂
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

int n,q,A,B,a[300001];

struct Matrix{
    int a[3][3];
    friend Matrix operator+(const Matrix x,const Matrix y){
        Matrix ret;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                ret.a[i][j]=(x.a[i][j]+y.a[i][j])%mod;
        return ret;
    }
    friend Matrix operator*(const Matrix x,const Matrix y){
        Matrix ret;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++){
                ret.a[i][j]=0;
                for(int k=0;k<3;k++)
                    ret.a[i][j]=(ret.a[i][j]+1ll*x.a[i][k]*y.a[k][j])%mod;
            }
        return ret;
    }
    Matrix reverse(){
        Matrix ret;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                ret.a[i][j]=a[j][i];
        return ret;
    }
}I,BASE,BASE_T,PLUS,PLUS_T,MINUS,MINUS_T;

Matrix power(Matrix x,int y){
    if(y==0)return I;
    Matrix tmp=power(x,y>>1);
    tmp=tmp*tmp;
    if(y&1)tmp=tmp*x;
    return tmp;
}

int power(int x,int y=mod-2){
    if(y==0)return 1;
    int tmp=power(x,y>>1);
    tmp=1ll*tmp*tmp%mod;
    if(y&1)tmp=1ll*tmp*x%mod;
    return tmp;
}

struct SegmentTree{
    struct Node{
        int l,r;
        Matrix val,tag_left,tag_right;
        void update(Matrix left,Matrix right){
            tag_left=left*tag_left;
            tag_right=tag_right*right;
            val=left*val*right;
        }
    }node[1200001];

    void pushup(int id){
        node[id].val=node[id<<1].val+node[id<<1|1].val;
    }
    void pushdown(int id){
        node[id<<1].update(node[id].tag_left,node[id].tag_right);
        node[id<<1|1].update(node[id].tag_left,node[id].tag_right);
        node[id].tag_left=I,node[id].tag_right=I;
    }

    void build(int id,int l,int r){
        node[id].l=l,node[id].r=r;
        node[id].tag_left=I,node[id].tag_right=I;
        if(l==r){
            node[id].val=(power(PLUS,a[l-1]+1-2)*BASE)*(BASE_T*power(PLUS_T,a[l+1]-1-2));
            return;
        }
        int mid=l+r>>1;
        build(id<<1,l,mid);
        build(id<<1|1,mid+1,r);
        pushup(id);
    }

    void update(int id,int l,int r,Matrix left,Matrix right){
        if(l<=node[id].l&&node[id].r<=r)
            return node[id].update(left,right);
        int mid=node[id].l+node[id].r>>1;
        pushdown(id);
        if(l<=mid)update(id<<1,l,r,left,right);
        if(mid<r)update(id<<1|1,l,r,left,right);
        pushup(id);
    }

    Matrix query(int id,int l,int r){
        if(l<=node[id].l&&node[id].r<=r)
            return node[id].val;
        int mid=node[id].l+node[id].r>>1;
        pushdown(id);
        if(r<=mid)return query(id<<1,l,r);
        if(mid<l)return query(id<<1|1,l,r);
        return query(id<<1,l,r)+query(id<<1|1,l,r);
    }
}_;

int main(){
    scanf("%d%d%d%d",&n,&q,&A,&B);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    I.a[0][0]=I.a[1][1]=I.a[2][2]=1;
    BASE.a[0][0]=2,BASE.a[1][0]=BASE.a[2][0]=1;
    PLUS.a[0][0]=PLUS.a[1][0]=PLUS.a[2][2]=1,PLUS.a[0][1]=A,PLUS.a[0][2]=B;
    MINUS.a[0][1]=MINUS.a[2][2]=1,MINUS.a[1][0]=power(A);
    MINUS.a[1][1]=(mod-power(A))%mod,MINUS.a[1][2]=(mod-1ll*B*power(A)%mod)%mod;
    if(A==0)MINUS.a[1][1]=1,MINUS.a[1][2]=(mod-B)%mod;
    BASE_T=BASE.reverse();
    PLUS_T=PLUS.reverse();
    MINUS_T=MINUS.reverse();
    _.build(1,2,n-1);
    while(q--){
        char s[10];
        int l,r;
        scanf("%s%d%d",s,&l,&r);
        if(s[0]=='q')printf("%d\n",l+1<=r-1?_.query(1,l+1,r-1).a[0][0]:0);
        else{
            if(l+1<=min(r+1,n-1))_.update(1,l+1,min(r+1,n-1),s[0]=='p'?PLUS:MINUS,I);
            if(max(l-1,2)<=r-1)_.update(1,max(l-1,2),r-1,I,s[0]=='p'?PLUS_T:MINUS_T);
        }
    }
    return 0;
}
