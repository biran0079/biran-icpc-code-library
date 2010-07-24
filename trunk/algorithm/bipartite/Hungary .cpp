#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;
const int maxn=120;
vector<int> g[maxn];
int link_from[maxn];
bool in[maxn];
int node_num;	//number of nodes on the left side
bool find(int x){
	for(int k=0;k<g[x].size();k++){
		int i=g[x][k];
		if(!in[i]){
			in[i]=true;
			if(link_from[i]==-1 || find(link_from[i])){
				link_from[i]=x;
				return true;                                 
			}        

		}        
	}
	return false;  
}
int max_match(){
	int res=0;
	memset(link_from,-1,sizeof(link_from));
	for(int i=0;i<node_num;i++){  
		memset(in,false,sizeof(in));  
		if(find(i))
			res++;
	}
	return res;
}
