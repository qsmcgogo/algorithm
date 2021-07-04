import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.Stack;

public class Main{

	static class off{
		private int to,next;
		public off(int to,int next) {
			this.next=next;
			this.to=to;
		}
	}
	
	
	static int n;
	static int head[],cent=0;
	static off a[];
	static int num[],fa[];
	static int sum[];
	static boolean vis[];
	static long ans=0;
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		n=sc.nextInt();
		num=new int[n+1];fa=new int[n+1];
		sum=new int[n+1];vis=new boolean[n+1];
		a=new off[n*2+2];head=new int[n+2];
		ArrayList<Integer> d=new ArrayList<>();
		Arrays.fill(head,-1);Arrays.fill(num,1);
		for (int i =1; i<=n; i++) {
			fa[i]=i;
		}
		String s=sc.next();
		for (int i = 0; i <s.length(); i++) {
			char u=s.charAt(i);
			if(u=='W') {
				vis[i+1]=true;
			}else {
				d.add(i+1);
			}
		}
		int x,y;
		for (int i =1; i<n; i++) {
			x=sc.nextInt();y=sc.nextInt();
			add(x,y);if(vis[x]&&vis[y])con(x,y);
		}
		for (int i = 0; i <d.size(); i++) {
			int u=d.get(i);int wo=0;
			int t=0;
			for (int j =head[u]; j!=-1;j=a[j].next) {
				if(!vis[a[j].to]) continue;t++;
				wo=num[find(a[j].to)];
					ans+=(long)(wo*sum[u]);
				sum[u]+=wo;
			}
			ans+=sum[u];
		}
		System.out.println(ans);
	}
	public static void con(int x,int y) {
		int X=find(x);int Y=find(y);
		if(X!=Y) {
			fa[X]=Y;
			num[Y]+=num[X];
		}
	}
	public static int find(int q) {
		if(q!=fa[q]) {
			return fa[q]=find(fa[q]);
		}
		return q;
	}
	public static void add(int x,int y) {
		a[cent]=new off(y,head[x]);
		head[x]=cent++;
		a[cent]=new off(x,head[y]);
		head[y]=cent++;
	}
}
