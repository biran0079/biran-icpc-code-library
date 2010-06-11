/*
 *	pass:pku1113
 * */
#include<stdio.h>
#include<math.h>
#include<vector>
#include<algorithm>
#define sqr(x) ((x)*(x))
using namespace std;
const double PI = 3.1415926535897932,EPI=1e-6;
const int maxn=50000;
struct vertex{
	int x,y;
	double angle;
	vertex(int _x,int _y):x(_x),y(_y){}     
	inline double set_angle(vertex &b){
		angle=atan2(y-b.y,x-b.x);       
	}
};
inline bool ccw(vertex &a,vertex &b,vertex &c){
	return a.x*b.y+b.x*c.y+c.x*a.y-a.y*b.x-b.y*c.x-c.y*a.x>0;     
}
inline double dis(vertex &a,vertex &b){
	return  sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));     
}
inline bool cmp( const vertex &a, const vertex &b){

	if(a.angle!=b.angle)
		return a.angle<b.angle;
	else 
		return a.x<b.x;
} 
struct convex_hall{
	vector<vertex> V;  
	int *CH;
	int top;   
	convex_hall(){
		CH=new int[maxn];
		top=0;
	}   
	inline void add_vertex(int a,int b){
		vertex t(a,b);
		V.push_back(t);       
	}
	inline void push(int n){
		CH[top++]=n; 
	}
	inline int pop(){
		return CH[--top];    
	}
	inline vertex& first_top(){
		return  V[CH[top-1]];       
	}
	inline vertex& second_top(){
		return  V[CH[top-2]];       
	}    
	void find_convex_hall(){
		for(int i=1;i<V.size();i++)
			if(V[i].y<V[0].y || (V[i].y==V[0].y && V[i].x<V[0].x))
				swap(V[0],V[i]);
		V[0].angle=-10; 
		for(int i=1;i<V.size();i++)
			V[i].set_angle(V[0]);
		sort(V.begin(),V.end(),cmp);
		push(0);
		push(1);
		push(2);
		for(int i=3;i<V.size();i++){
			while(top>1 && !ccw(second_top(),first_top(),V[i])) 
				pop();
			push(i);
		}
	}
	double perimeter(){
		double res=dis(V[CH[0]],V[CH[top-1]]);
		for(int i=0;i<top-1;i++)
			res+=dis(V[CH[i]],V[CH[i+1]]);
		return res;
	}
	double diameter(){
		push(0);
		int p=0,q=0,predis=0;
		double tangent[maxn],res=0;
		for(int i=0;i<top-1;i++){
			tangent[i]=atan2(V[CH[i+1]].y-V[CH[i]].y-EPI,V[CH[i+1]].x-V[CH[i]].x);
			if(tangent[i]+EPI<0)tangent[i]+=PI;
		}
		for(int i=1;i<top-1;i++)
			if(V[CH[i]].y>V[CH[q]].y)
				q=i;
		while(q!=top){
			res=max(res,dis(V[CH[p]],V[CH[q]]));
			if(tangent[p]<tangent[q])p++;
			else q++;                
		}
		pop();
		return res;
	}
}HALL;    
int main(){
	int n,a,b;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&a,&b);
		HALL.add_vertex(a,b);        
	}   
	HALL.find_convex_hall();
	double ans=HALL.diameter();
	printf("%d\n",(int)(sqr(ans)+EPI));
	return 0;
}

