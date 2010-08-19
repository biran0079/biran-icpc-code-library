#include<stdio.h>
#include<assert.h>
#include<vector>
#include<algorithm>
#include<time.h>
using namespace std;
template<class T>
struct Matrix{
	int n,m;
	vector<vector<T> > a;
	Matrix(int n,int m):n(n),m(m){
		a.resize(n);
		for(int i=0;i<n;i++)a[i].resize(m);
	}
	Matrix(){
		Matrix(0,0);
	}
	inline T operator()(int i,int j)const{
		return i>=0 && i<n && j>=0 && j<m ? a[i][j]:0;
	}
	Matrix<T> operator+(const Matrix& t){
		assert(n==t.n && m==t.m);
		Matrix<T> res(n,m);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				res.a[i][j]=(*this)(i,j)+t(i,j);
		return res;
	}
	Matrix<T> operator-(const Matrix& t){
		assert(n==t.n && m==t.m);
		Matrix<T> res(n,m);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				res.a[i][j]=(*this)(i,j)-t(i,j);
		return res;
	}
	void resize(int N,int M){
		n=N;
		m=M;
		a.resize(N);
		for(int i=0;i<N;i++)a[i].resize(M);
	}
	Matrix<T> sub_matrix(int x,int y,int N,int M)const{
		assert(N<=n && M<=m);
		Matrix<T> res(N,M);
		for(int i=0;i<N;i++)
			for(int j=0;j<M;j++)
				res.a[i][j]=(*this)(x+i,y+j);
		return res;
	}
	void set_value(int x,int y,const Matrix<T>& t){
		assert(x>=0 && y>=0 && x+t.n<=n && y+t.m<=m);
		for(int i=0;i<t.n;i++)
			for(int j=0;j<t.m;j++)
				a[i+x][j+y]=t(i,j);
	}
	Matrix<T> operator*(const Matrix<T>& t){
		assert(m==t.n);
		Matrix<T> res(n,t.m);
		for(int i=0;i<n;i++)
			for(int j=0;j<t.m;j++)
				for(int k=0;k<m;k++)
					res.a[i][j]+=(*this)(i,k)*t(k,j);
		return res;
	}
	void print(){
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++)
				printf("%d ",a[i][j]);
			putchar(10);
		}
	}
};
int main(){
	Matrix<int> a,b;
	int n,m,t;
	clock_t tot=0,st,ed;
	while(1){
		scanf("%d%d",&n,&m);
		if(n==0)break;
		a.resize(n,m);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				scanf("%d",&t);
				a.a[i][j]=t;
			}
		scanf("%d%d",&n,&m);
		b.resize(n,m);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				scanf("%d",&t);
				b.a[i][j]=t;
			}
		st=clock();
		Matrix<int> c=(a*b);
		ed=clock();
		tot+=ed-st;
		c.print();
	}
	printf("Time : %.2lf sec\n",1.0*tot/CLOCKS_PER_SEC);
	return 0;
}

