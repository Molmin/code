/**
 * @date: 2024.04.22
 * @problem: P3338, LOJ2200, BZOJ3527
 * @tags: 多项式, 快速傅里叶变换
 */

#include<bits/stdc++.h>
using namespace std;
const double PI=acos(-1);

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

int n; double q[100001];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf",q+i);
    int k=1; while(k<=n*2)k<<=1;
    vector<complex<double>> f1(k,0),f2(k,0),g(k,0);
    for(int i=0;i<n;i++)
        f1[i]=q[i+1],f2[i]=q[n-i],g[i]=i?(1.0/i/i):0;
    FFT(&f1[0],k,1);
    FFT(&f2[0],k,1);
    FFT(&g[0],k,1);
    for(int i=0;i<k;i++)f1[i]*=g[i],f2[i]*=g[i];
    FFT(&f1[0],k,-1);
    FFT(&f2[0],k,-1);
    for(int i=0;i<n;i++)
        printf("%.5lf\n",(f1[i]-f2[n-i-1]).real());
    return 0;
}
