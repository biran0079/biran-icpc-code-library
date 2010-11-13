#include<stdio.h>
//	ua+vb=(a,b)
void extend_euclidean(int a,int b,int& u,int& v){
	if(b==0){
		u=1;
		v=0;
	}else{
		int q=a/b,r=a%b;
		extend_euclidean(b,r,u,v);
		int tv=v;
		v=u-q*v;
		u=tv;
	}
}
//n[i] must be pairwisely relatively prime
int CRT(int* a,int* n,int k){
	int N=1;
	for(int i=0;i<k;i++)
		N*=n[i];
	int u,v,res=0;
	for(int i=0;i<k;i++){
		extend_euclidean(n[i],N/n[i],u,v);
		res+=a[i]*N*v/n[i];
	}
	return res;
}
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
int main(){
	int a[]={2,3,1},b[]={3,4,5};
	printf("%d\n",CRT(a,b,3));
	return 0;
}
