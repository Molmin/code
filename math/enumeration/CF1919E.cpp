/**
 * @date: 2024.02.21
 * @problem: CF1919E
 * @tags: 数学, 组合数学, 组合计数, 思维, 构造
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;

long long power(long long x,long long y=mod-2){
    if(y==0)return 1;
    long long tmp=power(x,y>>1);
    tmp=tmp*tmp%mod;
    if(y&1)tmp=tmp*x%mod;
    return tmp;
}

long long fac[10001],invfac[10001];
void init(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    invfac[n]=power(fac[n]);
    for(int i=n;i>=1;i--)invfac[i-1]=invfac[i]*i%mod;
}
inline long long C(int x,int y){
    return fac[x]*invfac[x-y]%mod*invfac[y]%mod;
}

int n,a[5001],_cnt[10001],*cnt=_cnt+5000;
int _now[10001],*now=_now+5000;

int main(){
    init(10000);
    int T; scanf("%d",&T);
    while(T--){
        memset(_cnt,0,sizeof _cnt);
        scanf("%d",&n);
        int mina=n,maxa=-n;
        cnt[0]++;
        for(int i=1;i<=n;i++){
            scanf("%d",a+i);
            cnt[a[i]]++;
            mina=min(mina,a[i]);
            maxa=max(maxa,a[i]);
        }
        long long sum=0;
        for(int s=mina;s<=maxa;s++){
            memset(_now,0,sizeof _now);
            now[0]++;
            for(int i=1;i<=a[n];i++)now[i]++;
            if(a[n]<s)for(int i=a[n]+1;i<=s;i++)now[i]++;
            else for(int i=max(a[n],0)-1;i>=s;i--)now[i]++;
            bool flag=true;
            long long answer=1;
            for(int i=max(a[n],s);i>mina;i--){
                int require=cnt[i]-now[i];
                if(require<0||!now[i]){flag=false;break;}
                answer=answer*C(require+now[i]-1,now[i]-1)%mod;
                now[i]+=require,now[i-1]+=require;
            }
            for(int i=min(0,mina);i<=max(0,maxa);i++)
                if(now[i]!=cnt[i])flag=false;
            if(flag)sum+=answer;
        }
        printf("%lld\n",sum%mod);
    }
    return 0;
}
