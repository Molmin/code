/**
 * @date: 2024.04.15
 * @problem: CF1375H
 * @tags: 构造, 分块, 分治
 */

#include<bits/stdc++.h>
using namespace std;

int n,q,a[(1<<12)+2],pos[(1<<12)+1],answer[(1<<16)+1];
int blockposl[(1<<8)+1][(1<<12)+2],blockposr[(1<<8)+1][(1<<12)+2];
int blocklen,blockId[(1<<12)+1];

int cntNode;
pair<int,int> node[2200001];
vector<vector<int>> nodeId[(1<<8)+1];

inline int newNode(int x,int y){
    if(!x||!y)return x+y;
    node[++cntNode]={x,y};
    return cntNode;
}

vector<vector<int>> build(int l,int r){
    if(l==r)return {{pos[l]}};
    vector<vector<int>> ret(r-l+1,vector<int>(r-l+1,0));
    int mid=l+r>>1;
    vector<vector<int>> L=build(l,mid),R=build(mid+1,r);
    vector<int> t;
    for(int i=l;i<=r;i++)t.push_back(pos[i]);
    sort(t.begin(),t.end());
    for(int i=0,ll=0,rl=0;i<=r-l;i++){
        if(i)(a[t[i-1]]<=mid?ll:rl)++;
        for(int j=r-l,lr=mid-l,rr=r-mid-1;j>=i;j--){
            if(j<r-l)(a[t[j+1]]<=mid?lr:rr)--;
            ret[i][j]=newNode(ll<=lr?L[ll][lr]:0,rl<=rr?R[rl][rr]:0);
        }
    }
    return ret;
}

int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),pos[a[i]]=i;
    blocklen=sqrt(q),cntNode=n;
    while((n-1)/blocklen+1>(1<<8))blocklen++;
    for(int i=1;i<=n;i++)
        blockId[i]=(i-1)/blocklen+1;
    for(int i=1;i<=(n-1)/blocklen+1;i++){
        int minn=(i-1)*blocklen+1,maxn=min(i*blocklen,n);
        nodeId[i]=build(minn,maxn);
        for(int j=1;j<=n;j++)
            blockposl[i][j]=blockposl[i][j-1]+(minn<=a[j-1]&&a[j-1]<=maxn);
        blockposr[i][n+1]=maxn-minn;
        for(int j=n;j>=1;j--)
            blockposr[i][j]=blockposr[i][j+1]-(minn<=a[j+1]&&a[j+1]<=maxn);
    }
    for(int i=1;i<=q;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        for(int j=1;j<=(n-1)/blocklen+1;j++){
            int x=blockposl[j][l],y=blockposr[j][r];
            int id=x<=y?nodeId[j][x][y]:0;
            answer[i]=newNode(answer[i],id);
        }
    }
    printf("%d\n",cntNode);
    for(int i=n+1;i<=cntNode;i++)
        printf("%d %d\n",node[i].first,node[i].second);
    for(int i=1;i<=q;i++)
        printf("%d%c",answer[i]," \n"[i==q]);
    return 0;
}
