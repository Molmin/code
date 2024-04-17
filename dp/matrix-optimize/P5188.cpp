/**
 * @date: 2024.04.05
 * @problem: P5188, LOJ2965
 * @tags: 动态规划, 矩阵, 矩阵乘法, 矩阵快速幂, 组合数学, 组合计数, 容斥原理
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=5557;

int n,m,t;
int s[26][26];

struct Matrix{
    int n,m;
    vector<vector<int> > data;
    inline void init(int _n,int _m){
        n=_n,m=_m;
        data.clear();
        vector<int> vec;
        for(int i=0;i<m;i++)
            vec.push_back(0);
        for(int i=0;i<n;i++)
            data.push_back(vec);
    }
    inline int val(int i,int j){
        return data[i][j];
    }
    inline int set(int i,int j,int val){
        return data[i][j]=val;
    }
    inline int add(int i,int j,int val){
        return data[i][j]=(data[i][j]+val)%mod;
    }
    inline Matrix operator*(Matrix S)const{
        if(m!=S.n)return{0,0,{}};
        Matrix res;
        res.n=n,res.m=S.m;
        for(int i=0;i<res.n;i++){
            vector<int> tmp;
            for(int j=0;j<res.m;j++){
                long long sum=0;
                for(int k=0;k<m;k++)
                    sum+=data[i][k]*S.val(k,j);
                tmp.push_back(sum%mod);
            }
            res.data.push_back(tmp);
        }
        return res;
    }
};

Matrix power(Matrix x,int y){
    if(y==1)return x;
    Matrix tmp=power(x,y>>1);
    tmp=tmp*tmp;
    if(y&1)tmp=tmp*x;
    return tmp;
}

int f[2][26];

inline int solve(int status){
    memset(f,0,sizeof f);
    f[0][1]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(s[i][j])f[1][j]+=f[0][i];
    Matrix A,B,C;
    A.init(1,(n<<1)+1);
    B.init((n<<1)+1,(n<<1)+1);
    for(int i=0;i<2;i++)
        for(int j=0;j<n;j++)
            A.set(0,i*n+j,f[i][j+1]);
    for(int i=0;i<n;i++)
        B.add(i+n,i,1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            if(!s[i][j])continue;
            B.add(i-1+n,j-1+n,1);
            if((status&s[i][j])==s[i][j])B.add(i-1,j-1+n,1);
        }
    B.add(n<<1,n<<1,1);
    B.add(n,n<<1,1);
    C=A*power(B,t);
    return C.val(0,n<<1);
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v; char ch[5]={};
        scanf("%d%d%s",&u,&v,ch);
        for(int j=0,len=strlen(ch);j<len;j++)
            s[u][v]|=1<<(ch[j]=='B'?0:(ch[j]=='J'?1:(ch[j]=='M'?2:3)));
    }
    scanf("%d",&t);
    int answer=0;
    for(int i=0;i<(1<<4);i++)
        answer+=((__builtin_popcount(i)&1)?-1:1)*solve(i);
    printf("%d\n",(answer%mod+mod)%mod);
    return 0;
}
