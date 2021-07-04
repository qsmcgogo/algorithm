#include<bits/stdc++.h>
using namespace std;
#define ll long long
int fa[250010];
int kdm[250020];
string a[505];
int n;
int mod=1e9+7;
ll power(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res=res*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return res;
}
ll inv(ll x){
    return power(x,mod-2);
}
int f(int x){
    if(fa[x]==x)return x;
    return f(fa[x]);
}
void uni(int x,int y){
    int p=f(x),q=f(y);
    if(p==q)return;
    if(kdm[p]<kdm[q]){
        fa[p]=q;
        kdm[q]+=kdm[p]+1;
    }
    else {
        fa[q]=p;
        kdm[p]+=kdm[q]+1;
    }
}
int visited[505][505];
void dfs(int x,int y){
    visited[x][y]=1;
    if(x>0&&!visited[x-1][y]&&a[x-1][y]=='1')dfs(x-1,y);
    if(x<n-1&&!visited[x+1][y]&&a[x+1][y]=='1')dfs(x+1,y);
    if(y>0&&!visited[x][y-1]&&a[x][y-1]=='1')dfs(x,y-1);
    if(y<n-1&&!visited[x][y+1]&&a[x][y+1]=='1')dfs(x,y+1);
}

int main(){
   // freopen("10.in","r",stdin);
  //  freopen("10.out","w",stdout);
    int i,j;
    cin>>n;
    for(i=0;i<n;i++)cin>>a[i];
    for(i=0;i<n*n;i++)fa[i]=i;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(j<n-1&&a[i][j]=='1'&&a[i][j+1]=='1'){
                uni(i*n+j,i*n+j+1);
            }
            if(i<n-1&&a[i][j]=='1'&&a[i+1][j]=='1'){
                uni(i*n+j,(i+1)*n+j);
            }
        }
    }
    int cnt=0;
    ll res=1;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(a[i][j]=='1'&&!visited[i][j]){
                cnt++;
           //     cout<<kdm[f(n*i+j)]+1<<endl;
                res=res*(kdm[f(n*i+j)]+1)%mod;
                dfs(i,j);
            }
        }
    }
   // cout<<cnt<<endl;

    for(i=1;i<=cnt;i++)res=res*i%mod;
 //    cerr<<"RES:"<<res<<endl;
    int q;
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        if(a[x][y]=='1'){
            cout<<res<<endl;
        }
        else{
            int temp=1;
            cnt++;
            res=res*cnt%mod;
       //          cerr<<"RES:"<<res<<endl;

            a[x][y]='1';
            if(x>0&&a[x-1][y]=='1'&&f(n*(x-1)+y)!=f(n*x+y)){
                res=res*inv(kdm[f(n*(x-1)+y)]+1)%mod;

                temp+=kdm[f(n*(x-1)+y)]+1;
                uni(n*(x-1)+y,n*x+y);
                res=res*inv(cnt)%mod;
                cnt--;
            }
            //     cerr<<"RES:"<<res<<endl;

            if(x<n-1&&a[x+1][y]=='1'&&f(n*(x+1)+y)!=f(n*x+y)){
                res=res*inv(kdm[f(n*(x+1)+y)]+1)%mod;
             //   cout<<kdm[f(n*(x+1)+y)]+1<<endl;
                temp+=kdm[f(n*(x+1)+y)]+1;
                uni(n*(x+1)+y,n*x+y);
                res=res*inv(cnt)%mod;
                cnt--;
            }
          //       cerr<<"RES:"<<res<<endl;

            if(y>0&&a[x][y-1]=='1'&&f(n*x+y-1)!=f(n*x+y)){
                res=res*inv(kdm[f(n*x+y-1)]+1)%mod;
                temp+=kdm[f(n*x+y-1)]+1;
                uni(n*x+y-1,n*x+y);
                res=res*inv(cnt)%mod;
                cnt--;
            }
         //        cerr<<"RES:"<<res<<endl;

            if(y<n-1&&a[x][y+1]=='1'&&f(n*x+y+1)!=f(n*x+y)){
                res=res*inv(kdm[f(n*x+y+1)]+1)%mod;
                temp+=kdm[f(n*x+y+1)]+1;
                uni(n*x+y+1,n*x+y);
                res=res*inv(cnt)%mod;
                cnt--;
            }
            //  cout<<temp<<" "<<kdm[f(x*n+y)]+1<<endl;
            res=res*temp%mod;
            cout<<res<<endl;
        }
    }
}
