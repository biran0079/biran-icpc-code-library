#include<stdio.h>
inline unsigned int bin_to_gray_code(unsigned int n){
	return n^(n>>1);         
}
inline unsigned int gray_code_to_bin(unsigned int n){
	unsigned int res=n&(1<<31);
	for(int i=30;i>=0;i--)
		res|=((res&(1<<(i+1)))>>1)^(n&(1<<i));
	return res;
}
void print_bit(unsigned int n){
	int i;
	for(i=31;(n & (1<<i))==0;i--); 
	for(;i>=0;i--) (n & (1<<i)) ? putchar('1') : putchar('0');
}
unsigned int bit_code_to_int(char *s){
	unsigned int res=0;
	for(int i=0;s[i];i++)
		res= (s[i]=='1') ? (res<<1)+1 : res<<1;      
	return res;   
}
int main(){
	char s[100];
	while(gets(s)!=NULL)
		print_bit(gray_code_to_bin(bit_code_to_int(s)));
}
