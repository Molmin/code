/**
 * @date: 2024.04.01
 * @problem: P4245
 * @tags: 多项式, 快速数论变换, 中国剩余定理, 模板
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,p,a[2000001],b[2000001];

int power(int x,int y,int mod){
    if(y==0)return 1;
    int tmp=power(x,y>>1,mod);
    tmp=1ll*tmp*tmp%mod;
    if(y&1)tmp=1ll*tmp*x%mod;
    return tmp;
}

inline void NTT(int *a,int len,int k=1,int mod=998244353,int modg=3){
    vector<int> rev;
    for(int i=0;i<len;i++)
        rev.push_back((i?rev[i>>1]:0)>>1|((i&1)?(len>>1):0));
    for(int i=0;i<len;i++)
        if(i<rev[i])swap(a[i],a[rev[i]]);
    for(int h=2;h<=len;h<<=1){
        int w=power(modg,(mod-1)/h,mod);
        if(k==-1)w=power(w,h-1,mod);
        for(int i=0;i<len;i+=h){
            int now=1;
            for(int j=i;j<i+(h>>1);j++,now=1ll*now*w%mod){
                int x=a[j],y=1ll*now*a[j+(h>>1)]%mod;
                a[j]=(x+y)%mod,a[j+(h>>1)]=(x-y+mod)%mod;
            }
        }
    }
    if(k==-1){
        int inv=power(len,mod-2,mod);
        for(int i=0;i<len;i++)a[i]=1ll*a[i]*inv%mod;
    }
}

inline void polyMul(int len,int *a,int *b,int *c,int mod=998244353,int modg=3){
    NTT(a,len,1,mod,modg);
    NTT(b,len,1,mod,modg);
    for(int i=0;i<len;i++)c[i]=1ll*a[i]*b[i]%mod;
    NTT(c,len,-1,mod,modg);
}

int main(){
    scanf("%d%d%d",&n,&m,&p);
    int k=1; while(k<=n+m)k<<=1;
    vector<int> f(k,0),g(k,0),a,b,res[3];
    for(int i=0;i<=n;i++)
        scanf("%d",&f[i]);
    for(int i=0;i<=m;i++)
        scanf("%d",&g[i]);
    int mod[3]={469762049,998244353,1004535809};
    for(int i=0;i<3;i++){
        a=f,b=g,res[i].resize(k);
        polyMul(k,&a[0],&b[0],&res[i][0],mod[i]);
    }
    long long premod=1ll*mod[0]*mod[1];
    int inv1=power(mod[0],mod[1]-2,mod[1]);
    int inv2=power(premod%mod[2],mod[2]-2,mod[2]);
    for(int i=0;i<=n+m;i++){
        int x[3]={res[0][i],res[1][i],res[2][i]};
        long long answer=0;
        answer=(1ll*(x[1]-x[0])%mod[1]+mod[1])%mod[1]*inv1%mod[1]*mod[0]+x[0];
        answer=(1ll*(x[2]-answer)%mod[2]+mod[2])%mod[2]*inv2%mod[2]*(premod%p)+answer;
        printf("%lld%c",(answer%p+p)%p," \n"[i==n+m]);
    }
    return 0;
}
