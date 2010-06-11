#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010,maxk=20;
struct edge{
	int v;
	edge* next;
};
edge *data=new edge[maxn*2],*ptr;
edge *E[maxn];
edge* new_edge(int v,edge* n){
	ptr->v=v;
	ptr->next=n;
	return ptr++;
}
int f[maxn*2][maxk],first[maxn],dep[maxn],ord[maxn],top;
void dfs(int u,int d){
	first[u]=top;
	dep[u]=d;
	ord[top++]=u;
	for(edge* e=E[u];e;e=e->next){
		if(first[e->v]==-1){
			dfs(e->v,d+1);
			ord[top++]=u;
		}
	}
}
int high_bit(int x){
	int res=0,t=1;
	while(t<=x){
		res++;
		t<<=1;
	}
	return res-1;
}
int RMQ(int a,int b){
	if(a>b)swap(a,b);
	int k=high_bit(b-a+1),i=f[a][k],j=f[b-(1<<k)+1][k];
	return dep[i]<dep[j]?i:j;
}
int LCA(int a,int b){
	return RMQ(first[a],first[b]);
}
int in[maxn];
int main(){
	int times;
	scanf("%d",&times);
	while(times--){
		memset(E,0,sizeof(E));
		memset(in,0,sizeof(in));
		ptr=data;
		int n,a,b;
		scanf("%d",&n);
		for(int i=0;i<n-1;i++){
			scanf("%d%d",&a,&b);
			a--;b--;
			in[b]++;
			E[a]=new_edge(b,E[a]);
			E[b]=new_edge(a,E[b]);
		}
		int root;
		for(int i=0;i<n;i++){
			if(in[i]==0){
				root=i;
				break;
			}
		}
		top=0;
		memset(first,-1,sizeof(first));
		dfs(root,0);
		for(int i=0;i<top;i++)
			f[i][0]=ord[i];
		for(int k=1;k<maxk;k++)
			for(int i=0;i+(1<<(k-1))<top;i++){
				a=f[i][k-1];
				b=f[i+(1<<(k-1))][k-1];
				f[i][k]=dep[a]<dep[b]?a:b;
			}
		scanf("%d%d",&a,&b);
		a--;b--;
		printf("%d\n",LCA(a,b)+1);
	}
	return 0;
}
