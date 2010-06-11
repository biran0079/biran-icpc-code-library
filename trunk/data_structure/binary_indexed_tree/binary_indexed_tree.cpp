/*
 *	pass: pku2352
 * */
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=16000;
struct star{
	int x,y;
	bool operator< (const star& t)const{
		if(x!=t.x)return x<t.x;
		return y<t.y;
	}
}st[maxn];
int a[33000]={0},ans[maxn]={0};
int top;
inline int low_bit(int x){
	return x & (-x);
}
void plus(int x,int m){
	while(x<=top){
		a[x]+=m;
		x+=low_bit(x);
	}
}
int sum(int x){
	int res=0;
	while(x){
		res+=a[x];
		x-=low_bit(x);
	}
	return res;
}
int main(){
	int n;
	scanf("%d",&n);
	top=0;
	for(int i=0;i<n;i++){
		scanf("%d%d",&st[i].x,&st[i].y);
		st[i].x++;
		st[i].y++;
		top=max(top,st[i].y);
	}
	sort(st,st+n);
	for(int i=0;i<n;i++){
		ans[sum(st[i].y)]++;
		plus(st[i].y,1);
	}
	for(int i=0;i<n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
