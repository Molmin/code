/**
 * @date: 2024.03.27
 * @problem: BZOJ3028
 * @tags: 数学, 生成函数
 */

#include<bits/stdc++.h>
using namespace std;
const int mod=10007;

int power(int x,int y=mod-2){
    if(y==0)return 1;
    int tmp=power(x,y>>1);
    tmp=tmp*tmp%mod;
    if(y&1)tmp=tmp*x%mod;
    return tmp;
}

int main(){
    string n; cin>>n;
    int x=0;
    for(int i=0;i<n.size();i++)
        x=(x*10+n[i]-'0')%mod;
    printf("%d\n",x*(x+1)%mod*(x+2)%mod*power(6)%mod);
    return 0;
}
