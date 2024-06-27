/**
 * @date: 2024.06.09
 * @problem: CF1329D
 * @tags: 构造, 数据结构, 线段树
 */

#include<bits/stdc++.h>
using namespace std;

int n,m,pos[200001];
char s[200002],t[200001];
bool vis[200001];

int cnt['z'+1],most,sum;
void findMost(){
    most='z';
    for(char c='a';c<'z';c++)
        if(cnt[c]>cnt[most])most=c;
}

struct SegmentTree{
    struct Node{
        int l,r;
        int sum,tag;
        void update(int val){
            sum=(r-l+1)*val,tag=val;
        }
    }node[800001];
    
    void pushdown(int id){
        if(node[id].tag!=-1){
            node[id<<1].update(node[id].tag);
            node[id<<1|1].update(node[id].tag);
            node[id].tag=-1;
        }
    }
    void pushup(int id){
        node[id].sum=node[id<<1].sum+node[id<<1|1].sum;
    }

    void build(int id,int l,int r){
        node[id].l=l,node[id].r=r;
        node[id].sum=0,node[id].tag=-1;
        if(l==r)return;
        int mid=l+r>>1;
        build(id<<1,l,mid);
        build(id<<1|1,mid+1,r);
    }

    void update(int id,int l,int r,int val){
        if(l<=node[id].l&&node[id].r<=r)
            return node[id].update(val);
        int mid=node[id].l+node[id].r>>1;
        pushdown(id);
        if(l<=mid)update(id<<1,l,r,val);
        if(mid<r)update(id<<1|1,l,r,val);
        pushup(id);
    }

    int query(int id,int l,int r){
        if(l<=node[id].l&&node[id].r<=r)
            return node[id].sum;
        int mid=node[id].l+node[id].r>>1,ret=0;
        pushdown(id);
        if(l<=mid)ret+=query(id<<1,l,r);
        if(mid<r)ret+=query(id<<1|1,l,r);
        return ret;
    }
}_;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s+1);
        n=strlen(s+1);
        m=sum=0;
        for(int i=1;i<n;i++)
            if(s[i]==s[i+1])t[++m]=s[i],pos[m]=i,vis[m]=false;
        vector<pair<int,int>> answer;
        stack<int> s;
        for(char c='a';c<='z';c++)cnt[c]=0;
        for(int i=1;i<=m;i++)cnt[t[i]]++,sum++;
        findMost();
        if(cnt[most]>sum/2){
            for(int i=1;i<=m;i++){
                if(t[i]==most){
                    if(s.empty()||t[s.top()]==t[i])s.push(i);
                    else answer.emplace_back(s.top(),i),s.pop();
                }
                else{
                    if(s.empty()||t[s.top()]!=most)s.push(i);
                    else answer.emplace_back(s.top(),i),s.pop();
                }
            }
            while(!s.empty())answer.emplace_back(s.top(),0),s.pop();
        }
        else{
            if(m&1){
                answer.emplace_back(m,0);
                sum--,cnt[t[m]]--,m--;
            }
            for(int i=1;i<=m;i++){
                if(s.empty()||t[s.top()]==t[i]){
                    s.push(i); continue;
                }
                sum-=2,cnt[t[s.top()]]--,cnt[t[i]]--;
                findMost();
                if(cnt[most]>sum/2){
                    sum+=2,cnt[t[s.top()]]++,cnt[t[i]]++;
                    s.push(i);
                }
                else{
                    vis[s.top()]=vis[i]=true;
                    answer.emplace_back(s.top(),i),s.pop();
                }
            }
        }
        printf("%d\n",(int)answer.size()+1);
        _.build(1,1,n);
        _.update(1,1,n,1);
        for(pair<int,int> i :answer){
            int x=i.first,y=i.second;
            if(y){
                int u=_.query(1,1,pos[x]+1);
                int v=_.query(1,1,pos[y]);
                printf("%d %d\n",u,v);
                _.update(1,pos[x]+1,pos[y],0);
            }
            else{
                int u=_.query(1,1,pos[x]);
                printf("%d %d\n",u,u);
                _.update(1,pos[x],pos[x],0);
            }
        }
        printf("%d %d\n",1,_.query(1,1,n));
    }
    return 0;
}
