#ifndef __BINOMIAL_HEAP__
#define __BINOMIAL_HEAP__
#include"PQ.h"

template<class T>
class binomial_heap : public PQ<T>{
	private:
		class node{
			public:
				T key;
				int degree,idx;
				node *child,*sibling,*parent;
		};
		typedef pair<T,int> PTI;

		node *data, *head;
		node ** id;
		int alloc_idx;

		node* new_node(){
			return &data[alloc_idx++];
		}
		node* min_node(){
			node* res=0;
			for(node* t=head;t;t=t->sibling)
				if(!res || t->key < res->key)
					res=t;
			return res;
		}
		node* link(node*a,node* b){
			//assume a->degree==b->degree
			if(b->key < a->key) swap(a,b);
			b->sibling=a->child;
			a->child=b;
			b->parent=a;
			a->degree++;
			return a;
		}
		void swap_node(int i,int j){
			swap(id[i]->idx,id[j]->idx);
			swap(id[i]->key,id[j]->key);
			swap(id[i],id[j]);
		}
		node* list_insert(node* tail,node* a){
			if(!tail)return a;
			tail->sibling=a;
			return a;
		}
		node* list_reverse(node* a){
			if(!a)return 0;
			node *prev=a,*next=a->sibling;
			a->sibling=0;
			while(next){
				a=next;
				next=a->sibling;
				a->sibling=prev;
				prev=a;
			}
			return prev;
		}
		node* merge(node* a,node* b){
			if(!a)return b;
			if(!b)return a;
			node *res=0,*tail=0,*carry=0;
			while(a && b){
				if(a->degree > b->degree)
					swap(a,b);
				if(a->degree==b->degree){
					if(carry){
						tail=list_insert(tail,carry);
						if(!res)res=tail;
					}
					node* t1=a->sibling,*t2=b->sibling;
					carry=link(a,b);
					carry->sibling=0;
					a=t1;
					b=t2;
				}else{	//a->degree < b->degree
					if(carry){
						if(carry->degree < a->degree){
							tail=list_insert(tail,carry);
							if(!res)res=tail;
							carry=0;
						}else{
							node* t=a->sibling;
							carry=link(carry,a);
							carry->sibling=0;
							a=t;
						}
					}else{
						tail=list_insert(tail,a);
						if(!res)res=tail;
						a=a->sibling;
					}
				}
			}
			if(a)swap(a,b);
			if(carry){
				if(b){
					while(b && carry->degree==b->degree){
						node* t=b->sibling;
						carry=link(carry,b);
						carry->sibling=0;
						b=t;
					}
					if(b){
						tail=list_insert(tail,carry);
						if(!res)res=tail;
						tail=list_insert(tail,b);
					}else{
						tail=list_insert(tail,carry);
						if(!res)res=tail;
					}
				}else{
					tail=list_insert(tail,carry);
					if(!res)res=tail;
				}
			}else if(b){
				tail=list_insert(tail,b);
				if(!res)res=tail;
			}
			return res;
		}
	public:
		binomial_heap(int n){
			head=0;
			data=new node[n];
			id=new node*[n];
			alloc_idx=0;
		}
		~binomial_heap(){
			delete[] data;
			delete[] id;
		}
		virtual bool empty(){
			return !head;
		}
		virtual void insert(int i,const T& key){
			id[i]=new_node();
			id[i]->idx=i;
			id[i]->key=key;
			id[i]->degree=0;
			id[i]->child=id[i]->sibling=id[i]->parent=0;
			head=merge(head,id[i]);
		}
		virtual PTI min(){
			//assume non-empty
			node* res=min_node();
			return make_pair(res->key,res->idx);
		}
		virtual int delete_min(){
			//assume non-empty
			node *m=head,*pre=0;
			for(node* p=head;p->sibling;p=p->sibling){
				if(p->sibling->key < m->key){
					m=p->sibling;
					pre=p;
				}
			}
			if(m==head){
				head=m->sibling;
			}else{
				pre->sibling=m->sibling;
			}
			//print(m->child);printf("!\n");
			//print(list_reverse(m->child));printf("!\n");
			head=merge(head,list_reverse(m->child));
			return m->idx;
		}
		virtual void decrease_key(int i,const T& k){
			node* t=id[i];
			t->key=k;
			while(t->parent && k < t->parent->key){
				swap_node(t->idx,t->parent->idx);
				t=t->parent;
			}
		}
		void print(node* a){
			for(node* t=a;t;t=t->sibling)
				printf("%d ",t->degree);
		}
		void print(){
			print(head);
		}
};

#endif
