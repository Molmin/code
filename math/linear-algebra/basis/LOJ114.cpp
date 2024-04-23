/**
 * @date: 2024.04.22
 * @problem: LOJ114
 * @tags: 线性代数, 线性基, 模板
 */

#include<bits/stdc++.h>
using namespace std;

int n;
long long a[50];

inline bool insert(long long v){
    for(int i=49;i>=0;i--){
        if(!(v&(1ll<<i)))continue;
        if(a[i])v^=a[i];
        else{a[i]=v;break;}
    }
    return !v;
}

inline long long query(){
    long long answer=0;
    for(int i=49;i>=0;i--)
        answer=max(answer,answer^a[i]);
    return answer;
}

int main(){
    scanf("%d",&n);
    bool flag=false;
    for(int i=1;i<=n;i++){
        long long v;
        scanf("%lld",&v);
        flag=insert(v)||flag;
    }
    vector<int> vec;
    for(int i=49;i>=0;i--){
        if(!a[i])continue;
        for(int j=49;j>i;j--)
            if(a[j]&(1ll<<i))a[j]^=a[i];
        vec.push_back(i);
    }
    reverse(vec.begin(),vec.end());
    int q; scanf("%d",&q);
    while(q--){
        long long k; scanf("%lld",&k);
        if(flag)k--;
        if((1ll<<(int)vec.size())<=k){
            printf("-1\n");
            continue;
        }
        long long answer=0;
        for(int j=0;j<vec.size();j++)
            if(k&(1ll<<j))answer^=a[vec[j]];
        printf("%lld\n",answer);
    }
    return 0;
}
