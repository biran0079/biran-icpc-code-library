//pku 2186.
//tarjan algorithm
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int maxn=11000;
struct edge{
	int v;
	edge* next;
	edge(int v,edge* n):v(v),next(n){}
}*E[maxn];
int vis[maxn];
int low[maxn],stack[maxn],top;
int belong[maxn],compN,out[maxn],num[maxn],ct;
void tarjan(int u){
	low[u]=num[u]=ct++;
	stack[top++]=u;
	vis[u]=1;
	for(edge* e=E[u];e;e=e->next){
		if(0==vis[e->v]){
			tarjan(e->v);
			low[u]=min(low[u],low[e->v]);
		}else if(1==vis[e->v]){
			low[u]=min(low[u],num[e->v]);
		}
	}
	if(low[u]==num[u]){
		do{
			belong[stack[--top]]=compN;
			vis[stack[top]]=2;
		}while(stack[top]!=u);
		compN++;
	}
}
int main(){
	int n,m,a,b;
	cin>>n>>m;
	while(m--){
		cin>>a>>b;
		E[a]=new edge(b,E[a]);
	}
	memset(vis,0,sizeof(vis));
	top=0;compN=0;ct=0;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			tarjan(i);
		}
	}
	memset(out,0,sizeof(out));
	for(int i=1;i<=n;i++){
		for(edge *e=E[i];e;e=e->next){
			if(belong[e->v]!=belong[i])
				out[belong[i]]++;
		}
	}
	int ind_num=0,ans=0,idx;
	for(int i=0;i<compN;i++){
		if(out[i]==0){
			ind_num++;
			idx=i;
		}
	}
	if(ind_num!=1){
		ans=0;
	}else{
		for(int i=1;i<=n;i++)
			if(belong[i]==idx)
				ans++;
	}
	cout<<ans<<endl;
	return 0;
}
