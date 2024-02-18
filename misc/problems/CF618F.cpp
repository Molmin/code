/**
 * @date: 2024.02.17
 * @problem: CF618F
 * @tags: 思维, 前缀和, 数学, 抽屉原理
 */

#include<bits/stdc++.h>
using namespace std;

int n,a[1000001],b[1000001];
long long suma[1000001],sumb[1000001];
bool swapped;
int r1[1000000],r2[1000000];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),suma[i]=suma[i-1]+a[i];
    for(int i=1;i<=n;i++)
        scanf("%d",b+i),sumb[i]=sumb[i-1]+b[i];
    memset(r1,-1,sizeof r1);
    if(suma[n]>sumb[n]){
        swap(a,b); swap(suma,sumb);
        swapped=true;
    }
    int tar=0;
    for(int i=0;i<=n;i++){
        while(sumb[tar]<suma[i])tar++;
        int val=sumb[tar]-suma[i];
        if(r1[val]!=-1){
            int l1=r1[val],l2=r2[val];
            int r1=i,r2=tar;
            if(swapped)swap(l1,l2),swap(r1,r2);
            printf("%d\n",r1-l1);
            for(int j=l1+1;j<=r1;j++)
                printf("%d%c",j," \n"[j==r1]);
            printf("%d\n",r2-l2);
            for(int j=l2+1;j<=r2;j++)
                printf("%d%c",j," \n"[j==r2]);
            return 0;
        }
        r1[val]=i,r2[val]=tar;
    }
    return 0;
}
