#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;
static const int maxn=2000;
int node_num;
vector<int> g[maxn]; 
void add_edge(int i,int j){
	g[i].push_back(j);
	g[j].push_back(i);
}   

int  in[maxn];
bool DFS(int i,int flag){
	in[i]=flag;
	for(int k=0;k<g[i].size();k++){
		int j=g[i][k];  
		if(in[j]==flag || (in[j]==-1 && !DFS(j,1^flag)))
			return false;	
	}
	return true;
}
bool is_bipartite(){
	memset(in,-1,sizeof(in));
	for(int i=0;i<node_num;i++)
		if(in[i]==-1 && !DFS(i,0))
			return false;
	return true;		
}
