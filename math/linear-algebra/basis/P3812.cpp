/**
 * @date: 2024.04.22
 * @problem: P3812, LOJ113
 * @tags: 线性代数, 线性基, 模板
 */

#include<bits/stdc++.h>
using namespace std;

int n;
long long a[50];

inline void insert(long long v){
    for(int i=49;i>=0;i--){
        if(!(v&(1ll<<i)))continue;
        if(a[i])v^=a[i];
        else{a[i]=v;break;}
    }
}

inline long long query(){
    long long answer=0;
    for(int i=49;i>=0;i--)
        answer=max(answer,answer^a[i]);
    return answer;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        long long v;
        scanf("%lld",&v);
        insert(v);
    }
    printf("%lld\n",query());
    return 0;
}
