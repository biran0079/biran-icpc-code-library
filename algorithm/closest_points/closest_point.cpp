#include<vector>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define EPI 0.000001

using namespace std;
const int maxn=100000;
struct point{
	double x,y;
	int ID;
	point(double _x,double _y,int _ID):x(_x),y(_y),ID(_ID){}    
	point(){}    
};
typedef const point* PP;


inline double Distance(const point &a,const point &b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline double min(double a,double b){
	return a<b?a:b;
}
inline bool within_strip(const point &a,double mid,double delta){
	return a.x>mid-delta && a.x<mid+delta;       
}

void merge_points(PP A[], PP tem[],int left,int mid,int right){
	int i=left,j=mid+1,k=left;
	while(i<mid+1 && j<right+1){
		if(A[i]->y < A[j]->y) 
			tem[k++]=A[i++];
		else
			tem[k++]=A[j++];             
	}    
	while(i<mid+1)    tem[k++]=A[i++]; 
	while(j<right+1)  tem[k++]=A[j++];      
	for(int i=left;i<=right;i++)A[i]=tem[i];
}
double strip_min(PP A[],int left,int right,double mid_x,double delta){
	double res=1e200;
	for(int i=left;i<=right;i++)
		if(within_strip(*A[i],mid_x,delta)){
			for(int j=i+1;j<=right;j++)
				if(A[j]->y - A[i]->y>delta)
					break;
				else 
					res=min(res,Distance(*A[i],*A[j]));                                   
		}
	return res;
}
double sub_closest_points(PP A[],PP tem[],int left,int right){
	if(right<=left)return 1e200;       

	int mid=(left+right)>>1;
	double mid_x=A[mid]->x;
	double min1=sub_closest_points(A,tem,left,mid);        
	double min2=sub_closest_points(A,tem,mid+1,right);
	double delta=min(min1,min2);              
	merge_points(A,tem,left,mid,right);       
	return min(delta,strip_min(A,left,right,mid_x,delta));
}
inline bool compareX(const PP &a,const PP &b){
	return a->x < b->x; 
}
double closest_points(const vector<point> &points){
	PP *A=new PP[points.size()],
	   *tem=new PP[points.size()];
	for(int i=0;i<points.size();i++)
		A[i]=&points[i];
	sort(A,A+points.size(),compareX);
	return sub_closest_points(A,tem,0,points.size()-1);
}

int main(){
	vector<point> points;
	int n;
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int ac=0,wa=0;
	while(scanf("%d",&n)!=EOF){
		double x,y;
		points.clear();
		for(int i=0;i<n;i++){
			scanf("%lf%lf",&x,&y);    
			points.push_back(point(x,y,i));   
		}              
		time_start();
		double ans1=closest_points(points); 
		printf("VER2: ");time_end();
		printf("\n");
	}
}
