import java.math.BigInteger;
import java.util.*;

public class Main {
    static int[] f;
    static int[] t;
    static boolean[][] visit;
    static int[][] map;
    static int n;
    static int size = 0;
    static long init = 1;
    static int mod = 1000000007;
    static Map<Integer,Integer> m = new HashMap<>();
    static int find(int x){return x==f[x]?x:(f[x]=find(f[x]));}
    
    static long fastPower(long n,int p)
    {
        long ret = 1;
        while(p!=0)
        {
            if((p&1)==1)ret = (ret*n)%mod;
            n = (n*n)%mod;
            p>>=1;
        }
        return ret;
    }
    
    static void union(int x,int y)
    {
        int X = find(x);
        int Y = find(y);
        if(X==Y)return;
        size-=1;
        f[X] = Y;
        m.remove(X);
        //init/=t[X];init/=t[Y];
        init=(init*fastPower(t[X],mod-2))%mod;init=(init*fastPower(t[Y],mod-2))%mod;
        t[Y]+=t[X];init=(init*t[Y])%mod;
        t[X] = 0;
        //System.out.println(Y+" "+X+" "+t[Y]+" "+t[X]);
        m.put(Y,t[Y]);
    }
    static int[] moveX = new int[]{-1,1,0,0};
    static int[] moveY = new int[]{0,0,1,-1};

    static boolean check(int cx,int cy)
    {
        if(cx>=n||cy>=n||cx<0||cy<0)return false;
        if(map[cx][cy]==0)return false;
        return true;
    }

    static void dfs(int[] point){
        int cx = point[0];
        int cy = point[1];
        int nx,ny;
        visit[cx][cy] = true;
        for(int i=0;i<4;i++)
        {
            nx = cx+moveX[i];ny = cy+moveY[i];
            if(check(nx,ny)==true)
            {
                union(cx*n+cy,nx*n+ny);
                if(visit[nx][ny]==false)dfs(new int[]{nx,ny});
            }
        }
    }

    public static void main(String[] args) {
        Scanner scanner =  new Scanner(System.in);
        long[] pre = new long[250001];
        pre[1] = 1;
        for(int i=2;i<=250000;i++)
            pre[i] = (pre[i-1]*i)%mod;
        n = scanner.nextInt();
        f = new int[n*n+1];
        t = new int[n*n+1];
        visit = new boolean[n][n];
        for(int i=0;i<n*n;i++)f[i]=i;
        scanner.nextLine();
        map = new int[n][n];
        for(int i=0;i<n;i++)
        {
            String s =scanner.nextLine();
            for(int j=0;j<n;j++)
            {
                t[i*n+j] = map[i][j] = s.charAt(j)-'0';
                if(map[i][j]==1)size+=1;
            }
        }

        for(int i =0;i<n;i++)
            for(int j=0;j<n;j++)
                if(map[i][j]==1)
                {
                    int nx,ny;
                    for(int x=0;x<4;x++)
                    {
                        nx = i+moveX[x];
                        ny = j+moveY[x];
                        if(check(nx,ny))
                        {
                            union(i*n+j,nx*n+ny);
                        }
                    }
                }
        //System.out.println(size);

        int q = scanner.nextInt();
        long prev = -1;
        for(int i=0;i<q;i++)
        {
            int x = scanner.nextInt();
            int y = scanner.nextInt();
            if(map[x][y]!=1)
            {
                t[x*n+y] = map[x][y]=1;
                size+=1;
                int nx,ny;
                for(int j=0;j<4;j++)
                {
                    nx = x+moveX[j];ny = y+moveY[j];
                    if(check(nx,ny)==true)
                    {
                    union(x*n+y,nx*n+ny);
                    }
                }
             }
            long ans = init;
            
            ans = (ans*pre[size])%mod;
            //ans = (ans*fastPower(pre[size+1],mod-2))%mod;
            //ans = (ans*fastPower(pre[size+2],mod-2))%mod;
            
            prev = ans;
            System.out.println(ans);


        }
    }
}
