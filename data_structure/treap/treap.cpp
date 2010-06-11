/*
 *	pass:pku2761,pku1442,pku2892,pku2892,pku2352
 * */
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
template<class T>
struct Treap{
	struct node{
		T value;
		int pri,times,size;
		node *left,*right;	
	}*root,*null,*pool;
	int alloc_ptr;
	Treap(){
		null=new node();
		null->pri = 0x7fffffff;
		null->size = null->times = 0;
		null->left=null->right=null;
		pool=new node[1000000];
		root=null;
		alloc_ptr=0;
	}
	inline node* new_node(const T& v){
		node* res=&pool[alloc_ptr++];
		res->value=v;
		res->left=res->right=null;
		res->times=1;
		res->size=1;
		res->pri=rand();
		return res;
	}
	void clear(node* cur){
		if(null!=cur){
			clear(cur->left);
			clear(cur->right);
			delete cur;
		}
	}
	void clear(){
		clear(root);
		root=null;
		alloc_ptr=0;
	}
	void resize(node* cur){
		cur->size=cur->left->size+cur->right->size+cur->times; 
	}
	void left_rotate(node* &cur){
		node *res=cur->left;
		cur->left=res->right;
		res->right=cur;
		resize(cur);
		cur=res;		 
	}
	void right_rotate(node* &cur){
		node *res=cur->right;
		cur->right=res->left;
		res->left=cur;
		resize(cur);
		cur=res;		 
	}
	void insert(const T& x, node* &cur){
		if(cur == null)
			cur = new_node(x);
		else if(x < cur->value){
			insert(x,cur->left);
			if(cur->pri > cur->left->pri)
				left_rotate(cur);	 
		}else if(cur->value < x){
			insert(x,cur->right);	
			if(cur->pri > cur->right->pri)
				right_rotate(cur);	   
		}else cur->times++;	
		resize(cur);
	}
	void remove(const T& x, node* &cur){
		if(cur==null)
			return;
		else if(cur->value < x)
			remove(x,cur->right);
		else if(x < cur->value)
			remove(x,cur->left);
		else if(cur->times-1 == 0){
			if(cur->left == null && cur->right == null)
				cur=null;
			else if(cur->left->pri < cur->right->pri){
				left_rotate(cur);
				remove(x,cur->right);
			}
			else{ 
				right_rotate(cur);
				remove(x,cur->left);
			}
		}else cur->times--;
		resize(cur);	 
	}
	int rank(const T& x){
		node* cur=root;
		int res=0;
		while(cur!=null){
			if(cur->value < x){
				res+=cur->left->size + cur->times;
				cur=cur->right;
			}else if(x < cur->value){	   
				cur=cur->left;
			}else{
				res=cur->left->size+1;
			}
		}
		return res;
	}
	T select(int k){
		node* cur=root;
		while(cur!=null){
			if(k <= cur->left->size){
				cur=cur->left;
			}else if(k <= cur->left->size + cur->times){
				break;
			}else{
				k-=cur->left->size+cur->times;
				cur=cur->right;
			}
		}
		return cur->value;
	}
	void insert(const T& x){
		insert(x,root);		
	}
	void remove(const T&x){
		remove(x,root);
	}
	bool contains(const T &x){
		node* cur=root;
		while(cur!=null){
			if(x < cur->value)
				cur=cur->left;
			else if(cur->value < x)
				cur=cur->right;
			else return true;				 
		}		
		return false;
	}
	T find_max(node* cur){
		while(cur->right!=null)
			cur=cur->right;
		return cur->value;
	}
	T find_min(node* cur){
		while(cur->left!=null)
			cur=cur->left;
		return cur->value;
	}
	//return min element greater than or equal to x
	T find_next(const T& x){
		T res=this->find_max();
		node *cur=root;
		while(cur!=null){
			if(x < cur->value){
				res=min(res,cur->value);
				cur=cur->left;
			}else if(cur->value < x){
				cur=cur->right;
			}else{
				res=x;
				break;
			}
		}
		return res;
	}
	//return max element smaller than or equal to x
	T find_prev(const T& x){
		T res=this->find_min();
		node *cur=root;
		while(cur!=null){
			if(x < cur->value){
				cur=cur->left;
			}else if(cur->value < x){
				res=max(res,cur->value);
				cur=cur->right;
			}else{
				res=x;
				break;
			}
		}
		return res;
	}
	//return the number of elements smaller than or equal to x
	int count_prev(const T& x){
		node *cur=root;
		int res=0;
		while(cur!=null){
			if(x < cur->value){
				cur=cur->left;
			}else if(cur->value < x){
				res+=cur->left->size+cur->times;
				cur=cur->right;
			}else{
				res+=cur->left->size+cur->times;
				break;
			}
		}
		return res;
	}
	//return the number of elements greater than or equal to x
	int count_next(const T& x){
		node *cur=root;
		int res=0;
		while(cur!=null){
			if(x > cur->value){
				cur=cur->right;
			}else if(cur->value > x){
				res+=cur->right->size+cur->times;
				cur=cur->left;
			}else{
				res+=cur->right->size+cur->times;
				break;
			}
		}
		return res;
	}
};
struct client{
	int i,p;
	client(){}
	client(int i,int p):i(i),p(p){}
	bool operator< (const client& t)const{
		return p < t.p;
	}
	bool operator==(const client& t)const{
		return p == t.p;
	}
	bool operator!=(const client &t)const{
		return p!=t.p;
	}
};
int main(){
	int n,a,b,ans;
	Treap<client> tree;
	while(1){
		scanf("%d",&n);
		switch(n){
			case 1:
				scanf("%d%d",&a,&b);
				tree.insert(client(a,b));
				break;
			case 2:
				if(tree.root->size){
					client t=tree.find_max(tree.root);
					ans=t.i;
					tree.remove(t);
				}else{
					ans=0;
				}
				printf("%d\n",ans);
				break;
			case 3:
				if(tree.root->size){
					client t=tree.find_min(tree.root);
					ans=t.i;
					tree.remove(t);
				}else{
					ans=0;
				}
				printf("%d\n",ans);
				break;
			case 0:goto outside;
		}
	}
outside:
	return 0;
}
