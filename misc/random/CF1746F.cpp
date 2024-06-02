/**
 * @date: 2024.06.02
 * @problem: CF1746F
 * @tags: 随机化, 数据结构, 树状数组
 */

#include<bits/stdc++.h>
using namespace std;
const int CNT_TEST=25;

mt19937 mt_rand(random_device{}());

int n,q,a[300001],now[300001],queries[300001][3];
int values[600001],cnt,newValue[600001];
bool answer[300001];

struct BIT{
    long long v[300001];
    void clear(){
        for(int i=1;i<=n;i++)v[i]=0;
    }
    inline int lowbit(int x){return x&-x;};
    void add(int x,int val){
        for(;x<=n;x+=lowbit(x))v[x]+=val;
    }
    long long query(int x){
        long long ret=0;
        for(;x;x-=lowbit(x))ret+=v[x];
        return ret;
    }
}_;

void getNewValue(int &x){
    x=lower_bound(values+1,values+1+cnt,x)-values;
}

int main(){
    memset(answer,true,sizeof answer);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
        values[++cnt]=a[i];
    }
    for(int i=1;i<=q;i++){
        int op; scanf("%d",&op);
        if(op==1){
            int pos,val;
            scanf("%d%d",&pos,&val);
            values[++cnt]=val;
            queries[i][0]=pos,queries[i][1]=val;
        }
        else{
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            queries[i][0]=l,queries[i][1]=r,queries[i][2]=k;
        }
    }
    sort(values+1,values+1+cnt);
    cnt=unique(values+1,values+1+cnt)-values-1;
    for(int i=1;i<=n;i++)getNewValue(a[i]);
    for(int i=1;i<=q;i++)if(!queries[i][2])getNewValue(queries[i][1]);
    for(int testid=1;testid<=CNT_TEST;testid++){
        for(int i=1;i<=cnt;i++)newValue[i]=mt_rand()%(1<<30);
        _.clear();
        for(int i=1;i<=n;i++)_.add(i,newValue[a[i]]),now[i]=a[i];
        for(int i=1;i<=q;i++){
            if(queries[i][2]){
                long long sum=_.query(queries[i][1])-_.query(queries[i][0]-1);
                if(sum%queries[i][2]%queries[i][2]!=0)answer[i]=false;
            }
            else{
                int x=queries[i][0];
                _.add(x,newValue[queries[i][1]]-newValue[now[x]]);
                now[x]=queries[i][1];
            }
        }
    }
    for(int i=1;i<=q;i++){
        if(!queries[i][2])continue;
        if(answer[i])puts("YES");
        else puts("NO");
    }
    return 0;
}
