/**
 * @date: 2024.02.23
 * @problem: GYM103447C
 * @tags: 图论, 树上启发式合并, 贪心
 */

#include<bits/stdc++.h>
using namespace std;

int n,c[100001];

struct Edge{
    int to,nxt;
}edge[200001];
int cntEdge,head[100001];
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

struct Node{
    map<int,int> s;
    set<int> maxid;
    int maxval,answer;
    inline void add(int x){
        s[x]++;
        if(s[x]==maxval)maxid.insert(x);
        else if(s[x]>maxval){
            maxid.clear();
            maxid.insert(x);
            maxval=s[x];
        }
    }
}node[100001];

int tar[100001],id;
void dfs(int id,int father){
    tar[id]=id;
    int pos=0;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father)continue;
        dfs(v,id);
        if(!pos||node[tar[v]].maxid.size()>node[tar[pos]].maxid.size())pos=v;
    }
    if(!pos){
        node[id].add(c[id]);
        node[id].answer=1;
        return;
    }
    tar[id]=tar[pos];
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(v==father||v==pos)continue;
        for(int x :node[tar[v]].maxid)
            node[tar[id]].add(x);
        node[tar[id]].answer+=node[tar[v]].answer;
    }
    node[tar[id]].answer-=node[tar[id]].maxval-1;
    if(node[tar[id]].maxval==1)return;
    node[tar[id]].s.clear();
    node[tar[id]].maxval=1;
    for(int x :node[tar[id]].maxid)
        node[tar[id]].s[x]=1;
}

int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        int fa; scanf("%d",&fa);
        addEdge(fa,i);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",c+i);
    dfs(1,0);
    printf("%d\n",node[tar[1]].answer);
    return 0;
}
