#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<time.h>
using namespace std;
const int MAXN=10000000;
int rank[MAXN],H;
struct SuffixArray{
	int i;
	bool operator<(const SuffixArray &x)const{
		if(rank[i]!=rank[x.i])return rank[i]<rank[x.i];
		return rank[i+H]<rank[x.i+H];
	}
	bool operator==(const SuffixArray &x)const{
		return rank[i]==rank[x.i] && rank[i+H]==rank[x.i+H];
	}
} SA[MAXN];
char s[MAXN];
void build_SA(char *s,SuffixArray* SA){
	vector<int> ct[128];
	int len=strlen(s);
	for(int i=0;i<=len;i++)ct[s[i]].push_back(i);
	int N=0;
	for(int i=0;i<128;i++){
		for(int j=0;j<ct[i].size();j++){
			rank[ct[i][j]]=i;
			SA[N++].i=ct[i][j];
		}
	}
	int* trank=new int[N];	//comparison need to use rank. cannot update inplace
	for(H=1;;H*=2){
		int p=0;
		for(int i=1;i<N;i++){
			if(rank[SA[i].i]!=rank[SA[i-1].i]){
				sort(SA+p,SA+i);
				p=i;
			}
		}
		sort(SA+p,SA+N);
		//stable_sort(SA,SA+N);
		int rN=0;
		for(int i=0;i<N;i++){
			if(i && SA[i]==SA[i-1]){
				trank[SA[i].i]=trank[SA[i-1].i];
			}else{
				trank[SA[i].i]=rN++;
			}
		}
		memcpy(rank,trank,N*sizeof(int));
		if(rN==N)break;
	}
	delete[] trank;
}
bool cmp(int i,int j){
	return strcmp(s+i,s+j)<0;
}
int a[MAXN];

int main(){
	time_t st,ed;
	while(gets(s)){
		int len=strlen(s);
		st=clock();
		build_SA(s,SA);
		ed=clock();
		printf("nlog^2n: %.2lf\n",(ed-st)*1.0/CLOCKS_PER_SEC);
	
		st=clock();
		for(int i=0;i<=len;i++)a[i]=i;
		sort(a,a+len+1,cmp);
		ed=clock();
		printf("n^2logn: %.2lf\n",(ed-st)*1.0/CLOCKS_PER_SEC);
		bool pass=true;
		for(int i=0;i<=len;i++)
			if(a[i]!=SA[i].i){
				pass=false;
				break;
			}
		if(pass) printf("result: pass\n\n");
		else printf("result: fail\n\n\n");
	}
	return 0;
}
