/**
 * @date: 2024.03.25
 * @problem: P3846
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

int main(){
    int a,v,mod;
    scanf("%d%d%d",&mod,&a,&v);
    int answer=bsgs(a,v,mod);
    if(answer==-1)puts("no solution");
    else printf("%d\n",answer);
    return 0;
}
