/*
 *	for fun again
 * */
#include<iostream>
#include<stdio.h>
using namespace std;
template<class T,class K>
struct KDTree{
	struct node{
		T a;
		K b;
		node *left,*right;
		bool del;
		node():del(0){}
	};
	node *root,*null;
	node *data;
	int alloc;
	KDTree(){
		data=new node[1000000];
		null=new node;
		null->left=null->right=null;
		root=null;
		alloc=0;
	}
	void clear(){
		root=null;
		alloc=0;
	}
	node* new_node(const T& a,const T& b){
		node* res=&data[alloc++];
		res->left=res->right=null;
		res->a=a;
		res->b=b;
		return res;
	}
	void insert(const T& a,const K& b){
		insert(root,a,b,1);
	}
	void remove(const T& a,const K& b){
		remove(root,a,b,1);
	}
	void query(const T& a1,const T& a2,const K& b1,const K& b2){
		query(root,a1,a2,b1,b2,1);
	}
	void insert(node* &cur,const T& a,const K& b,int level){
		if(cur==null)cur=new_node(a,b);
		else if(level & 1){
			if(a < cur->a){
				insert(cur->left,a,b,1-level);
			}else{
				insert(cur->right,a,b,1-level);
			}
		}else{
			if(b < cur->b){
				insert(cur->left,a,b,1-level);
			}else{
				insert(cur->right,a,b,1-level);
			}
		}
	}
	void remove(node* &cur,const T& a,const K& b,int level){
		if(cur==null)return;
		else if(level & 1){
			if(a < cur->a){
				remove(cur->left,a,b,1-level);
			}else if(cur->a < a){
				remove(cur->right,a,b,1-level);
			}else{
				cur->del=1;
			}
		}else{
			if(b < cur->b){
				remove(cur->left,a,b,1-level);
			}else if(cur->b < b){
				remove(cur->right,a,b,1-level);
			}else{
				cur->del=1;
			}
		}
	}
	void query(node* &cur,const T& a1,const T& a2,const K& b1,const K& b2,int level){
		if(cur==null)return ;
		if(!cur->del && a1 <= cur->a && cur->a <=a2 && b1 <= cur->b && cur->b <= b2){
			cout<<cur->a<<" "<<cur->b<<endl;
		}
		if(level & 1){
			if(a1 <= cur->a)query(cur->left,a1,a2,b1,b2,1-level);
			if(cur->a <= a2)query(cur->right,a1,a2,b1,b2,1-level);
		}else{
			if(b1 <= cur->b)query(cur->left,a1,a2,b1,b2,1-level);
			if(cur->b <= b2)query(cur->right,a1,a2,b1,b2,1-level);
		}
	}
};
int main(){
	KDTree<int,int> tree;
	for(int i=0;i<100;i++)
		for(int j=0;j<100;j++)
			tree.insert(i,j);
	tree.query(10,20,30,40);
	return 0;
}
