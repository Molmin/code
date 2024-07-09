/**
 * @date: 2024.07.04
 * @problem: CF1616E
 * @tags: 数据结构, 树状数组, 贪心, 栈
 */

#include<bits/stdc++.h>
using namespace std;

int n;
char s[100002],t[100002];

struct BIT{
    int v[100001];
    inline int lowbit(int x){
        return x&-x;
    }
    void clear(){
        for(int i=1;i<=n;i++)v[i]=0;
    }
    void add(int x,int val){
        for(;x<=n;x+=lowbit(x))v[x]+=val;
    }
    int query(int x){
        int ret=0;
        for(;x;x-=lowbit(x))ret+=v[x];
        return ret;
    }
}_;

stack<int> sta[26];

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%s%s",&n,s+1,t+1);
        _.clear();
        for(int i=2;i<=n;i++)_.add(i,1);
        for(int i=0;i<26;i++)
            while(!sta[i].empty())sta[i].pop();
        for(int i=n;i>=1;i--)sta[s[i]-'a'].push(i);
        long long answer=1e18,now=0;
        for(int i=1;i<=n;i++){
            int minn=1e9;
            for(int j=0;j<t[i]-'a';j++)
                if(!sta[j].empty())minn=min(minn,sta[j].top());
            if(minn<=n)answer=min(answer,now+_.query(minn));
            if(sta[t[i]-'a'].empty())break;
            now+=_.query(sta[t[i]-'a'].top());
            _.add(sta[t[i]-'a'].top(),-1);
            sta[t[i]-'a'].pop();
        }
        if(answer==1e18)puts("-1");
        else printf("%lld\n",answer);
    }
    return 0;
}
