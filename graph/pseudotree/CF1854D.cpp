/**
 * @date: 2024.02.16
 * @problem: CF1854D
 * @tags: 基环树, 二分, 交互
 */

#include<bits/stdc++.h>
using namespace std;
const int M=125;

int n;
bool vis[501];

inline int binary(int u,int k){
    int l=1,r=n;
    while(l<r){
        int mid=l+r>>1;
        printf("? %d %d %d ",u,k,mid-l+1);
        for(int i=l;i<=mid;i++)
            printf("%d%c",i," \n"[i==mid]);
        fflush(stdout);
        int result;
        scanf("%d",&result);
        if(result)r=mid;
        else l=mid+1;
    }
    return l;
}

vector<int> vec;

inline bool tryToCycle(int u,int k){
    printf("? %d %d %d",u,k,vec.size());
    for(int v :vec)printf(" %d",v);
    printf("\n");
    fflush(stdout);
    int result;
    scanf("%d",&result);
    return result;
}

void printAnswer(vector<int> answer){
    printf("! %d",answer.size());
    for(int v :answer)printf(" %d",v);
    printf("\n");
    fflush(stdout);
}

void solveByCycle(){
    vector<int> answer;
    for(int i=1;i<=n;i++)
        if(tryToCycle(i,n))answer.push_back(i);
    printAnswer(answer);
}

int main(){
    scanf("%d",&n);
    vec.push_back(binary(1,n));
    vis[vec[0]]=true;
    bool flag=false;
    for(int i=1;i<M;i++){
        int nxt=binary(vec.back(),1);
        if(vis[nxt]){flag=true; break;}
        else vec.push_back(nxt),vis[nxt]=true;
    }
    if(flag){
        solveByCycle();
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(vis[i])continue;
        if(tryToCycle(i,M))vec.push_back(i),vis[i]=true;
    }
    for(int i=1;i<=n;i++){
        if(vis[i])continue;
        if(tryToCycle(i,n))vec.push_back(i),vis[i]=true;
        else if(vec.size()>M*2&&tryToCycle(i,n+M*2))
            vec.push_back(i),vis[i]=true;
    }
    printAnswer(vec);
    return 0;
}
