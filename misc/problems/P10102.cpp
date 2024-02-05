/**
 * @date: 2023.03.18
 * @problem: P10102, LOJ4067
 * @tags: 随机化, 矩阵乘法
 */

#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;

struct Matrix{
    int n,m;
    vector<vector<int> > data;
    int val(int i,int j){
        return data[i][j];
    }
    int set(int i,int j,int val){
        return data[i][j]=val;
    }
    void init(int n1,int m1){
        n=n1,m=m1;
        vector<int> tmp;
        tmp.clear();
        for(int i=1;i<=m;i++)
            tmp.push_back(0);
        data.clear();
        for(int i=1;i<=n;i++)
            data.push_back(tmp);
    }
    void read(int a,int b){
        n=a,m=b;
        data.clear();
        for(int i=0;i<n;i++){
            vector<int> tmp;
            for(int j=0;j<m;j++){
                int x;
                scanf("%d",&x);
                tmp.push_back(x);
            }
            data.push_back(tmp);
        }
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
                    sum+=1ll*data[i][k]*S.val(k,j),sum%=mod;
                tmp.push_back(sum);
            }
            res.data.push_back(tmp);
        }
        return res;
    }
    bool operator==(Matrix S)const{
        if(n!=S.n||m!=S.m)return false;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(S.val(i,j)!=data[i][j])return false;
        return true;
    }
}A,B,C,M;

int main(){
    srand(time(0));
    int T; scanf("%d",&T);
    while(T--){
        int n; scanf("%d",&n);
        A.read(n,n); B.read(n,n); C.read(n,n);
        M.init(1,n);
        for(int i=0;i<n;i++)
            M.set(0,i,rand()%(mod-1)+1);
        if(M*A*B==M*C)printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
