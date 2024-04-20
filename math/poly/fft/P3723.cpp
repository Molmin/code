/**
 * @date: 2024.04.20
 * @problem: P3723, LOJ2020, BZOJ4827
 * @tags: 多项式, 快速傅里叶变换, 快速数论变换, 贪心
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,modg=3;

int n;

int power(int x,int y=mod-2){
    if(y==0)return 1;
    int tmp=power(x,y>>1);
    tmp=1ll*tmp*tmp%mod;
    if(y&1)tmp=1ll*tmp*x%mod;
    return tmp;
}

inline void NTT(int *a,int len,int k=1){
    vector<int> rev;
    for(int i=0;i<len;i++)
        rev.push_back((i?rev[i>>1]:0)>>1|((i&1)?(len>>1):0));
    for(int i=0;i<len;i++)
        if(i<rev[i])swap(a[i],a[rev[i]]);
    for(int h=2;h<=len;h<<=1){
        int w=power(modg,(mod-1)/h);
        if(k==-1)w=power(w,h-1);
        for(int i=0;i<len;i+=h){
            int now=1;
            for(int j=i;j<i+(h>>1);j++,now=1ll*now*w%mod){
                int x=a[j],y=1ll*now*a[j+(h>>1)]%mod;
                a[j]=(x+y)%mod,a[j+(h>>1)]=(x-y+mod)%mod;
            }
        }
    }
    if(k==-1)for(int i=0,inv=power(len);i<len;i++)a[i]=1ll*a[i]*inv%mod;
}

int main(){
    long long answer=0,sum=0;
    scanf("%d%*d",&n);
    int k=1; while(k<=3*n)k<<=1;
    vector<int> f(k,0),g(k,0);
    for(int i=0;i<n;i++){
        scanf("%d",&f[i]),f[i+n]=f[i];
        answer+=f[i]*f[i],sum+=2*f[i];
    }
    for(int i=0;i<n;i++){
        int v; scanf("%d",&v),g[n-i-1]=v;
        answer+=v*v,sum-=2*v;
    }
    NTT(&f[0],k,1);
    NTT(&g[0],k,1);
    for(int i=0;i<k;i++)f[i]=1ll*f[i]*g[i]%mod;
    NTT(&f[0],k,-1);
    int maxn=0;
    for(int i=0;i<n;i++)maxn=max(maxn,f[i+n]);
    long long c=round(-sum*1.0/(2*n));
    answer+=n*c*c+sum*c-2ll*maxn;
    printf("%lld\n",answer);
    return 0;
}
