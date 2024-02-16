/**
 * @date: 2024.02.15
 * @problem: QOJ837, GYM102538G
 * @tags: 图论, 点分治, 最短路
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,k;

struct Edge{
    int to,nxt;
    bool onTree;
}edge[400001];
int cntEdge,head[100001];
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

bool vis[100001];
void init(int id,int father){
    vis[id]=true;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father){
            edge[i].onTree=true;
            continue;
        }
        if(vis[v])continue;
        edge[i].onTree=true;
        init(v,id);
    }
}

bool cut[100001];
int root,fa[100001],siz[100001],maxSize[100001];
void findRoot(int id,int father,int sumSize){
    fa[id]=father,siz[id]=1,maxSize[id]=0;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(!edge[i].onTree||v==father||cut[v])continue;
        findRoot(v,id,sumSize);
        siz[id]+=siz[v];
        maxSize[id]=max(maxSize[id],siz[v]);
    }
    maxSize[id]=max(maxSize[id],sumSize-siz[id]);
    if(!root||maxSize[id]<maxSize[root])root=id;
}

int levelRoot[19][100001];
void calcSize(int id,int father,int level){
    siz[id]=1,levelRoot[level][id]=root;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(!edge[i].onTree||v==father||cut[v])continue;
        calcSize(v,id,level);
        siz[id]+=siz[v];
    }
}

int col[100001];
void updateColor(int id,int father,int color){
    col[id]=color;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father||cut[v]||!edge[i].onTree)continue;
        updateColor(v,id,color);
    }
}

void calcTargetPoints(int id,int father,vector<int> &tar,int level){
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father||cut[v]||levelRoot[level][v]!=root)continue;
        if(!edge[i].onTree){
            if(id<v&&col[id]!=col[v])tar.push_back(id);
        }
        else calcTargetPoints(v,id,tar,level);
    }
}

vector<int> target[19][100001];
int dis[19][11][100001],minn[100001][11];
void divide(int id,int level){
    root=0; findRoot(id,0,siz[id]);
    calcSize(root,0,level);
    for(int i=head[root];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(cut[v]||!edge[i].onTree)continue;
        updateColor(v,root,v);
    }
    col[root]=root;
    vector<int> tar;
    tar.push_back(root);
    calcTargetPoints(root,0,tar,level);
    sort(tar.begin(),tar.end());
    tar.resize(unique(tar.begin(),tar.end())-tar.begin());
    target[level][root]=tar;
    for(int i=0;i<tar.size();i++){
        minn[root][i]=0x3fffffff;
        queue<int> Q,clearQueue;
        Q.push(tar[i]);
        clearQueue.push(tar[i]),vis[tar[i]]=true;
        while(!Q.empty()){
            int u=Q.front(); Q.pop();
            for(int j=head[u];j;j=edge[j].nxt){
                int v=edge[j].to;
                if(cut[v]||levelRoot[level][v]!=root||vis[v])continue;
                dis[level][i][v]=dis[level][i][u]+1;
                Q.push(v);
                clearQueue.push(v),vis[v]=true;
            }
        }
        while(!clearQueue.empty())
            vis[clearQueue.front()]=false,clearQueue.pop();
    }
    cut[root]=true;
    for(int i=head[root];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(cut[v]||!edge[i].onTree)continue;
        divide(v,level+1);
    }
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    init(1,0);
    memset(vis,false,sizeof vis);
    calcSize(1,0,0);
    divide(1,1);
    int q; scanf("%d",&q);
    while(q--){
        int t,u;
        scanf("%d%d",&t,&u);
        if(t==1){
            for(int level=1;level<=18;level++){
                if(!levelRoot[level][u])continue;
                for(int i=0;i<target[level][levelRoot[level][u]].size();i++){
                    int *tmp=&minn[levelRoot[level][u]][i];
                    *tmp=min(*tmp,dis[level][i][u]);
                }
            }
        }
        else{
            int answer=0x7fffffff;
            for(int level=1;level<=18;level++){
                if(!levelRoot[level][u])continue;
                for(int i=0;i<target[level][levelRoot[level][u]].size();i++)
                    answer=min(answer,minn[levelRoot[level][u]][i]+dis[level][i][u]);
            }
            printf("%d\n",answer);
        }
    }
    return 0;
}
