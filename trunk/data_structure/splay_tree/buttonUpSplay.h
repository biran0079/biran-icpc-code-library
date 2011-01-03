//	this implementation is slow
#include<stdio.h>
#include<assert.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<queue>
using namespace std;

template<class T>
class SplayTree{
	private:
		class Node{
		public:
			T value;
			Node* left;
			Node* right;
		};
		Node* root;
		Node* null;

		Node* newNode(const T& v);
		void zig(Node* x,Node* y);
		void zag(Node* x,Node* y);
		void splay(const T& v);
		Node* splayUp(vector<Node*>& path,vector<char>& which);

		Node* findMin(Node* cur);
		Node* findMax(Node* cur);
		void clear(Node* cur);
		void inorder(Node*);
	public:
		SplayTree();
		~SplayTree();
		void clear();
		void insert(const T& x);
		void remove(const T& x);
		const T& findMin();
		const T& findMax();
		bool contains(const T& v);
		void printElements();
		void toDot(const char* fileName);
};
template<class T>
void SplayTree<T>::printElements(){
	cout<<"[ ";
	inorder(root);
	cout<<"]"<<endl;
}
template<class T>
void SplayTree<T>::inorder(SplayTree<T>::Node* cur){
	if(cur==null)return;
	inorder(cur->left);
	cout<<cur->value<<" ";
	inorder(cur->right);
}
template<class T>
typename SplayTree<T>::Node* SplayTree<T>::findMin(Node* cur){
	vector<Node*> path;
	vector<char> which;
	while(cur!=null){
		path.push_back(cur);
		which.push_back('l');
		cur=cur->left;
	}
	return splayUp(path,which);
}
template<class T>
typename SplayTree<T>::Node* SplayTree<T>::findMax(Node* cur){
	vector<Node*> path;
	vector<char> which;
	while(cur!=null){
		path.push_back(cur);
		which.push_back('r');
		cur=cur->right;
	}
	return splayUp(path,which);
}
template<class T>
const T& SplayTree<T>::findMax(){
	root=findMax(root);
	return root->value;
}
template<class T>
const T& SplayTree<T>::findMin(){
	root=findMin(root);
	return root->value;
}
template<class T>
typename SplayTree<T>::Node* SplayTree<T>::newNode(const T& v){
	Node* res=new Node();
	res->value=v;
	res->left=res->right=null;
	return res;
}
template<class T>
void SplayTree<T>::zig(SplayTree<T>::Node* x,SplayTree<T>::Node* y){
	Node* t=x->right;
	x->right=y;
	y->left=t;
}
template<class T>
void SplayTree<T>::zag(SplayTree<T>::Node* x,SplayTree<T>::Node* y){
	Node* t=x->left;
	x->left=y;
	y->right=t;
}
template<class T>
void SplayTree<T>::clear(){
	clear(root);
	root=null;
}
template<class T>
void SplayTree<T>::clear(SplayTree<T>::Node* cur){
	if(cur==null)return;
	queue<Node*> q;
	q.push(cur);
	while(!q.empty()){
		Node* t=q.front();
		q.pop();
		if(t->left!=null)
			q.push(t->left);
		if(t->right!=null)
			q.push(t->right);
		delete t;
	}
	root=null;
}
template<class T>
SplayTree<T>::~SplayTree(){
	clear(root);
	delete null;
}
template<class T>
SplayTree<T>::SplayTree(){
	null=newNode(T());
	null->left=null->right=0;
	root=null;
}
template<class T>
typename SplayTree<T>::Node* SplayTree<T>::splayUp(vector<Node*>& path,vector<char>& which){
	assert(path.size()>0);
	assert(which.size() >= path.size()-1);	//last element for which is not required
	int idx=path.size()-1;
	while(idx >= 2){
		Node *x=path[idx],*y1=path[idx-1],*y2=path[idx-2];
		char cy1=which[idx-1],cy2=which[idx-2];
		if(cy2=='l'){
			if(cy1=='l'){
				zig(y1,y2);
				zig(x,y1);

			}else{
				zag(x,y1);
				y2->left=x;
				zig(x,y2);
			}
		}else{
			if(cy1=='l'){
				zig(x,y1);
				y2->right=x;
				zag(x,y2);
			}else{
				zag(y1,y2);
				zag(x,y1);
			}
		}
		idx-=2;
		path[idx]=x;
		if(idx > 0){
			//	update children of original parent of y2
			if(which[idx-1]=='l')
				path[idx-1]->left=x;
			else
				path[idx-1]->right=x;
		}
	}
	if(idx == 1)
		which[0]=='l' ? zig(path[1],path[0]) : zag(path[1],path[0]);
	return path[idx];
}
template<class T>
void SplayTree<T>::splay(const T& v){
	if(root==null)return;
	vector<Node*> path;
	vector<char> which;
	Node* cur=root;
	//	find the path
	while(cur != null){
		path.push_back(cur);
		if(v < cur->value){
			cur = cur->left;
			which.push_back('l');
		}else if(cur->value < v){
			cur = cur->right;
			which.push_back('r');
		}else break;
	}
	//	splay the last node up to root
	root = splayUp(path,which);
}
template<class T>
void SplayTree<T>::insert(const T& v){
	Node* new_node=newNode(v);
	if(root == null)root=new_node;
	else{
		vector<Node*> path;
		vector<char> which;
		Node* cur=root;
		while(cur!=null){
			path.push_back(cur);
			if(v < cur->value){
				which.push_back('l');
				if(cur->left==null)
					cur->left=new_node;
				cur=cur->left;
			}else if(cur->value < v){
				which.push_back('r');
				if(cur->right==null)
					cur->right=new_node;
				cur=cur->right;
			}else break;	
			//	if has dulplication, then no change to tree, x is splayed to root
			//	else, insert new node into tree, and also splay it to root
		}
		root=splayUp(path,which);
	}
}
template<class T>
void SplayTree<T>::remove(const T& v){
	if(root==null)return;
	splay(v);
	if(root->value != v)return;
	Node *t=root;
	if(root->left == null){
		root=root->right;
	}else{
		root->left=findMax(root->left);
		root->left->right=root->right;
		root=root->left;
	} 
	delete t;
}
template<class T>
bool SplayTree<T>::contains(const T& v){
	if(root==null)return false;
	splay(v);
	return root->value == v;
}
template<class T>
void SplayTree<T>::toDot(const char* fileName){
	ofstream out(fileName);
	assert(!out.fail());
	queue<Node*> q;
	q.push(root);
	out<<"digraph g{"<<endl;
	while(!q.empty()){
		Node* t=q.front();
		q.pop();
		if(t->left!=null){
			q.push(t->left);
			out<<"\t"<<t->value<<" -> "<<t->left->value<<";"<<endl;
		}
		if(t->right!=null){
			q.push(t->right);
			out<<"\t"<<t->value<<" -> "<<t->right->value<<";"<<endl;
		}
	}
	out<<"}"<<endl;
	out.close();
}
