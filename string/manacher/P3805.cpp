/**
 * @date: 2024.04.07
 * @problem: P3805
 * @tags: 字符串, manacher, 模板
 */

#include<bits/stdc++.h>
using namespace std;

char ch[11000001],s[22000003];
int f[22000003];

int main(){
    scanf("%s",ch);
    int n=0; s[++n]='#';
    for(int i=0,len=strlen(ch);i<len;i++)
        s[++n]=ch[i],s[++n]='#';
    int pos=1,maxr=1,answer=1;
    f[1]=1;
    for(int i=2;i<=n;i++){
        if(i<=maxr)f[i]=min(f[pos*2-i],maxr-i+1);
        else f[i]=1;
        while(1<=i-f[i]&&i+f[i]<=n&&s[i-f[i]]==s[i+f[i]])f[i]++;
        answer=max(answer,f[i]-1);
        if(i+f[i]-1>maxr)maxr=i+f[i]-1,pos=i;
    }
    printf("%d\n",answer);
    return 0;
}
