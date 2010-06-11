#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
const int maxn=100010;
struct edge{
	int v;
	edge* next;
} *E[maxn]={0};
edge  *e_pool=new edge[maxn*2];
edge* new_edge(int v,edge* n){
	e_pool->v=v;
	e_pool->next=n;
	return e_pool++;
}
struct q_lst{
	int v,idx;
	q_lst* next;
} *Q[maxn]={0};
q_lst* q_pool=new q_lst[maxn*2];
q_lst* new_q_lst(int i,int v,q_lst *n){
	q_pool->v=v;
	q_pool->idx=i;
	q_pool->next=n;
	return q_pool++;
}
int ct[maxn]={0};
int ans;
int n,m;
int lca[maxn];
bool vis[maxn]={0};
int dp(int u){		//count number of new edges going outside
	vis[u]=1;
	int res=ct[u];
	for(edge* e=E[u];e;e=e->next)
		if(!vis[e->v])
			res+=dp(e->v);
	if(res==1)ans++;
	else if(res==0 && u!=1)ans+=m;
	return res;
}
int color[maxn]={0},p[maxn],ancestor[maxn];
int root(int x){
	return p[x]==x?x:p[x]=root(p[x]);
}
void merge(int i,int j){
	p[root(i)]=root(j);
}
void LCA(int u){
	color[u]=1;
	ancestor[u]=u;
	for(edge* e=E[u];e;e=e->next){
		if(color[e->v]==0){
			LCA(e->v);
			merge(e->v,u);
			ancestor[root(u)]=u;
		}
	}
	color[u]=2;
	for(q_lst *l=Q[u];l;l=l->next){
		if(color[l->v]==2){
			lca[l->idx]=ancestor[root(l->v)];
		}
	}
}
int main(){
	int a,b;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n-1;i++){
		scanf("%d%d",&a,&b);
		E[a]=new_edge(b,E[a]);
		E[b]=new_edge(a,E[b]);
	}
	for(int i=0;i<m;i++){
		scanf("%d%d",&a,&b);
		Q[a]=new_q_lst(i,b,Q[a]);
		Q[b]=new_q_lst(i,a,Q[b]);
		ct[a]++;
		ct[b]++;
	}
	for(int i=1;i<=n;i++)p[i]=i;
	LCA(1);
	for(int i=0;i<m;i++)
		ct[lca[i]]-=2;
	ans=0;
	dp(1);
	printf("%d\n",ans);
	return 0;
}
