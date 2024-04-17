/**
 * @date: 2024.04.01
 * @problem: P3803
 * @tags: 多项式, 快速傅里叶变换, 模板
 */

#include<bits/stdc++.h>
using namespace std;
const double PI=acos(-1);

int n,m,a[2000001],b[2000001];

inline void FFT(complex<double> *a,int len,int k=1){
    vector<int> rev;
    for(int i=0;i<len;i++)
        rev.push_back((i?rev[i>>1]:0)>>1|((i&1)?(len>>1):0));
    for(int i=0;i<len;i++)
        if(i<rev[i])swap(a[i],a[rev[i]]);
    for(int h=2;h<=len;h<<=1){
        complex<double> w=cos(2*PI/h)+k*sin(2*PI/h)*1i;
        for(int i=0;i<len;i+=h){
            complex<double> now=1;
            for(int j=i;j<i+(h>>1);j++,now*=w){
                complex<double> x=a[j],y=now*a[j+(h>>1)];
                a[j]=x+y,a[j+(h>>1)]=x-y;
            }
        }
    }
    if(k==-1)for(int i=0;i<len;i++)a[i]/=len;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)
        scanf("%d",a+i);
    for(int i=0;i<=m;i++)
        scanf("%d",b+i);
    int k=1; while(k<=n+m)k<<=1;
    vector<complex<double>> f,g;
    for(int i=0;i<k;i++)
        f.push_back(i<=n?a[i]:0);
    for(int i=0;i<k;i++)
        g.push_back(i<=m?b[i]:0);
    FFT(&f[0],k,1);
    FFT(&g[0],k,1);
    for(int i=0;i<k;i++)f[i]*=g[i];
    FFT(&f[0],k,-1);
    for(int i=0;i<=n+m;i++)
        printf("%d%c",(int)round(f[i].real())," \n"[i==n+m]);
    return 0;
}
