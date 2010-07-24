#include <cstdio>
#include <cstring>
using namespace std;
const int OO=0x11111111,maxX=50,maxY=2500;
int w[maxX][maxY];
int lx[maxX],ly[maxY];
int linky[maxY];
int visx[maxX],visy[maxY];
int xN,yN;  //xN <= yN
int slack[maxY];
void input(){
	scanf("%d%d",&xN,&yN);
	int t;
	for(int i=0;i<xN;i++)
		for(int j=0;j<yN;j++){
			scanf("%d",&t);
			for(int k=0;k<xN;k++)
				w[i][j+k*yN]=-(k+1)*t;		   
		}
	yN*=xN;
}
bool find(int x){
	visx[x]=true;
	for(int y=0;y<yN;++y){
		if(visy[y])continue;
		int t=lx[x]+ly[y]-w[x][y];
		if(t==0){
			visy[y]=true;
			if(linky[y]==-1||find(linky[y])){
				linky[y]=x;
				return true;
			}
		}
		else slack[y]<?=t;
	}
	return false;
}
int KM(){
	memset(linky,-1,sizeof(linky));
	memset(lx,0,sizeof(lx));
	memset(ly,0,sizeof(ly));
	for(int i=0;i<xN;++i)
		for(int j=0;j<yN;++j)
			lx[i]>?=w[i][j];
	for(int x=0;x<xN;x++){
		while(1){
			memset(visx,0,sizeof(visx));
			memset(visy,0,sizeof(visy));
			memset(slack,0x11,sizeof(slack));
			if(find(x))break;
			int d=OO;
			for(int i=0;i<yN;++i)
				if(!visy[i])
					d<?=slack[i];
			for(int i=0;i<xN;++i){
				if(visx[i])
					lx[i]-=d;
			}
			for(int i=0;i<yN;++i){
				if(visy[i])
					ly[i]+=d;
			}
		}
	}
	int res=0;
	for(int i=0;i<yN;i++)
		if(linky[i]!=-1)
			res+=w[linky[i]][i];		
	return res;
}
