/**
 * @date: 2024.06.10
 * @problem: CF453E
 * @tags: 数据结构, 分块
 */

#include<bits/stdc++.h>
using namespace std;
const int blocklen=350;

int n,m,s[100001],v[100001],lim[100001];
int blockId[100001],cntBlock,blockL[300],blockR[300];
int clearBlock[300],clear[100001];
long long blocksum[300][100001];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        blockId[i]=(i-1)/blocklen+1;
        scanf("%d%d%d",s+i,lim+i,v+i);
    }
    cntBlock=blockId[n];
    for(int i=1;i<=cntBlock;i++){
        blockL[i]=(i-1)*blocklen+1;
        blockR[i]=min(i*blocklen,n);
        clearBlock[i]=-1;
        vector<pair<int,int>> vec;
        int pos=0; long long sumv=0;
        for(int j=blockL[i];j<=blockR[i];j++)
            if(v[j]&&lim[j])vec.emplace_back((lim[j]-1)/v[j]+1,j),sumv+=v[j];
        sort(vec.begin(),vec.end());
        for(int j=1;j<=1e5;j++){
            blocksum[i][j]=blocksum[i][j-1]+sumv;
            while(pos<vec.size()&&vec[pos].first==j){
                int x=vec[pos].second;
                sumv-=v[x],blocksum[i][j]-=1ll*j*v[x]-lim[x];
                pos++;
            }
        }
    }
    int q; scanf("%d",&q);
    while(q--){
        int t,l,r;
        scanf("%d%d%d",&t,&l,&r);
        long long answer=0;
        auto handleNotClear=[&](int b){
            for(int i=blockL[b];i<=blockR[b];i++){
                if(clearBlock[b]!=-1)clear[i]=clearBlock[b];
                if(l<=i&&i<=r){
                    answer+=min((clear[i]?0:s[i])+1ll*(t-clear[i])*v[i],1ll*lim[i]);
                    clear[i]=t;
                }
            }
            clearBlock[b]=-1;
        };
        if(blockId[l]==blockId[r])
            handleNotClear(blockId[l]);
        else{
            handleNotClear(blockId[l]);
            handleNotClear(blockId[r]);
            for(int i=blockId[l]+1;i<blockId[r];i++){
                if(clearBlock[i]==-1)handleNotClear(i);
                else answer+=blocksum[i][min(t-clearBlock[i],(int)1e5)];
                clearBlock[i]=t;
            }
        }
        printf("%lld\n",answer);
    }
    return 0;
}
