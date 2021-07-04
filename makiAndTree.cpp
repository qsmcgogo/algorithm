#include<bits/stdc++.h>
using namespace std;
#define ll long long
int fa[111111];     //父亲
int kdm[111111];    //孩子数量
string color;
int f(int x){       //寻找祖先
    if(fa[x]==x)return x;
    return f(fa[x]);
}
void uni(int x,int y){  //连接x点和y点
    int p=f(x),q=f(y);
    if(p!=q){
        if(kdm[p]>kdm[q]){
            fa[q]=p;
            kdm[p]+=kdm[q]+1;
        }
        else{
            fa[p]=q;
            kdm[q]+=kdm[p]+1;
        }
    }
}
ll t[111111];       //统计连通块白点数量
vector<int>g[111111];
ll gao(vector<int>temp){    //temp为黑点的每个相邻白点孩子数量集合
    ll res=0,i;
    ll n=temp.size();
    if(n==0)return 0;
    ll dp[n]={0},sum[n]={0},s=0;
    sum[0]=s=temp[0];
    for(i=0;i<n;i++){
        res+=temp[i];
    }
    for(i=1;i<n;i++){
        sum[i]=s+=temp[i];
    }
    for(i=1;i<n;i++){
        dp[i]=dp[i-1]+temp[i]*sum[i-1];
    }
    return res+dp[n-1];
}
int main(){

    int n,i,j;
    cin>>n>>color;
    for(i=1;i<=n;i++)fa[i]=i;
    for(i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
        if(color[x-1]=='W'&&color[y-1]=='W')
            uni(x,y);
    }
    ll sum=0;
    for(i=1;i<=n;i++)t[i]=kdm[f(i)]+1;
    for(i=1;i<=n;i++){
        if(color[i-1]=='B'){
            vector<int>temp;
            for(j=0;j<g[i].size();j++){
                if(color[g[i][j]-1]=='W')temp.push_back(t[g[i][j]]);    //若相邻点是白点，加入temp
            }
            sum+=gao(temp);

        }
    }
    cout<<sum;
}

