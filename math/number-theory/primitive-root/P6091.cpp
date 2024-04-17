/**
 * @date: 2024.03.24
 * @problem: P6091
 * @tags: 数学, 数论, 原根, 模板
 */

#include<bits/stdc++.h>
using namespace std;

int power(int x,int y,int mod){
    if(y==0)return 1;
    int tmp=power(x,y>>1,mod);
    tmp=1ll*tmp*tmp%mod;
    if(y&1)tmp=1ll*tmp*x%mod;
    return tmp;
}

bool vis[1000001];
int cntprime,prime[100000],minprime[1000001],phi[1000001];

void init(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cntprime]=i;
            minprime[i]=i;
            phi[i]=i-1;
        }
        for(int j=1;i*prime[j]<=n&&j<=cntprime;j++){
            vis[i*prime[j]]=true;
            minprime[i*prime[j]]=prime[j];
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            phi[i*prime[j]]=phi[i]*phi[prime[j]];
        }
    }
}

inline bool check(int n){
    if(n==2||n==4)return true;
    if(!(n&1))n>>=1;
    if(!(n&1)||n==1)return false;
    for(int i=2;i<=cntprime&&1ll*prime[i]*prime[i]<=n;i++){
        if(n%prime[i])continue;
        while(n%prime[i]==0)n/=prime[i];
        return n==1;
    }
    return true;
}

inline int getMinRoot(int n){
    vector<int> p;
    int x=phi[n];
    while(x>1){
        int d=minprime[x];
        while(x%d==0)x/=d;
        p.push_back(d);
    }
    for(int i=1;i<n;i++){
        bool flag=true;
        if(power(i,phi[n],n)!=1)flag=false;
        for(int j=0;j<p.size()&&flag;j++)
            if(power(i,phi[n]/p[j],n)==1)flag=false;
        if(flag)return i;
    }
    return 0;
}

int n,d;

int main(){
    init(1e6);
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&d);
        if(!check(n)){
            printf("0\n\n");
            continue;
        }
        int minn=getMinRoot(n);
        vector<int> answer;
        for(int i=1,now=1;i<=phi[n];i++){
            now=1ll*now*minn%n;
            if(__gcd(i,phi[n])==1)answer.push_back(now);
        }
        sort(answer.begin(),answer.end());
        printf("%d\n",answer.size());
        for(int i=d-1;i<answer.size();i+=d)
            printf("%d ",answer[i]);
        printf("\n");
    }
    return 0;
}
