/**
 * @date: 2024.01.23
 * @problem: CF1201E1, CF1201E2
 * @tags: 博弈论
 */

#include<bits/stdc++.h>
using namespace std;
const int dx[8]={-2,-2,-1,-1,1,1,2,2};
const int dy[8]={-1,1,-2,2,-2,2,-1,1};

int n,m;

struct Point{
    int x,y;
    inline void read(){
        cin>>x>>y;
    }
    inline void print(){
        cout<<x<<' '<<y<<endl;
    }
    inline int type(){
        return (x+y)&1;
    }
    inline bool operator==(Point t)const{
        return x==t.x&&y==t.y;
    }
    inline Point to(int method){
        return{x+dx[method],y+dy[method]};
    }
    inline bool isOnlyOneStepTo(Point other){
        if(abs(x-other.x)+abs(y-other.y)!=3)return false;
        return x!=other.x&&y!=other.y;
    }
}W,B,tarW,tarB,other,myTar;

void chooseWhite(){
    cout<<"WHITE"<<endl;
    myTar=tarW;
}
void chooseBlack(){
    cout<<"BLACK"<<endl;
    myTar=tarB;
}

struct Queue{
    bool vis[1001][1001];
    Point v[1000001];
    int pre[1000001];
    int step[1000001];
    int head,tail;

    inline void clear(){
        memset(vis,0,sizeof vis);
        head=1,tail=0;
    }
    inline void push(Point x,int prev,int s){
        vis[x.x][x.y]=true;
        v[++tail]=x,step[tail]=s,pre[tail]=prev;
    }
    inline Point pop(){
        return v[head++];
    }

    void print(int id){
        if(pre[id])print(pre[id]);
        else return;
        v[id].print();
        if(other==v[id])exit(0);
        if(v[id]==myTar)exit(0);
        other.read();
    }
    inline void print(){
        print(this->head);
    }

    inline int bfs(Point S,Point T){
        this->clear();
        this->push(S,0,0);
        while(head<=tail){
            Point x=v[head];
            int s=step[head];
            if(x==T)return s;
            for(int i=0;i<8;i++){
                Point nxt=x.to(i);
                if(nxt.x<1||nxt.x>n||nxt.y<1||nxt.y>m)continue;
                if(vis[nxt.x][nxt.y])continue;
                this->push(nxt,head,s+1);
            }
            this->pop();
        }
        assert(false);
    }
}QW,QB,QWB,QBW,Qtar;

int main(){
    cin>>n>>m;
    tarW={n/2,m/2},tarB={n/2+1,m/2};
    W.read(),B.read();
    int wdis=QW.bfs(W,tarW);
    int bdis=QB.bfs(B,tarB);
    int wbdis=QWB.bfs(W,tarB);
    int bwdis=QBW.bfs(B,tarW);
    if(W.type()!=B.type()){
        // It means that only white can eat black
        if(wdis<=bdis){
            chooseWhite();
            QW.print();
            return 0;
        }
        if(wbdis<=bdis+1){
            chooseWhite();
            QWB.print();
            if(other.isOnlyOneStepTo(tarB))other.print();
            else{
                Qtar.bfs(tarB,tarW);
                Qtar.print();
            }
            return 0;
        }
        chooseBlack();
        other.read();
        QB.print();
    }
    else{
        // It means that only black can eat white
        if(bdis<wdis){
            chooseBlack();
            other.read();
            QB.print();
            return 0;
        }
        if(bwdis<=wdis){
            chooseBlack();
            other.read();
            QBW.print();
            if(other.isOnlyOneStepTo(tarW))other.print();
            else{
                Qtar.bfs(tarW,tarB);
                Qtar.print();
            }
            return 0;
        }
        chooseWhite();
        QW.print();
    }
    return 0;
}
