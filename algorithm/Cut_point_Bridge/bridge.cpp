/*
 *	PKU3177
 * */
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=11000;
struct edge{
	int v;
	bool vis,bridge;
	edge *next,*back;
	edge(int v,edge* n):v(v),next(n),vis(0){}
}*E[maxn]={0};
int vis[maxn]={0},num[maxn],low[maxn],ct=0;
int p[maxn];
int root(int x){return p[x]==x?x:p[x]=root(p[x]);}
void dfs(int u){
	low[u]=num[u]=ct++;
	vis[u]=1;
	int v;
	for(edge* e=E[u];e;e=e->next){
		if(e->vis)continue;
		e->vis=e->back->vis=1;
		v=e->v;
		if(vis[v]==0){
			dfs(v);
			low[u]=min(low[u],low[v]);
			if(!(low[v]>num[u])){	//is not a bridge
				p[root(u)]=root(v);
			}
		}else if(vis[v]==1){
			low[u]=min(low[u],num[v]);
		}
	}
	vis[u]=2;
}
int deg[maxn]={0};
int main(){
	int n,m,a,b;
	cin>>n>>m;
	while(m--){
		cin>>a>>b;
		E[a]=new edge(b,E[a]);
		E[b]=new edge(a,E[b]);
		E[a]->back=E[b];
		E[b]->back=E[a];
	}
	for(int i=1;i<=n;i++)p[i]=i;
	dfs(1);
	for(int i=1;i<=n;i++){
		a=root(i);
		for(edge* e=E[i];e;e=e->next){
			b=root(e->v);
			if(a!=b){
				deg[a]++;
				deg[b]++;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(root(i)==i){
			deg[i]/=2;	//each edge count twice
			if(deg[i]==1)ans++;
		}
	}
	cout<<(ans+1)/2<<endl;
	return 0;
}
