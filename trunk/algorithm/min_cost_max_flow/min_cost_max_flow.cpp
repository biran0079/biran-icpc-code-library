/*
 *	pass:	pku2516,hdu3488
 * */
#include<stdio.h>
#include<string.h>
#include<queue>
#include<algorithm>
using namespace std;
static const int maxn=110;
int source,sink;
struct edge{
	int i,j,cap,flow,cost;
	edge *back,*next;
	edge(){}
}*E[maxn];
edge *pool=new edge[10000];
int allc_ptr;
edge* new_edge(int i,int j,int cap,int cost,edge* next){
	edge* res=&pool[allc_ptr++];
	res->i=i;
	res->j=j;
	res->cap=cap;
	res->cost=cost;
	res->next=next;
	res->flow=0;
	return res;
}
inline void add_edge(int i,int j,int cap,int cost){
	E[i]=new_edge(i,j,cap,cost,E[i]);
	E[j]=new_edge(j,i,0,-cost,E[j]);
	E[i]->back=E[j];
	E[j]->back=E[i];
}
pair<int,int> SPFA(){
	edge *path[maxn]={0};
	queue<int> Q;
	bool in[maxn]={0};
	int dis[maxn];
	memset(dis,0x11,sizeof(dis));
	Q.push(source);
	dis[source]=0;
	in[source]=true;
	while(!Q.empty()){
		int i=Q.front();
		Q.pop();	
		in[i]=false;		  
		for(edge* e=E[i];e;e=e->next){
			if(e->cap > e->flow && dis[e->j] > dis[e->i] + e->cost){
				dis[e->j] = dis[e->i] + e->cost;	
				path[e->j]=e;	
				if(!in[e->j]){
					Q.push(e->j);	
					in[e->j]=true;	 
				}
			}	  
		}			  				  
	}
	if(!path[sink])	return make_pair(0,0);
	int min_flow=0x11111111,cost=0;
	for(edge* e=path[sink];e;e=path[e->i]){
		min_flow=min(min_flow,e->cap - e->flow);
	}
	for(edge* e=path[sink];e;e=path[e->i]){
		e->flow+=min_flow;
		e->back->flow-=min_flow;
		cost+=min_flow * e->cost;
	}	  
	return make_pair(cost,min_flow);
}
pair<int,int> min_cost_max_flow(){
	int cost=0,flow=0;
	pair<int,int> p;
	while(1){
		p=SPFA();
		if(!p.second)break;
		cost+=p.first;			
		flow+=p.second;
	}
	return make_pair(cost,flow);
}
int need[maxn][maxn],store[maxn][maxn],cost[maxn][maxn][maxn],sum[maxn];
int main(){
	int ans,n,m,k;
	while(1){
		memset(sum,0,sizeof(sum));
		scanf("%d%d%d",&n,&m,&k);
		if(!n)break;
		for(int i=0;i<n;i++){
			for(int j=0;j<k;j++){
				scanf("%d",&need[i][j]);
				sum[j]+=need[i][j];
			}
		}
		for(int i=0;i<m;i++)
			for(int j=0;j<k;j++)
				scanf("%d",&store[i][j]);
		for(int i=0;i<k;i++)
			for(int a=0;a<n;a++)
				for(int b=0;b<m;b++)
					scanf("%d",&cost[i][a][b]);
		ans=0;
		for(int i=0;i<k;i++){
			memset(E,0,sizeof(E));
			allc_ptr=0;
			source=0,sink=n+m+1;
			for(int j=0;j<m;j++)
				add_edge(source,j+1,store[j][i],0);
			for(int j=0;j<n;j++)
				add_edge(j+m+1,sink,need[j][i],0);
			for(int a=0;a<m;a++)
				for(int b=0;b<n;b++)
					add_edge(1+a,1+m+b,0x11111111,cost[i][b][a]);
			pair<int,int> p=min_cost_max_flow();
			if(p.second != sum[i]){
				ans=-1;
				break;
			}else{
				ans+=p.first;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
