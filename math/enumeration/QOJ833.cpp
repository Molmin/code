/**
 * @date: 2024.02.15
 * @problem: QOJ833, GYM102538C
 * @tags: 数学, 组合计数
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,total;
bool a[3002][3002],f[3001][3001],g[3002][3002];
vector<int> vec[6001];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            char ch; scanf(" %c",&ch);
            a[i][j]=ch=='.',total+=a[i][j];
        }
    f[1][1]=g[n][m]=true;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            f[i][j]=(f[i][j]||f[i-1][j]||f[i][j-1])&&a[i][j];
    for(int i=n;i>=1;i--)
        for(int j=m;j>=1;j--)
            g[i][j]=(g[i][j]||g[i+1][j]||g[i][j+1])&&a[i][j];
    if(!f[n][m])return printf("%lld\n",total*(total-1ll)/2),0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(!(f[i][j]&&g[i][j]))a[i][j]=false;
            else vec[i+j].push_back(i);
        }
    int cnt=0;
    long long answer=0;
    for(int i=1+1;i<=n+m;i++){
        if(vec[i].size()==1){
            cnt++,answer+=total-cnt;
            continue;
        }
        if(vec[i].size()==2)answer++;
        int u=vec[i][1],v=vec[i].back();
        for(int j=i+1;j<=n+m;j++){
            v++;
            if(!a[u][j-u])u++;
            if(!a[v][j-v])v--;
            if(u==v&&vec[j].size()!=1)answer++;
        }
        u=vec[i][0],v=vec[i][vec[i].size()-2];
        for(int j=i+1;j<=n+m;j++){
            v++;
            if(!a[u][j-u])u++;
            if(!a[v][j-v])v--;
            if(u==v&&vec[j].size()!=1)answer++;
        }
    }
    printf("%lld\n",answer);
    return 0;
}
