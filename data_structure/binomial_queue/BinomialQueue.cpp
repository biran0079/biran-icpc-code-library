/*
 *	Generally useless for ICPC. Just for fun :)
 * */
#include<vector>
#include<iostream>
#include<stdlib.h>
using namespace std;
template<class T>
struct BinomialTree{
	T value;
	int deg;
	vector<BinomialTree<T>* > *children;
	BinomialTree(const T& v):value(v),deg(0){
		children=new vector<BinomialTree<T>* >;
	}
	void add(BinomialTree<T> *tree){
		if(tree->deg != deg){
			cout<<"different degree"<<endl;
			exit(-1);
		}
		if(tree->value < value){
			swap(value,tree->value);
			swap(children,tree->children);
		}
		children->push_back(tree);
		deg++;
	}
};
template<class T>
BinomialTree<T>* sum(BinomialTree<T>* a,BinomialTree<T>* b,BinomialTree<T>* c){
	if(a && !b && !c){
		return a;
	}if(!a && b && !c){
		return b;
	}if(!a && !b && c){
		return c;
	}if(a && b && c){
		return c;
	}
	return 0;
}
template<class T>
BinomialTree<T>* carry(BinomialTree<T>* a,BinomialTree<T>* b,BinomialTree<T>* c){
	if(a && b && !c){
		a->add(b);
		return a;
	}
	if(a && !b && c){
		a->add(c);
		return a;
	}
	if(!a && b && c){
		b->add(c);
		return b;
	}
	if(a && b && c){
		a->add(b);
		return a;
	}
	return 0;
}
template<class T>
struct BinomialQueue{
	vector<BinomialTree<T>* > *lst;
	BinomialQueue(){
		lst=new vector<BinomialTree<T>* >;
	}
	BinomialQueue(vector<BinomialTree<T>* > *l){
		lst=l;
	}
	void merge(BinomialQueue<T> *q){
		int len=max(lst->size() , q->lst->size());
		lst->resize(len,0);
		q->lst->resize(len,0);
		BinomialTree<T> *a,*b,*c=0;
		for(int i=0;i<len;i++){
			a=lst->at(i);
			b=q->lst->at(i);
			lst->at(i)=sum(a,b,c);
			c=carry(a,b,c);
		}
		if(c)lst->push_back(c);
	}
	void insert(const T& v){
		BinomialQueue<T> q;
		q.lst->push_back(new BinomialTree<T>(v));
		merge(&q);
	}
	T pop(){
		int idx;
		for(idx=0 ; idx < lst->size() && !lst->at(idx) ; idx++);
		if(idx==lst->size()){
			printf("poping an empty queue\n");
			exit(-1);
		}
		for(int i=idx+1;i<lst->size();i++){
			if(lst->at(i) && lst->at(i)->value < lst->at(idx)->value){
				idx=i;
			}
		}
		BinomialTree<T>* m=lst->at(idx);
		lst->at(idx)=0;
		T res=m->value;
		merge(new BinomialQueue<T>(m->children));
		return res;
	}
	void print(){
		for(int i=0;i<lst->size();i++){
			if(lst->at(i))cout<<i<<"("<<lst->at(i)->deg<<") ";
		}
		cout<<endl;
	}
};
void my_sort(int *a, int *b){
	BinomialQueue<int> q;
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
