//	this implementation is FAST
#include<stdio.h>
#include<assert.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<queue>
#include"BinarySearchTree.h"
using namespace std;

template<class T>
class SplayTree : public BinarySearchTree<T>{
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
		Node* zig(Node* x);
		Node* zag(Node* x);
		Node* splay(const T& x,Node *t);

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
		const T* find(const T& v);
		void printElements();
		void toDot(const char* fileName);
};
template<class T>
const T* SplayTree<T>::find(const T& v){
	if(root==null)return 0;
	root=splay(v,root);
	if(root->value == v)
		return &(root->value);
	return 0;
}
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
	assert(cur!=null);
	while(cur->left != null)
		cur=cur->left;
	return splay(cur->value,cur);
}
template<class T>
typename SplayTree<T>::Node* SplayTree<T>::findMax(Node* cur){
	assert(cur!=null);
	while(cur->right != null)
		cur=cur->left;
	return splay(cur->value,cur);
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
typename SplayTree<T>::Node* SplayTree<T>::zig(SplayTree<T>::Node* k2){
	Node* k1=k2->left;
	k2->left=k1->right;
	k1->right=k2;
	return k1;
}
template<class T>
typename SplayTree<T>::Node* SplayTree<T>::zag(SplayTree<T>::Node* k1){
	Node* k2=k1->right;
	k1->right=k2->left;
	k2->left=k1;
	return k2;
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
typename SplayTree<T>::Node* SplayTree<T>::splay(const T& v,SplayTree<T>::Node* t){
	static Node* header=new Node();
	Node *leftMax=header,*rightMin=header;
	header->left=header->right=null;
	null->value=v;
	while(1){
		if(v < t->value){
			if(v < t->left->value)
				t=zig(t);	
			if(t->left==null)break;
			rightMin->left=t;
			rightMin=t;
			t=t->left;
		}else if(t->value < v){
			if(t->right->value < v)
				t=zag(t);
			if(t->right == null)break;
			leftMax->right=t;
			leftMax=t;
			t=t->right;
		}else break;
	}
	leftMax->right=t->left;
	rightMin->left=t->right;
	t->left=header->right;
	t->right=header->left;
	return t;
}
template<class T>
void SplayTree<T>::insert(const T& v){
	Node* new_node=newNode(v);
	if(root == null)root=new_node;
	else{
		root=splay(v,root);
		Node* cur=root;
		if(v < root->value){
			new_node->left=root->left;
			new_node->right=root;
			root->left=null;
			root=new_node;
		}else if(root->value < v){
			new_node->right=root->right;
			new_node->left=root;
			root->right=null;
			root=new_node;
		}
	}
}
template<class T>
void SplayTree<T>::remove(const T& v){
	root=splay(v,root);
	if(root->value != v)return;
	Node *newTree;
	if(root->left == null){
		newTree=root->right;
	}else{
		newTree=root->left;
		newTree=splay(v,newTree);
		newTree->right=root->right;
	} 
	delete root;
	root=newTree;
}
template<class T>
bool SplayTree<T>::contains(const T& v){
	if(root==null)return false;
	root = splay(v,root);
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
