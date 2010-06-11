/*
 *	pku3648
 * */
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<sstream>
using namespace std;
const int maxn=100;
struct edge{
	int v;
	edge* next;
	edge(int v,edge* n):v(v),next(n){}
}*E1[maxn],*E2[maxn];
int n,m;
int get_idx(string& s){
	stringstream str;
	int a;
	char b;
	str<<s;
	str>>a>>b;
	return b=='w'?a*2:a*2+1;
}
string get_str(int idx){
	stringstream str;
	str<<idx/2<<((idx&1)?'h':'w');
	return str.str();
}
void add_edge(edge* E[],int u,int v){
	E[u]=new edge(v,E[u]);
}

int stack[maxn],low[maxn],num[maxn],top,ct,N,belong[maxn];
bool instack[maxn],vis[maxn];
int topo[maxn];
void tarjan(edge* E[],int u){
	stack[top++]=u;
	instack[u]=1;
	low[u]=num[u]=ct++;
	vis[u]=1;
	int v;
	for(edge* e=E[u];e;e=e->next){
		v=e->v;
		if(vis[v]==0){
			tarjan(E,v);
			low[u]=min(low[u],low[v]);
		}else if(instack[v]){
			low[u]=min(low[u],num[v]);
		}
	}
	if(low[u]==num[u]){
		do{
			belong[stack[--top]]=N;
			instack[stack[top]]=0;
		}while(stack[top]!=u);
		N++;
	}
}
const int red=0,blue=1;
int color[maxn];
void toposort(edge* E[],int u){
	vis[u]=1;
	for(edge* e=E[u];e;e=e->next){
		if(!vis[e->v]){
			toposort(E,e->v);
		}
	}
	topo[top++]=u;
}
void floodfill(edge* E[],int u){
	color[u]=blue;
	for(edge* e=E[u];e;e=e->next){
		floodfill(E,e->v);
	}
}
int main(){
	int a,b;
	string s1,s2;
	while(1){
		cin>>n>>m;
		if(!n && !m)break;
		memset(E1,0,sizeof(E1));
		while(m--){
			cin>>s1>>s2;
			a=get_idx(s1);
			b=get_idx(s2);
			add_edge(E1,a,b^1);
			add_edge(E1,b,a^1);
		}
		add_edge(E1,0,1);
		top=ct=0;
		memset(vis,0,sizeof(vis));
		memset(instack,0,sizeof(instack));
		N=0;
		for(int i=0;i<2*n;i++)
			if(!vis[i])
				tarjan(E1,i);
		bool bad_luck=0;
		for(int i=0;i<2*n;i+=2){
			if(belong[i]==belong[i+1]){
				bad_luck=1;
				break;
			}
		}
		if(bad_luck){
			cout<<"bad luck"<<endl;
		}else{
			memset(E2,0,sizeof(E2));
			for(int i=0;i<2*n;i++){
				a=belong[i];
				for(edge* e=E1[i];e;e=e->next){
					b=belong[e->v];
					if(a!=b){
						add_edge(E2,b,a);
					}
				}
			}
			top=0;
			int oppo[maxn];		//oppo in new graph
			for(int i=0;i<2*n;i+=2){
				a=belong[i];
				b=belong[i+1];
				oppo[a]=b;
				oppo[b]=a;
			}
			memset(vis,0,sizeof(vis));
			for(int i=0;i<N;i++)
				if(!vis[i])
					toposort(E2,i);
			memset(color,-1,sizeof(color));
			for(int i=N-1;i>=0;i--){
				int u=topo[i];
				if(color[u]==-1){
					color[u]=red;
					floodfill(E2,oppo[u]);
				}
			}
			for(int i=2;i<2*n;i+=2){
				if(i>2) cout<<" ";
				if(color[belong[i]]==blue){
					cout<<get_str(i);
				}else{
					cout<<get_str(i+1);
				}
			}
			cout<<endl;
		}
	}
	return 0;
}
