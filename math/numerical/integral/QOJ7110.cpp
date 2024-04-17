/**
 * @date: 2024.03.31
 * @problem: QOJ7110, GYM104566I
 * @tags: 数学, 二分, 计算几何, 积分, 自适应辛普森积分
 */

#include<bits/stdc++.h>
using namespace std;
const double eps=1e-10;

double v,r,d;

inline double func(double theta){
    double s=sin(theta);
    return 1/v/(sqrt(s*s+3)-s);
}
inline double simpson(double l,double r){
    return (func(l)+4*func((l+r)/2)+func(r))*(r-l)/6;
}
double integral(double l,double r,double eps,double val){
    double mid=(l+r)/2;
    double lval=simpson(l,mid),rval=simpson(mid,r);
    if(abs(val-lval-rval)<=15*eps)
        return lval+rval+(lval+rval-val)/15;
    return integral(l,mid,eps/2,lval)+integral(mid,r,eps/2,rval);
}
inline double integral(double l,double r){
    return integral(l,r,eps,simpson(l,r));
}

inline bool check(double t){
    double target=d-t*v;
    double theta=acos(-1)-acos((2*r)/(target-2*r));
    double dx=cos(theta)*(2*r),dy=sin(theta)*(2*r);
    double dis=hypot(target-2*r+dx,dy);
    double result=integral(0,theta)*(2*r)+dis*func(theta);
    return result<=t;
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%lf%lf%lf",&v,&r,&d);
        double L=0,R=(d-4*r)/v-eps;
        while(R-L>=1e-8){
            double mid=(L+R)/2;
            if(check(mid))R=mid;
            else L=mid;
        }
        double answer=d/v;
        if(check(R))answer=min(answer,R);
        printf("%.8lf\n",answer);
    }
    return 0;
}
