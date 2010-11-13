#include<stdio.h>
#include<string.h>
#include<math.h>
#include<vector>
const int SIZE=10000;
bool prime[SIZE];
using namespace std;
vector<int> primes;
void seive(){
	memset(prime,true,sizeof(prime));
	prime[0]=prime[1]=false;
	int k=2;
	while(k<SIZE)
	{
		for(int i=2*k;i<SIZE;i+=k)
			prime[i]=false;
		k++;while(k<SIZE && !prime[k])k++;             
	}
	for(int i=2;i<SIZE;i++)if(prime[i])primes.push_back(i); 
}
bool isprime(int n){
	if(n<SIZE)return prime[n];
	int bound=(int)(sqrt(n)+0.00001);  
	for(int i=0;primes[i]<=bound;i++)
		if(n%primes[i]==0)
			return false;     
	return true;
}
int expmod(int a,int k,int m){  //a^k mod m
	if(k==0)return 1;
	unsigned long long t=expmod(a,k>>1,m);
	if(k&1)return t*t*a%m;
	else return t*t%m;   
}
bool fermat_prime_test(int n){
	if(n<=1)return false;
	int a;
	const int s=3;
	for(int i=0;i<s;i++){
		a=rand()%(n-1)+1;  
		if(expmod(a,n-1,n)!=1)
			return false; 
	}
	return true;
}
int main(){
	seive();
	int y=0,n=0,t;
	srand(19203);
	for(int i=0;i<1000000;i++){
		t=rand();
		if(fermat_prime_test(t)==isprime(t))y++;
		else n++;  
	}
	printf("%d %d\n%lf\n",y,n,(double)y/(y+n));
	return 0;
}

