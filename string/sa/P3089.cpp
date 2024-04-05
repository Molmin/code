/**
 * @date: 2024.03.16
 * @problem: P3089, LOJ111
 * @tags: 字符串, 后缀数组, 模板
 */

#include<bits/stdc++.h>
using namespace std;

int n,tot[1000001],rnk[1000001],sa[1000001];
int oldrnk[1000001],oldsa[1000001];
string s;

void SA(){
    for(int i=1;i<=n;i++)tot[s[i]]++;
    for(int i='0';i<='z';i++)tot[i]+=tot[i-1];
    for(int i=1;i<=n;i++)sa[tot[s[i]]--]=i;
    for(int i=1;i<=n;i++)
        rnk[sa[i]]=rnk[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
    for(int k=1;k<=n;k<<=1){
        memset(tot,0,sizeof tot);
        swap(sa,oldsa);
        for(int i=1;i<=n;i++)tot[oldsa[i]+k<=n?rnk[oldsa[i]+k]:0]++;
        for(int i=1;i<=n;i++)tot[i]+=tot[i-1];
        for(int i=n;i>=1;i--)sa[tot[oldsa[i]+k<=n?rnk[oldsa[i]+k]:0]--]=oldsa[i];
        memset(tot,0,sizeof tot);
        swap(sa,oldsa);
        for(int i=1;i<=n;i++)tot[rnk[oldsa[i]]]++;
        for(int i=1;i<=n;i++)tot[i]+=tot[i-1];
        for(int i=n;i>=1;i--)sa[tot[rnk[oldsa[i]]]--]=oldsa[i];
        swap(rnk,oldrnk);
        for(int i=1,j=0;i<=n;i++){
            if(oldrnk[sa[i]]==oldrnk[sa[i-1]]&&oldrnk[sa[i]+k]==oldrnk[sa[i-1]+k])rnk[sa[i]]=j;
            else j++,rnk[sa[i]]=j;
        }
    }
}

int main(){
    cin>>s,n=s.size(),s=" "+s;
    SA();
    for(int i=1;i<=n;i++)
        printf("%d%c",sa[i]," \n"[i==n]);
    return 0;
}
