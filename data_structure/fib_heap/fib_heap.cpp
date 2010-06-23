/*
 *	fib heap. Decrease Key not implemented.
 *	Useless for ICPC, for fun again : )
 * */
#include<list>
#include<algorithm>
#include<stdlib.h>
using namespace std;
const int max_deg=20;
template<class T>
struct Tree{
	T value;
	int deg;
	list<Tree<T>*> children;
	Tree(const T& v):value(v),deg(0){}
	void merge(Tree<T>* tree){
		if(tree->deg != deg){
			printf("different degree\n");
			exit(-1);
		}
		if(tree->value < value){
			swap(this->value,tree->value);
			children.swap(tree->children);
		}
		children.push_back(tree);
		deg++;
	}
};
template<class T>
struct FibHeap{
	typedef typename list<Tree<T>*>::iterator LI;
	list<Tree<T>*> lst;
	LI min_it;
	FibHeap(){
		min_it=lst.end();
	}
	void insert(const T& v){
		Tree<T>* tree=new Tree<T>(v);
		lst.push_front(tree);
		if(lst.end()==min_it || tree->value < (*min_it)->value){
			min_it=lst.begin();
		}
	}
	T pop(){
		if(lst.end() == min_it){
			printf("Poping an empty heap\n");
			exit(-1);
		}
		Tree<T>* tree=*min_it;
		lst.erase(min_it);
		T res=tree->value;
		lst.insert(lst.begin(),tree->children.begin(),tree->children.end());
		LI ct[max_deg];
		int d;
		for(int i=0;i<max_deg;i++){
			ct[i]=lst.end();
		}
		for(LI it=lst.begin();it!=lst.end();it++){
			d=(*it)->deg;	
			if(lst.end()==ct[d]){
				ct[d]=it;
			}else{
				tree=*it;
				do{
					tree->merge(*ct[d]);
					lst.erase(ct[d]);
					ct[d]=lst.end();
					d++;
				}while(ct[d]!=lst.end());
				ct[d]=it;
			}
		}
		min_it=lst.begin();
		for(LI it=lst.begin();it!=lst.end();it++){
			if((*it)->value < (*min_it)->value){
				min_it=it;
			}
		}
		return res;
	}
	void print(){
		for(LI it=lst.begin();it!=lst.end();it++)
			printf("%d ",(*it)->deg);
		putchar(10);
	}
};
void my_sort(int *a, int *b){
	FibHeap<int> q;
	for(int* t=a;t!=b;t++){
		q.insert(*t);
	}
	for(int* t=a;t!=b;t++){
		*t=q.pop();
	}
}
const int maxn=100000;
int a[maxn],b[maxn];
int main(){
	for(int i=0;i<maxn;i++){
		a[i]=b[i]=rand();
	}
	printf("my_sort begins\n");
	my_sort(a,a+maxn);
	printf("my_sort ends\n\n");
	printf("sort begins\n");
	sort(b,b+maxn);
	printf("sort ends\n\n");
	bool AC=1;
	for(int i=0;i<maxn;i++){
		if(a[i]!=b[i]){
			AC=0;
			break;
		}
	}
	puts(AC?"AC":"WA");
	return 0;
}
