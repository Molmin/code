/**
 * @date: 2024.07.04
 * @problem: P7078
 * @tags: 数据结构, 双端队列
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[1000001];

void solve(){
    deque<pair<int,int>> Q1,Q2;
    auto getStrongest=[&](int &val,int &id){
        if(Q2.empty()||(!Q1.empty()&&Q1.back()>Q2.back()))
            id=Q1.back().second,val=Q1.back().first,Q1.pop_back();
        else id=Q2.back().second,val=Q2.back().first,Q2.pop_back();
    };
    for(int i=1;i<=n;i++)
        Q1.emplace_back(a[i],i);
    while(true){
        if(Q1.size()+Q2.size()==2){
            puts("1");
            return;
        }
        int weakest=Q1.front().first; Q1.pop_front();
        int strongest,id;
        getStrongest(strongest,id);
        pair<int,int> next={strongest-weakest,id};
        if(!Q1.empty()&&Q1.front()<next){
            Q2.push_front(next);
            continue;
        }
        int cnt=0,answer=Q1.size()+Q2.size()+1;
        while(true){
            cnt++;
            if(Q1.size()+Q2.size()==1){
                answer+=cnt&1;
                printf("%d\n",answer);
                return;
            }
            int val,id; getStrongest(val,id);
            next.first=val-next.first,next.second=id;
            if((!Q1.empty()&&Q1.front()<next)||(!Q2.empty()&&Q2.front()<next)){
                answer+=cnt&1;
                printf("%d\n",answer);
                return;
            }
        }
    }
}

int main(){
    int T; scanf("%d",&T);
    T--;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    solve();
    while(T--){
        int k;
        scanf("%d",&k);
        for(int i=1;i<=k;i++){
            int x,y;
            scanf("%d%d",&x,&y);
            a[x]=y;
        }
        solve();
    }
    return 0;
}
