/**
 * @date: 2024.02.14
 * @problem: AT_arc167_e
 * @tags: 构造, 计算几何, 数学, 数论
 */

#include<bits/stdc++.h>
using namespace std;

int T,S;

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&S);
        if(S==2||(S<=7&&(S&1))){
            puts("No");
            continue;
        }
        else{
            puts("Yes");
            if(S&1)printf("0 0 3 1 %d %d\n",(S-3)/2,(S-1)/2);
            else printf("0 0 2 0 %d %d\n",S/2,S/2);
        }
    }
    return 0;
}
