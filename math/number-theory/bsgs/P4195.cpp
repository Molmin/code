/**
 * @date: 2024.03.25
 * @problem: P3846, SP_MOD
 * @tags: 数学, 数论, BSGS, 模板
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

int exbsgs(int a,int v,int mod){
    if(mod==1||v==1)return 0;
    int cnt=0,base=1;
    while(true){
        int gcd=__gcd(a,mod);
        if(gcd==1)break;
        if(v%gcd)return -1;
        cnt++,v/=gcd,mod/=gcd;
        base=1ll*base*(a/gcd)%mod;
        if(base==v)return cnt;
    }
    int ret=bsgs(a,v,mod,base);
    if(ret==-1)return -1;
    else return ret+cnt;
}

int main(){
    int a,mod,v;
    scanf("%d%d%d",&a,&mod,&v);
    while(a||mod||v){
        int ret=exbsgs(a%mod,v%mod,mod);
        if(ret==-1)puts("No Solution");
        else printf("%d\n",ret);
        scanf("%d%d%d",&a,&mod,&v);
    }
    return 0;
}
