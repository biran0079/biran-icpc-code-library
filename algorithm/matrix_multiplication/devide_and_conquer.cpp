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
	Matrix<T> naive_mul(const Matrix<T>& t){
		assert(m==t.n);
		Matrix<T> res(n,t.m);
		for(int i=0;i<n;i++)
			for(int j=0;j<t.m;j++)
				for(int k=0;k<m;k++)
					res.a[i][j]+=(*this)(i,k)*t(k,j);
		return res;
	}
	Matrix<T> operator*(const Matrix<T>& t){
		assert(m==t.n);
		if(n<=60 || m<=60)return naive_mul(t);

		int pn=n,pm=m,pk=t.m;
		int N=n%2==0?n:n+1,M=m%2==0?m:m+1,K=t.m%2==0?t.m:t.m+1;
		Matrix<T> res(N,K);

		Matrix<T> A11=sub_matrix(0,0,N/2,M/2),
			A12=sub_matrix(0,M/2,N/2,M/2),
			A21=sub_matrix(N/2,0,N/2,M/2),
			A22=sub_matrix(N/2,M/2,N/2,M/2);
		Matrix<T> B11=t.sub_matrix(0,0,M/2,K/2),
			B12=t.sub_matrix(0,K/2,M/2,K/2),
			B21=t.sub_matrix(M/2,0,M/2,K/2),
			B22=t.sub_matrix(M/2,K/2,M/2,K/2);
		Matrix<T> P1=A11*(B12-B22),
			P2=(A11+A12)*B22,
			P3=(A21+A22)*B11,
			P4=A22*(B21-B11),
			P5=(A11+A22)*(B11+B22),
			P6=(A12-A22)*(B21+B22),
			P7=(A11-A21)*(B11+B12);
		Matrix<T> C11=P5+P4-P2+P6,
			C12=P1+P2,
			C21=P3+P4,
			C22=P5+P1-P3-P7;
		res.set_value(0,0,C11);
		res.set_value(0,K/2,C12);
		res.set_value(N/2,0,C21);
		res.set_value(N/2,K/2,C22);
		res.resize(pn,pk);
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
