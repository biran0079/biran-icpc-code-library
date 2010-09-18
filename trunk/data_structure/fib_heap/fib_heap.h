#ifndef __FIB_HEAP__
#define __FIB_HEAP__
#include"PQ.h"
template<class T>
class fib_heap : public PQ<T>{
	private:
		typedef pair<T,int> PTI;
		class node{
			public:
				int idx;
				int degree;
				T key;
				node *left,*right,*child,*parent;
				bool mark;
		};
		PTI* h;
		node** id;
		node* data;
		node *head,*min_node;
		int alloc_idx;
		int N;			//	number of trees
		node** in;		//	table for concatenating after deletion
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
		node* link(node *x,node *y){
			if(y->key < x->key)
				swap(x,y);
			head=list_remove(y);
			y->parent=x;
			x->degree++;
			x->child=list_cat(x->child,y);
			x->mark=0;
			return x;
		}
		void cut(node *e){
			node *p;
			while(1){
				if(!e->parent)return;
				p=e->parent;
				p->child=list_remove(e);
				p->degree--;

				head=list_cat(head,e);
				if(e->key < min_node->key)
					min_node=e;
				N++;
				if(!p->mark){
					p->mark=1;
					return;
				}else{
					p->mark=0;
					e=p;
				}
			}
		}
	public:
		fib_heap(int n){
			data=new node[n];
			id=new node*[n];
			in=new node*[n];
			memset(in,0,sizeof(node*)*n);
			alloc_idx=0;
			N=0;
			head=0;
			min_node=0;
		}
		~fib_heap(){
			delete[] data;
			delete[] id;
			delete[] in;
		}
		node* new_node(){
			return &data[alloc_idx++];
		}
		virtual bool empty(){
			return !head;
		}
		virtual void insert(int i,const T& key){
			id[i]=new_node();
			id[i]->key=key;
			id[i]->idx=i;
			id[i]->degree=0;
			id[i]->parent=id[i]->child=0;
			id[i]->left=id[i]->right=id[i];
			id[i]->mark=0;
			merge_with(id[i]);
		}
		void merge_with(node* a){
			node *e=a,*m=a;
			do{
				if(e->key < m->key)
					m=e;
				e=e->right;
				e->parent=0;
				N++;
			}while(e!=a);
			if(!min_node || m->key < min_node->key)
				min_node=m;
			head=list_cat(head,a);
		}
		virtual PTI min(){
			return PTI(min_node->key,min_node->idx);
		}
		virtual int delete_min(){

			int res=min_node->idx;
			node *children=min_node->child,*e,*next;
			head=list_remove(min_node);
			N=N-1+min_node->degree;
			int ct=N;
			if(children){
				e=children;
				do{
					e->parent=0;	//	going to merge into roots list, parent must be 0
					e=e->right;
				}while(e!=children);
				head=list_cat(head,children);
			}

			if(!head)return res;
			e=head;
			next=e->right;
			while(1){
				int d=e->degree;
				if(!in[d]){
					in[d]=e;
					e=next;
					next=e->right;
					ct--;
					if(!ct)break;
				}else{
					e=link(e,in[d]);
					N--;
					in[d]=0;
				}
			}

			e=head;
			min_node=e;
			do{
				if(e->key < min_node->key)
					min_node=e;		
				in[e->degree]=0;		//	reset each entry
				e=e->right;
			}while(e!=head);
			return res;
		}
		virtual void decrease_key(int i,const T& k){
			node* e=id[i];
			e->key=k;
			cut(e);
		}
		void print(node* a){
			if(!a)return;
			node* e=a;
			do{
				printf("%d(",e->key);
				print(e->child);
				printf(") ");
				e=e->right;
			}while(e!=a);
		}
		void print(){
			print(head);
			putchar(10);
		}
};
#endif

