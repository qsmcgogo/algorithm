import sys
sys.setrecursionlimit(250001)
n=int(input())
a=[]
mod=10**9+7
for i in range(n):
    a.append([int(i) for i in input()]+[0])
a.append([0]*888)
fa=[i for i in range(n*n+500)]
kdm=[0]*(n*n+1)
visited=[[False]*(n+510) for i in range(n+510)]
def dfs(x,y):
    global visited
    visited[x][y]=True
    if x>0 and not visited[x-1][y] and a[x-1][y]==1:
        dfs(x-1,y)
    if x<n-1 and not visited[x+1][y] and a[x+1][y]==1:
        dfs(x+1,y)
    if y>0 and not visited[x][y-1] and a[x][y-1]==1:
        dfs(x,y-1)
    if y<n-1 and not visited[x][y+1] and a[x][y+1]==1:
        dfs(x,y+1)
def f(x):
    if fa[x]==x:
        return x
    return f(fa[x])
def inv(x):
    return pow(x,mod-2,mod)
def uni(x,y):
    p,q=f(x),f(y)
    if p!=q:
        if kdm[p]<kdm[q]:
            fa[p]=q
            kdm[q]+=kdm[p]+1
        else:
            fa[q]=p
            kdm[p]+=kdm[q]+1
for i in range(n):
    for j in range(n):
        if j<n-1 and a[i][j]==1 and a[i][j+1]==1:
            uni(i*n+j,i*n+j+1)
        if i<n-1 and a[i][j]==1 and a[i+1][j]==1:
            uni(i*n+j,(i+1)*n+j)
cnt=0
res=1
for i in range(n):
    for j in range(n):
        if a[i][j]==1 and not visited[i][j]:
            cnt+=1
            res=res*(kdm[f(n*i+j)]+1)%mod
            dfs(i,j)
for i in range(1,cnt+1):
    res=res*i%mod
for i in range(int(input())):
    x,y=map(int,input().split())
    if(a[x][y]==1):
        print(res)
    else:
        temp=1
        cnt+=1
        res=res*cnt%mod
        a[x][y]=1
        if x>0 and a[x-1][y]==1 and f(n*(x-1)+y)!=f(n*x+y):
            res=res*inv(kdm[f(n*(x-1)+y)]+1)%mod
            temp+=kdm[f(n*(x-1)+y)]+1
            uni(n*(x-1)+y,n*x+y)
            res=res*inv(cnt)%mod
            cnt-=1
        if x<n-1 and a[x+1][y]==1 and f(n*(x+1)+y)!=f(n*x+y):
            res=res*inv(kdm[f(n*(x+1)+y)]+1)%mod
            temp+=kdm[f(n*(x+1)+y)]+1
            uni(n*(x+1)+y,n*x+y)
            res=res*inv(cnt)%mod
            cnt-=1
        if y>0 and a[x][y-1]==1 and f(n*x+y-1)!=f(n*x+y):
            res=res*inv(kdm[f(n*x+y-1)]+1)%mod
            temp+=kdm[f(n*x+y-1)]+1
            uni(n*x+y-1,n*x+y)
            res=res*inv(cnt)%mod
            cnt-=1
        if y<n-1 and a[x][y+1]==1 and f(n*x+y+1)!=f(n*x+y):
                res=res*inv(kdm[f(n*x+y+1)]+1)%mod
                temp+=kdm[f(n*x+y+1)]+1
                uni(n*x+y+1,n*x+y)
                res=res*inv(cnt)%mod
                cnt-=1
        res=res*temp%mod
        print(res)
        
        


