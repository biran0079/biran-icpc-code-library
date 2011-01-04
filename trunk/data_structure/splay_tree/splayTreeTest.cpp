#include"TopDownSplay.h"
#include"BinarySearchTree.h"
#include"assert.h"
#include<time.h>
#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;
const int maxn=1000000;
void test(BinarySearchTree<int> &tree,const string& name){
	//	only test for intener type
	cout<<"Testing "<<name<<":"<<endl;
	clock_t st,ed;
	st=clock();
	cout<<"inserting elements"<<endl;
	for(int i=0;i<maxn;i+=2)
		tree.insert(i);
	cout<<"check contains"<<endl;
	for(int i=0;i<maxn;i++){
		if(i % 2 == 0)
			assert(tree.contains(i));
		else
			assert(!tree.contains(i));
	}
	cout<<"removing elements"<<endl;
	for(int i=0;i<maxn;i+=4)
		tree.remove(i);
	cout<<"check contains"<<endl;
	for(int i=0;i<maxn;i++)
		if(i % 2 == 0 && i % 4 !=0)
			assert(tree.contains(i));
		else
			assert(!tree.contains(i));
	tree.clear();
	cout<<"check contains"<<endl;
	for(int i=0;i<maxn;i++)
		assert(!tree.contains(i));
	ed=clock();
	cout<<name<<" time cost: "<<1.0*(ed-st)/CLOCKS_PER_SEC<<endl<<endl;
}
int main(){
	SplayTree<int> splay;
	test(splay,"splay tree");
	return 0;
}

