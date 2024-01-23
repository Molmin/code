/**
 * @date: 2024.01.10
 * @problem: P7215, UOJ510
 * @tags: 图论, 点分治
 */

#include<bits/stdc++.h>
using namespace std;

int n,k,col[200001],answer;
vector<int> ids[200001];
bool vis[200001];

struct Edge{
    int to,nxt;
}edge[400001];
int cntEdge,head[200001];
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

bool cut[200001];
int root,fa[200001],siz[200001],maxSize[200001];
void findRoot(int id,int father,int sumSize,bool calcOnly=false){
    siz[id]=1,fa[id]=father;
    if(!calcOnly)maxSize[id]=0;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father||cut[v])continue;
        findRoot(v,id,sumSize,calcOnly);
        siz[id]+=siz[v];
        if(!calcOnly)maxSize[id]=max(maxSize[id],siz[v]);
    }
    if(calcOnly)return;
    maxSize[id]=max(maxSize[id],sumSize-siz[id]);
    if(!root||maxSize[id]<maxSize[root])root=id;
}

bool inserted[200001],inTree[200001];
queue<int> clearInserted,clearInTree;

void solve(int id){
    cut[id]=true;
    if(!vis[col[id]]){
        vis[col[id]]=true;
        while(!clearInserted.empty())
            inserted[clearInserted.front()]=false,clearInserted.pop();
        while(!clearInTree.empty())
            inTree[clearInTree.front()]=false,clearInTree.pop();
        {
            queue<pair<int,int> > Q; Q.push({id,0});
            while(!Q.empty()){
                pair<int,int> x=Q.front(); Q.pop();
                inTree[x.first]=true,clearInTree.push(x.first);
                for(int i=head[x.first];i;i=edge[i].nxt)
                    if(edge[i].to!=x.second&&!cut[edge[i].to])
                        Q.push({edge[i].to,x.first});
            }
        }
        queue<int> Q; bool flag=true;
        for(int i :ids[col[id]]){
            if(!inTree[i])flag=false;
            Q.push(i),inserted[i]=true,clearInserted.push(i);
        }
        int total=0;
        while(!Q.empty()){
            if(!flag)break;
            int x=Q.front(); Q.pop();
            if(x==id)continue;
            if(inserted[fa[x]])continue;
            for(int i :ids[col[fa[x]]]){
                if(!inTree[i]){flag=false;break;}
                Q.push(i),inserted[i]=true,clearInserted.push(i);
            }
            total++;
        }
        if(flag)answer=min(answer,total);
    }
    for(int i=head[id];i;i=edge[i].nxt){
        if(cut[edge[i].to])continue;
        root=0;
        findRoot(edge[i].to,id,siz[edge[i].to]);
        findRoot(root,0,siz[edge[i].to],true);
        solve(root);
    }
}

int main(){
    scanf("%d%d",&n,&k),answer=k-1;
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",col+i);
        ids[col[i]].push_back(i);
    }
    findRoot(1,0,n);
    findRoot(root,0,n,true);
    solve(root);
    printf("%d\n",answer);
    return 0;
}
