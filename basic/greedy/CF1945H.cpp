/**
 * @date: 2024.06.09
 * @problem: CF1945H
 * @tags: 贪心, 数据结构, ST 表, 位运算
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> d[400001];

int n,x,a[400001];
int st[20][400001];
vector<int> ids[400001];
bool vis[400001];

int queryAnd(int l,int r){
    if(l>r)return (1<<20)-1;
    int k=log2(r-l+1);
    return st[k][l]&st[k][r-(1<<k)+1];
}

int main(){
    for(int i=1;i<=400000;i++)
        for(int j=i;j<=400000;j+=i)
            d[j].push_back(i);
    int T; scanf("%d",&T);
    while(T--){
        int maxv=0;
        scanf("%d%d",&n,&x);
        for(int i=1;i<=n;i++)
            scanf("%d",a+i),st[0][i]=a[i],vis[i]=false,maxv=max(maxv,a[i]);
        for(int k=1;k<=19;k++)
            for(int i=1;i+(1<<k)-1<=n;i++)
                st[k][i]=st[k-1][i]&st[k-1][i+(1<<k-1)];
        set<int> S;
        for(int k=0;k<=19;k++){
            vector<int> vec;
            for(int i=1;i<=n;i++)
                if(!(a[i]&(1<<k)))vec.push_back(i);
            if(vec.size()<=2)
                for(int i :vec)S.insert(i),vis[i]=true;
        }
        auto print=[&](int x,int y){
            printf("Yes\n2 %d %d\n%d",a[x],a[y],n-2);
            for(int i=1;i<=n;i++)
                if(i!=x&&i!=y)printf(" %d",a[i]);
            printf("\n");
        };
        bool flag=false;
        for(int i :S){
            for(int j=1;j<=n&&!flag;j++){
                if(i==j)continue;
                int l=i,r=j; if(l>r)swap(l,r);
                int sum=queryAnd(1,l-1)&queryAnd(l+1,r-1)&queryAnd(r+1,n);
                int gcd=__gcd(a[l],a[r]);
                if(gcd>sum+x){
                    print(l,r);
                    flag=true;
                }
            }
            if(flag)break;
        }
        if(flag)continue;
        for(int i=1;i<=maxv;i++)ids[i].clear();
        for(int i=1;i<=n;i++){
            if(vis[i])continue;
            for(int j :d[a[i]])
                if(ids[j].size()<2)ids[j].push_back(i);
        }
        for(int i=maxv;i>=1&&!flag;i--){
            if(ids[i].size()<2)continue;
            int l=ids[i][0],r=ids[i][1];
            int sum=queryAnd(1,l-1)&queryAnd(l+1,r-1)&queryAnd(r+1,n);
            int gcd=__gcd(a[l],a[r]);
            if(gcd>sum+x){
                print(l,r);
                flag=true;
            }
        }
        if(flag)continue;
        puts("No");
    }
    return 0;
}
