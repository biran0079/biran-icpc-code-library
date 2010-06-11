/*
 *	PKU1144
 * */
#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
const int maxn=110;
struct edge{
	int v;
	edge* next;
	edge(int v,edge* n):v(v),next(n){}
}*E[maxn];
char s[1000];
int ans,ct,num[maxn],low[maxn],vis[maxn];
void dfs(int u,int father){
	vis[u]=1;
	num[u]=low[u]=ct++;
	int v,son=0;
	bool cut=0;
	for(edge *e=E[u];e;e=e->next){
		v=e->v;
		if(v==father)continue;
		if(vis[v]==0){
			son++;
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if(father==-1 && son>1)cut=1;
			if(father!=-1 && low[v]>=num[u])cut=1;
		}else if(vis[v]==1){
			low[u]=min(low[u],num[v]);
		}
	}
	if(cut)ans++;
	vis[u]=2;
}
int main(){
	int n,u,v;
	while(1){
		cin>>n;
		if(n==0)break;
		memset(E,0,sizeof(E));
		while(1){
			gets(s);
			while(!s[0])gets(s);
			char *str=strtok(s," ");
			sscanf(str,"%d",&u);
			if(u==0)break;
			for(str=strtok(0," ");str;str=strtok(0," ")){
				sscanf(str,"%d",&v);
				E[u]=new edge(v,E[u]);
				E[v]=new edge(u,E[v]);
			}
		}
		memset(vis,0,sizeof(vis));
		ans=0;ct=0;
		for(int i=1;i<=n;i++)
			if(!vis[i])
				dfs(i,-1);
		cout<<ans<<endl;
	}
	return 0;
}
