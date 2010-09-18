#ifndef __PARING_HEAP__
#define __PARING_HEAP__
#include"PQ.h"
template<class T>
class paring_heap{
	private:
		class node{
			public:
			T key;
			int idx;
			node *child,*left,*right,*parent;
		};
		node* root;
		node* data;
		node** id;
		int alloc_idx;
		node* new_node(){
			return &data[alloc_idx++];
		}
		node* list_cat(node* a,node* b){
			if(!a)return b;
			if(!b)return a;
			node *c=a->left,*d=b->right;
			c->right=d;
			d->left=c;
			a->left=b;
			b->right=a;
			return a;
		}
		node* list_remove(node* y){
			y->parent=0;
			if(y->left==y)return 0;
			node *a=y->left,*b=y->right;
			a->right=b;
			b->left=a;
			y->right=y->left=y;
			return a;
		}
	public:
		typedef pair<T,int> PTI;

		virtual PTI min(){
			return PTI(root->key,root->idx);
		}

		node* merge_pairs(node* a){
			if(!a)return 0;
			if(a->right==a)return a;
			node* b=a->right;
			node* c=list_remove(a);
			c=list_remove(b);
			return merge(merge(a,b),merge_pairs(c));
		}

		virtual int delete_min(){
			int res=root->idx;
			root=merge_pairs(root->child);
			if(root)root->parent=0;
			return res;
		}

		node* merge(node* a,node* b){
			if(!a)return b;
			if(!b)return a;
			if(b->key < a->key)
				swap(a,b);
			a->child=list_cat(a->child,b);
			b->parent=a;
			return a;
		}
		virtual void insert(int i,const T& key){
			id[i]=new_node();
			id[i]->key=key;
			id[i]->idx=i;
			id[i]->child=id[i]->parent=0;
			id[i]->left=id[i]->right=id[i];
			root=merge(root,id[i]);
		}

		virtual void decrease_key(int i,const T& k){
			node *t=id[i],*p=t->parent;
			t->key=k;
			if(p){
				p->child=list_remove(t);
				t->parent=0;
				root=merge(root,t);
			}
		}
		virtual bool empty(){
			return !root;
		}

		paring_heap(int n){
			root=0;
			data=new node[n];
			id=new node*[n];
			alloc_idx=0;
		}
		~paring_heap(){
			delete[] data;
			delete[] id;
		}

};
#endif
