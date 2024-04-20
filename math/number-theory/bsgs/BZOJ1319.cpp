/**
 * @date: 2024.04.19
 * @problem: BZOJ1319, BZOJ1420
 * @tags: 数论, 原根, BSGS, exgcd
 */

#include<bits/stdc++.h>
using namespace std;

int p,k,a;

int power(int x,int y,int mod){
    if(y==0)return 1;
    int tmp=power(x,y>>1,mod);
    tmp=1ll*tmp*tmp%mod;
    if(y&1)tmp=1ll*tmp*x%mod;
    return tmp;
}

int getMinRoot(int n){
    vector<int> p;
    int x=n-1;
    for(int i=2;i*i<=x;i++){
        if(x%i)continue;
        p.push_back(i);
        while(x%i==0)x/=i;
    }
    if(x>0)p.push_back(x);
    for(int i=1;i<n;i++){
        bool flag=true;
        if(power(i,n-1,n)!=1)flag=false;
        for(int j=0;j<p.size()&&flag;j++)
            if(power(i,(n-1)/p[j],n)==1)flag=false;
        if(flag)return i;
    }
    return 0;
}

int bsgs(int a,int v,int mod,int now=1){
    int block=ceil(sqrt(mod));
    unordered_map<int,int> mp;
    for(int i=0;i<block;i++)
        mp[v]=i+1,v=1ll*v*a%mod;
    a=power(a,block,mod);
    for(int i=1;i<=block;i++){
        now=1ll*now*a%mod;
        int tmp=mp[now]-1;
        if(tmp!=-1)return i*block-tmp;
    }
    return -1;
}

int exgcd(int a,int b,int &x,int &y){
    if(!a){x=0,y=1;return b;}
    int d=exgcd(b%a,a,y,x);
    x-=(b/a)*y%(p-1);
    return d;
}

int main(){
    scanf("%d%d%d",&p,&k,&a);
    int g=getMinRoot(p);
    int m=bsgs(g,a,p);
    k=k%(p-1);
    int x=0,y=0,gcd=exgcd(k,p-1,x,y);
    if(m%gcd)return printf("0\n"),0;
    x=((1ll*x*(m/gcd))%(p-1)+(p-1))%(p-1);
    vector<int> answer;
    for(int i=0;i<gcd;i++)
        answer.push_back(power(g,x,p)),x+=(p-1)/gcd;
    sort(answer.begin(),answer.end());
    printf("%d\n",(int)answer.size());
    for(int i :answer)printf("%d\n",i);
    return 0;
}
