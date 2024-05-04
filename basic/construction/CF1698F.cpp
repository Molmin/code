/**
 * @date: 2024.05.04
 * @problem: CF1698F
 * @tags: 构造
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[501],b[501],posa[501],posb[501];
vector<pair<int,int>> ops,revops;

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",a+i);
        for(int i=1;i<=n;i++)
            scanf("%d",b+i);
        ops.clear(),revops.clear();
        vector<pair<int,int>> A,B;
        for(int i=1;i<n;i++){
            A.emplace_back(min(a[i],a[i+1]),max(a[i],a[i+1]));
            B.emplace_back(min(b[i],b[i+1]),max(b[i],b[i+1]));
        }
        sort(A.begin(),A.end());
        sort(B.begin(),B.end());
        bool flag=a[1]==b[1]&&a[n]==b[n];
        for(int i=0;i<n-1&&flag;i++)
            if(A[i]!=B[i])flag=false;
        if(!flag){
            puts("NO");
            continue;
        }
        auto doA=[&](int l,int r){
            assert(a[l]==a[r]);
            reverse(a+l,a+r+1);
            ops.emplace_back(l,r);
        };
        auto doB=[&](int l,int r){
            assert(b[l]==b[r]);
            reverse(b+l,b+r+1);
            revops.emplace_back(l,r);
        };
        for(int i=1;i<=n;i++){
            if(a[i]==b[i])continue;
            bool flag=false;
            for(int j=i+1;j<=n&&!flag;j++)
                if(a[j]==a[i-1]&&a[j-1]==b[i])
                    doA(i-1,j),flag=true;
            for(int j=i+1;j<=n&&!flag;j++)
                if(b[j]==b[i-1]&&b[j-1]==a[i])
                    doB(i-1,j),flag=true;
            if(flag)continue;
            memset(posa,0,sizeof posa);
            memset(posb,0,sizeof posb);
            for(int j=i+1;j<=n;j++){
                if(a[j]==a[i-1])posa[a[j-1]]=j;
                if(b[j]==b[i-1])posb[b[j-1]]=j;
            }
            for(int j=1;j<=n&&!flag;j++)
                if(posa[j]&&posb[j]){
                    doA(i-1,posa[j]),doB(i-1,posb[j]);
                    flag=true;
                }
        }
        puts("YES");
        reverse(revops.begin(),revops.end());
        printf("%d\n",(int)ops.size()+(int)revops.size());
        for(pair<int,int> op :ops)
            printf("%d %d\n",op.first,op.second);
        for(pair<int,int> op :revops)
            printf("%d %d\n",op.first,op.second);
    }
    return 0;
}
