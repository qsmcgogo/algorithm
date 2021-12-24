/*
author:比那名居的桃子
输入一个正整数n，打印规模为n的圣诞树。
*/

#include<bits/stdc++.h>
using namespace std;
char out[3333][3333];
void gao(int n,int x,int y){
    if(n==1){
        out[x][y+2]=out[x+1][y+1]=out[x+1][y+3]=out[x+2][y]=out[x+2][y+2]=out[x+2][y+4]='*';
        return;
    }
    int sz=3*(1<<(n-2));
    gao(n-1,x,y+sz);
    gao(n-1,x+sz,y);
    gao(n-1,x+sz,y+2*sz);
}
int main(){
    int i,j;
    for(i=0;i<3e3;i++){
        for(j=0;j<3e3;j++)out[i][j]=' ';
        out[i][j]='\0';
    }
    int n;
    cin>>n;
    gao(n,0,0);
    for(i=0;i<3*1<<(n-1);i++){
        for(j=3e3-2;j>=0;j--){
            if(out[i][j]!=' ')break;
        }
        out[i][j+1]='\0';
        cout<<out[i]<<'\n';
    }
    for(i=0;i<n;i++){
        for(j=0;j<3*(1<<(n-1))-1;j++)cout<<" ";
        cout<<"*\n";
    }

}
