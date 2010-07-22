/*
 *	pass:	pku1273,pku1459,pku2125
 * */
#include <cstdio>
#include <cstring>
#include <climits>
using namespace std;
const int maxn=502,INF=1000000000;
struct edge{
	int x,y;
	int c;	
	int f;
	edge *next,*back;
	edge(){}
	edge(int x,int y,int c,edge* next):x(x),y(y),c(c),f(0),next(next),back(0){}
	void* operator new(size_t, void *p){
		return p;
	}
}*E[maxn];
int source,sink;

int Q[maxn];
int D[maxn];
void BFS(){
	memset(D,-1,sizeof(D));
	int head=0,tail=0;
	Q[tail++]=source;
	D[source]=0;
	for(;;){
		int i=Q[head++];
		for(edge* e=E[i];e;e=e->next){
			if(e->c==0)continue;
			int j=e->y;
			if(D[j]==-1){
				D[j]=D[i]+1;
				Q[tail++]=j;
				if(j==sink)return;
			}
		}
		if(head==tail)break;
	}
}
edge* cur[maxn];
edge* path[maxn];
int max_flow(){
	int res=0;
	int path_n;
	for(;;){
		BFS();
		if(D[sink]==-1)break;
		memcpy(cur,E,sizeof(E));
		path_n=0;
		int i=source;
		for(;;){
			if(i==sink){
				int mink=0;
				int delta=INT_MAX;
				for(int k=0;k<path_n;++k){
					if(path[k]->c < delta){
						delta = path[k]->c;
						mink=k;
					}
				}
				for(int k=0;k<path_n;++k){
					path[k]->c -= delta;
					path[k]->back->c += delta;
				}
				path_n=mink;
				i=path[path_n]->x;
				res+=delta;
			}
			edge* e;
			for(e=cur[i];e;e=e->next){
				if(e->c==0)continue;
				if(D[i]+1==D[e->y])break;
			}
			cur[i]=e;
			if(e){
				path[path_n++]=e;
				i=e->y;
			}else{
				D[i]=-1;
				if(path_n==0)break;
				path_n--;
				i=path[path_n]->x;
			}
		}
	}
	return res;
}
int sum;
edge *pool=new edge[150000],*data;
inline void add_edge(int x,int y,int w){
	E[x]=new((void*)data++) edge(x,y,w,E[x]);
	E[y]=new((void*)data++) edge(y,x,0,E[y]);
	E[x]->back = E[y];
	E[y]->back = E[x];      
}
/*
void builg_graph(){
	memset(E,0,sizeof(E));
	data=pool;
	source=n;
	sink=n+1;
}
*/
int n,np,nc,m;
int main(){	
	int a,b,c;
	while(scanf("%d%d%d%d",&n,&np,&nc,&m)!=EOF){
		memset(E,0,sizeof(E));
		data=pool;
		source=n;
		sink=n+1;
		for(int i=0;i<m;i++){
			while(getchar()!='(');
			scanf("%d",&a);
			while(getchar()!=',');
			scanf("%d",&b);
			while(getchar()!=')');
			scanf("%d",&c);
			add_edge(a,b,c);
		}
		for(int i=0;i<np;i++){
			while(getchar()!='(');
			scanf("%d",&a);
			while(getchar()!=')');
			scanf("%d",&b);
			add_edge(source,a,b);
		}
		for(int i=0;i<nc;i++){
			while(getchar()!='(');
			scanf("%d",&a);
			while(getchar()!=')');
			scanf("%d",&b);
			add_edge(a,sink,b);
		}
		printf("%d\n",max_flow());
	}
}


