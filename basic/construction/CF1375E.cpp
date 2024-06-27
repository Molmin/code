/**
 * @date: 2024.06.09
 * @problem: CF1375E
 * @tags: 构造
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[1001],pos[1001];
pair<int,int> vals[1001];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",a+i);
        vals[i]={a[i],i};
    }
    sort(vals+1,vals+1+n);
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(vals+1,vals+1+n,pair<int,int>{a[i],i})-vals;
        pos[a[i]]=i;
    }
    vector<pair<int,int>> answer;
    for(int i=2;i<=n;i++){
        vector<int> vec;
        for(int j=1;j<i;j++)
            if(pos[j]>pos[i])vec.push_back(pos[j]);
        sort(vec.begin(),vec.end());
        reverse(vec.begin(),vec.end());
        for(int j :vec)answer.emplace_back(pos[i],j);
    }
    printf("%d\n",(int)answer.size());
    for(pair<int,int> i :answer)
        printf("%d %d\n",i.first,i.second);
    return 0;
}
