#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100000;
int f[2][maxn],g[2][maxn];
void alignment(char* s1,int l1,char* s2,int l2){
	if(l1==0 || l2==0)return;
	if(l1>1){
		swap(s1,s2);
		swap(l1,l2);
	}
	for(int i=1;i<=l2;i++)
		if(s1[1]==s2[i]){
			printf("%c",s1[1]);
			break;
		}
}
int* forward(char* s1,int n1,char *s2,int n2){
	int cur=0;
	for(int i=0;i<=n2;i++)
		f[cur][i]=0;
	f[1-cur][0]=0;
	for(int i=1;i<=n1;i++){
		cur=1-cur;
		for(int j=1;j<=n2;j++){
			f[cur][j]=
			s1[i]==s2[j]?1+f[1-cur][j-1]:max(f[1-cur][j],f[cur][j-1]);
		}
	}
	return f[cur];
}
int* backward(char* s1,int n1,char *s2,int n2){
	int cur=0;
	for(int i=1;i<=n2+1;i++)
		g[cur][i]=0;
	g[1-cur][n2+1]=0;
	for(int i=n1;i>=1;i--){
		cur=1-cur;
		for(int j=n2;j>=1;j--){
			g[cur][j]=
			s1[i]==s2[j]?1+g[1-cur][j+1]:max(g[1-cur][j],g[cur][j+1]);
		}
	}
	return g[cur];
}
void Hirschberg(char* s1,int n1,char *s2,int n2){	
	//	string index starts from 1;
	if(n1<=1 || n2<=1){
		alignment(s1,n1,s2,n2);
	}else{
		int mid=n1>>1;
		int *left_res=forward(s1,mid,s2,n2);
		int *right_res=backward(s1+mid,n1-mid,s2,n2);
		int max_v=-1,max_i=0;
		for(int i=0;i<=n2;i++){
			if(left_res[i]+right_res[i+1]>max_v){
				max_v=left_res[i]+right_res[i+1];
				max_i=i;
			}
		}
		Hirschberg(s1,mid,s2,max_i);
		Hirschberg(s1+mid,n1-mid,s2+max_i,n2-max_i);
	}
}
char s1[maxn],s2[maxn];
int main(){
	clock_t st,ed,cost=0;
	while(scanf("%s%s",s1,s2)!=EOF){
		st=clock();

		Hirschberg(s1-1,strlen(s1),s2-1,strlen(s2));	
		putchar(10);

		ed=clock();
		cost+=(ed-st);
	}
	fprintf(stderr,"HLCS:\t%lf sec\n",1.0*cost/CLOCKS_PER_SEC);
	return 0;
}
