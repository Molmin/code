/**
 * @date: 2024.04.08
 * @problem: UOJ460
 * @tags: 构造, 图论
 */

#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> vec[1001];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n/2;i++){
        for(int j=1;j<i;j++){
            vec[j].push_back(j);
            vec[j].push_back(2*i-1);
            vec[j].push_back(i-1+j);
            vec[j].push_back(2*i);
            vec[i].push_back(j);
            vec[i].push_back(2*i);
            vec[i].push_back(i-1+j);
            vec[i].push_back(2*i-1);
        }
        vec[i].push_back(2*i-1);
        vec[i].push_back(2*i);
    }
    if(n&1){
        for(int i=1;i<=n/2;i++){
            vec[i].push_back(i);
            vec[i].push_back(n);
        }
    }
    printf("%d\n",n/2);
    for(int i=1;i<=n/2;i++){
        for(int j :vec[i])printf("%d ",j);
        printf("\n");
    }
    return 0;
}
