n=int(input())
color=input()
mod=10**9+7
kdm=[0]*(n+5)
fa=[i for i in range(n+50)]
def f(x):
    if fa[x]==x:
        return x
    return f(fa[x])
def uni(x,y):
    p,q=f(x),f(y)
    if p!=q:
        if kdm[p]<kdm[q]:
            fa[p]=q
            kdm[q]+=kdm[p]+1
        else:
            fa[q]=p
            kdm[p]+=kdm[q]+1
t=[0]*(n+5)
g=[[] for i in range(n+5)]
def gao(temp):
    res=0
    n=len(temp)
    if n==0:
        return 0
    dp=[0]*(n+1)
    su=[0]*(n+1)
    s=0
    su[0]=temp[0]
    s=temp[0]
    for i in range(n):
        res+=temp[i]
    for i in range(1,n):
        s+=temp[i]
        su[i]=s
    for i in range(1,n):
        dp[i]=dp[i-1]+temp[i]*su[i-1]
   # print(res,dp[n-1])
    return res+dp[n-1]
for i in range(n-1):
    x,y=map(int,input().split())
    g[x].append(y)
    g[y].append(x)
    if color[x-1]=='W' and color[y-1]=='W':
        uni(x,y)
res=0
for i in range(1,n+1):
    t[i]=kdm[f(i)]+1
for i in range(1,n+1):
    if color[i-1]=='B':
        temp=[]
        for j in g[i]:
            if color[j-1]=='W':
                temp.append(t[j])
       # print(gao(temp))
        res+=gao(temp)
print(res)
