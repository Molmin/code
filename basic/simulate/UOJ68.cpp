/**
 * @date: 2024.03.08
 * @problem: UOJ68
 * @tags: 模拟
 */

#include<bits/stdc++.h>
using namespace std;

struct player{
    int hui,xi,hong,mei;
    inline bool noCard(){
        return hui+hong+mei==0;
    }
    inline void read(){
        scanf("%d%d%d%d",&hui,&xi,&hong,&mei);
    }
};

inline int rev(int x){
    if(x)return 3-x;
    else return 0;
}
inline int better(int x,int y){
    if(x==1||y==1)return 1;
    if(x==0||y==0)return 0;
    return 2;
}

int calc(player x,player y){
    if(x.noCard()&&y.noCard())return 0;
    if(x.noCard())return rev(calc(y,x));
    if(x.hong>y.hui)return 1;
    if(x.hui&&!y.xi)return 1;
    if(x.mei&&x.hui>=y.hui)return 1;
    if(x.hong||y.hong){
        player xx=x,yy=y;
        yy.hui-=xx.hong,xx.hong=0;
        if(xx.mei&&xx.hui>=yy.hui)return 1;
        int res=rev(calc(yy,xx));
        if(xx.hui){
            xx.hui--,yy.xi--;
            res=better(res,rev(calc(yy,xx)));
        }
        return res;
    }
    if(x.mei&&y.mei){
        if(x.hui>=y.hui)return 1;
        else return 2;
    }
    if(!x.mei&&y.mei){
        player xx=x,yy=y;
        int res=rev(calc(yy,xx));
        if(xx.hui){
            xx.hui--,yy.xi--;
            res=better(res,rev(calc(yy,xx)));
        }
        return res;
    }
    if(x.mei&&!y.mei){
        int t=x.xi>=y.hui-x.hui?0:2;
        x.mei=0;
        return better(t,calc(x,y));
    }
    if(!x.hui&&!y.hui)return 0;
    int t=min(min(x.hui,x.xi),min(y.hui,y.xi));
    x.hui-=t,x.xi-=t,y.hui-=t,y.xi-=t;
    if(x.hui&&!y.xi)return 1;
    if(!x.hui){
        if(x.mei){
            if(y.hui>x.xi)return 2;
            else return 0;
        }
        return rev(calc(y,x));
    }
    if(!y.hui&&x.hui){
        if(x.hui>y.xi)return 1;
        else return 0;
    }
    x.hui--,y.xi--;
    return rev(calc(y,x));
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        player a,b;
        a.read(),b.read();
        int result=calc(a,b);
        if(result==1)puts("Meiyangyang");
        if(result==2)puts("Xiyangyang");
        if(!result)puts("Draw");
    }
    return 0;
}
