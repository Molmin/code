/**
 * @date: 2024.02.03
 * @problem: CF498E
 * @tags: 状态压缩动态规划, 矩阵乘法, 矩阵快速幂
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

int n=7,w[8];

struct Matrix{
    int n,m;
    vector<vector<int> > data;
    void init(int a,int b){
        n=a,m=b;
        data.clear();
        for(int i=0;i<n;i++){
            vector<int> tmp;
            for(int j=0;j<m;j++)
                tmp.push_back(0);
            data.push_back(tmp);
        }
    }
    int val(int i,int j){
        return data[i][j];
    }
    int set(int i,int j,int val){
        return data[i][j]=val;
    }
    Matrix operator*(Matrix S)const{
        if(m!=S.n)return{0,0,{}};
        Matrix res;
        res.n=n,res.m=S.m;
        for(int i=0;i<res.n;i++){
            vector<int> tmp;
            for(int j=0;j<res.m;j++){
                long long sum=0;
                for(int k=0;k<m;k++)
                    sum+=1ll*data[i][k]*S.val(k,j)%mod;
                tmp.push_back(sum%mod);
            }
            res.data.push_back(tmp);
        }
        return res;
    }
}A,B;

Matrix powerMatrix(Matrix x,int y){
    if(y==1)return x;
    Matrix tmp=powerMatrix(x,y>>1);
    tmp=tmp*tmp;
    if(y&1)tmp=tmp*x;
    return tmp;
}

int dp[1<<7];

int main(){
    for(int i=1;i<=n;i++)
        scanf("%d",w+i);
    dp[(1<<7)-1]=1;
    for(int i=n;i>=1;i--){
        if(w[i]){
            Matrix A,B;
            A.init(1,1<<i),B.init(1<<i,1<<i);
            for(int status=0;status<(1<<i);status++)
                A.set(0,status,dp[status]);
            for(int a=0;a<(1<<i);a++)
                for(int b=0;b<(1<<i);b++)
                    for(int c=0;c<(1<<i-1);c++){
                        bool flag=true;
                        for(int j=0;j<i;j++){
                            if((a&(1<<j))&&(b&(1<<j)&&(j==0?true:(c&(1<<j-1)))&&(j==i-1?true:(c&(1<<j)))))flag=false;
                        }
                        if(flag)B.set(b,a,B.val(b,a)+1);
                    }
            A=A*powerMatrix(B,w[i]);
            for(int status=0;status<(1<<i);status++)
                dp[status]=A.val(0,status);
        }
        for(int status=0;status<(1<<i-1);status++)
            dp[status]=dp[status|(1<<i-1)];
    }
    printf("%d\n",dp[1]);
    return 0;
}
