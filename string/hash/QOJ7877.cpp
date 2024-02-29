/**
 * @date: 2024.02.25
 * @problem: QOJ7877, GYM104857D
 * @tags: 哈希, 差分
 */

#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int T=998244353;

inline int read(){
    int ret=0; char ch;
    while(isspace(ch=getchar()));
    do ret=ret*62+(ch<='9'?ch-'0':(ch<='Z'?36+ch-'A':10+ch-'a'));
    while(!isspace(ch=getchar()));
    return ret;
}

int n,a[2000001],d[2000001];
ull base[2000001],hashval[2000001];
bool answer[2000001];

inline ull getHash(int l,int len){
    int r=l+len-1;
    return hashval[r]-hashval[l-1]*base[len];
}
inline bool check(int k,int l){
    int len=l-(k<<1|1);
    return getHash(1,len)+getHash(k<<1|1,len)==2*getHash(k+1,len);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)a[i]=read();
    base[0]=1;
    for(int i=1;i<n;i++){
        d[i]=a[i+1]-a[i];
        hashval[i]=hashval[i-1]*T+d[i];
        base[i]=base[i-1]*T;
    }
    int pos=0;
    for(int k=1;k<=(n-1>>1);k++){
        if(a[1]+a[k<<1|1]!=a[k+1]*2)continue;
        answer[k<<1|1]=true;
        pos=max(pos,k<<1|1);
        while(pos<n&&check(k,pos+1))answer[++pos]=true;
    }
    for(int i=1;i<=n;i++)
        printf("%d",answer[i]);
    printf("\n");
    return 0;
}
