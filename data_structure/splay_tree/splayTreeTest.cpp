#include"TopDownSplay.h"
#include"treap.h"
#include"assert.h"
#include<time.h>
#include<stdlib.h>
#include<set>
#include<iostream>
using namespace std;
const int maxn=500000;
int main(){
	clock_t st,ed;
/*
	SplayTree<int>* tree=new SplayTree<int>();
	for(int i=0;i<200;i++){
		tree->insert(rand());
		tree->contains(rand());
	}
	tree->toDot("g1.dot");
	*/
	st=clock();
	SplayTree<int>* tree=new SplayTree<int>();
	cout<<"inserting elements"<<endl;
	for(int i=0;i<maxn;i+=2){
		tree->insert(i);
	}
	cout<<"check contains"<<endl;
	for(int i=0;i<maxn;i++){
		if(i % 2 == 0)
			assert(tree->contains(i));
		else
			assert(!tree->contains(i));
	}
	cout<<"removing elements"<<endl;
	for(int i=0;i<maxn;i+=4){
		tree->remove(i);
	}
	cout<<"check contains"<<endl;
	for(int i=0;i<maxn;i++)
		if(i % 2 == 0 && i % 4 !=0)
			assert(tree->contains(i));
		else
			assert(!tree->contains(i));
	tree->clear();
	cout<<"check contains"<<endl;
	for(int i=0;i<maxn;i++)
		assert(!tree->contains(i));
	delete tree;
	cout<<endl<<"PASS"<<endl;
	ed=clock();
	cout<<"splay tree time: "<<1.0*(ed-st)/CLOCKS_PER_SEC<<endl;
	cout<<"**************************"<<endl<<endl;
	

	st=clock();
	Treap<int>* treap=new Treap<int>();
	cout<<"inserting elements"<<endl;
	for(int i=0;i<maxn;i+=2){
		treap->insert(i);
	}
	cout<<"check contains"<<endl;
	for(int i=0;i<maxn;i++){
		if(i % 2 == 0)
			assert(treap->contains(i));
		else
			assert(!treap->contains(i));
	}
	cout<<"removing elements"<<endl;
	for(int i=0;i<maxn;i+=4){
		treap->remove(i);
	}
	cout<<"check contains"<<endl;
	for(int i=0;i<maxn;i++)
		if(i % 2 == 0 && i % 4 !=0)
			assert(treap->contains(i));
		else
			assert(!treap->contains(i));
	treap->clear();
	cout<<"check contains"<<endl;
	for(int i=0;i<maxn;i++)
		assert(!treap->contains(i));
	delete treap;
	cout<<endl<<"PASS"<<endl;
	ed=clock();
	cout<<"treap tree time: "<<1.0*(ed-st)/CLOCKS_PER_SEC<<endl;
	cout<<"**************************"<<endl<<endl;


	st=clock();
	set<int> s;
	cout<<"inserting elements"<<endl;
	for(int i=0;i<maxn;i+=2){
		s.insert(i);
	}
	cout<<"check contains"<<endl;
	for(int i=0;i<maxn;i++){
		if(i % 2 == 0)
			assert(s.find(i)!=s.end());
		else
			assert(s.find(i)==s.end());
	}
	cout<<"removing elements"<<endl;
	for(int i=0;i<maxn;i+=4){
		s.erase(i);
	}
	cout<<"check contains"<<endl;
	for(int i=0;i<maxn;i++)
		if(i % 2 == 0 && i % 4 !=0)
			assert(s.find(i)!=s.end());
		else
			assert(s.find(i)==s.end());
	s.clear();
	cout<<"check contains"<<endl;
	for(int i=0;i<maxn;i++)
		assert(s.find(i)==s.end());
	cout<<endl<<"PASS"<<endl;
	ed=clock();
	cout<<"set time: "<<1.0*(ed-st)/CLOCKS_PER_SEC<<endl;
	cout<<"**************************"<<endl<<endl;
	return 0;
}

