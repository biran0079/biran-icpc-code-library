#include<stdio.h>
const int MAXN=1000000;
int p[MAXN];
void KMP(char *str,char *s){	//find s in str
	p[0]=-1;
	for(int i=1,j=-1;s[i];i++){
		while(j>=0 && s[j+1]!=s[i])
			j=p[j];
		if(s[j+1]==s[i])
			j++;
		p[i]=j;
	}
	for(int i=0,j=-1;str[i];i++){
		while(j>=0 && s[j+1]!=str[i])
			j=p[j];
		if(s[j+1]==str[i]){
			j++;
			if(!s[j+1]){
				printf("find matching at %d\n",i-j);
				j=p[j];
			}
		}
	}
}
char str[MAXN],s[MAXN];
int main(){
	while(scanf("%s%s",str,s)!=EOF){
		KMP(str,s);
	}
	return 0;
}
