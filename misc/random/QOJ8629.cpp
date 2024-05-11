/**
 * @date: 2024.05.10
 * @problem: QOJ8629
 * @tags: 通信, 图论, 二分图, 构造, 随机化
 */

#include<bits/stdc++.h>
#include"treasure.h"
using namespace std;

void Alice(
    const int testid,const int n,const int m,
    const int x,const int u[],const int v[],bool result[]
){
    static vector<int> E[1000000];
    static int dis[1000000];
    static bool vis[1000000];
    memset(dis,0x7f,sizeof dis);
    memset(vis,false,sizeof vis);
    for(int i=0;i<m;i++){
        E[u[i]].push_back(v[i]);
        E[v[i]].push_back(u[i]);
    }
    queue<int> Q;
    Q.push(x),dis[x]=0,vis[x]=true;
    while(!Q.empty()){
        int u=Q.front(); Q.pop();
        for(int v :E[u]){
            if(vis[v])continue;
            Q.push(v),vis[v]=true,dis[v]=dis[u]+1;
        }
    }
    int B=sqrt(n);
    for(int i=0;i<m;i++){
        int x=u[i],y=v[i];
        if(dis[x]>dis[y])swap(x,y);
        if(dis[x]<B)result[i]=1;
        else if((dis[x]-B)&1)result[i]=0;
        else result[i]=1;
        if(dis[u[i]]>dis[v[i]])result[i]=!result[i];
    }
}

mt19937 mt_rand(random_device{}());
int rnd(int l,int r){
    return mt_rand()%(r-l+1)+l;
}

int Bob(const int testId,const int n){
    static int vis[1000000];
    memset(vis,false,sizeof vis);
    auto getTargets=[&](vector<pair<int,bool>> &vec,int &inTarget,int &outTarget){
        inTarget=-1,outTarget=-1;
        for(pair<int,bool> i :vec){
            if(i.second)inTarget=i.first;
            else outTarget=i.first;
        }
    };
    int answer=-1,total=min(n,5000),u;
    bool reget=true;
    while(true){
        if(reget){
            do u=rnd(0,n-1); while(vis[u]);
        }
        else reget=true;
        vis[u]=true;
        vector<pair<int,bool>> vec=discover(u); total--;
        int inTarget,outTarget; getTargets(vec,inTarget,outTarget);
        if(inTarget!=-1&&outTarget!=-1){
            u=outTarget;
            while(true){
                if(vis[u])return u;
                vec=discover(u),vis[u]=true,total--;
                getTargets(vec,inTarget,outTarget);
                if(outTarget==-1)return u;
                u=outTarget;
            }
        }
        else if(inTarget!=-1)answer=u;
        else if(outTarget!=-1){
            if(!vis[outTarget])
                u=outTarget,reget=false;
        }
        if(!total)return answer;
    }
    return 0;
}
