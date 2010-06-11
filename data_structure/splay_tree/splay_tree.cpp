/*
 * pass:pku2761,pku2892,pku2352,pku3841
 * */
#include<stdio.h>
#include<algorithm>
using namespace std;
template<class T>
struct SplayTree{
	struct node{
		T value;
		node *left,*right;
		int times,size;
	};
	node *root,*null,*pool;
	int alloc_ptr;
	SplayTree(){
		null=new node;
		null->left=null->right=null;
		null->times=null->size=0;
		pool=new node[100000];
		root=null;
		alloc_ptr=0;
	}
	node* new_node(const T& x){
		node* res=&pool[alloc_ptr++];
		res->value=x;
		res->left=res->right=null;
		res->times=1;
		res->size=1;
		return res;
	}
	node* splay(const T& x,node* cur){
		while(1){
			if(x < cur->value){
				if(null == cur->left)return cur;
				if(x < cur->left->value && 
						null!=cur->left->left){
					cur->left=zig(cur->left);
					cur=zig(cur);
				}else if(cur->left->value < x && 
						null!=cur->left->right){
					cur->left=zag(cur->left);
					cur=zig(cur);
				}else{
					return zig(cur);
				}
			}else if(cur->value < x){
				if(null == cur->right)return cur;
				if(cur->right->value < x && 
						null != cur->right->right){
					cur->right=zag(cur->right);
					cur=zag(cur);
				}else if(x < cur->right->value 
						&& null != cur->right->left){
					cur->right=zig(cur->right);
					cur=zag(cur);
				}else{
					return zag(cur);
				}
			}else	return cur;
		}
	}
	inline void update(node* cur){
		cur->size=cur->times+cur->left->size+cur->right->size;
	}
	void insert(const T& v){
		if(root==null){
			root=new_node(v);
		}else{
			root=splay(v,root);
			if(v == root->value){
				root->times++;
				root->size++;
				return;
			}
			node* nnode=new_node(v);
			if(v < root->value){
				nnode->right=root;
				nnode->left=root->left;
				root->left=null;
				update(nnode->right);
				update(nnode);
			}else{
				nnode->left=root;
				nnode->right=root->right;
				root->right=null;
				update(nnode->left);
				update(nnode);
			}
			root=nnode;
		}
	}
	void remove(const T& v){
		if(null == root)return;
		root=splay(v,root);
		if(root->value != v)return;
		if(root->times>1){
			root->times--;
		}else{
			node* ntree;
			if(null == root->left){
				ntree=root->right;
			}else{
				ntree=splay(v,root->left);
				ntree->right=root->right;
			}
			root=ntree;
			update(root);
		}
	}
	T find_max(node* cur){
		while(cur->right!=null)
			cur=cur->right;
		root=splay(cur->value,root);
		return cur->value;
	}
	T find_min(node* cur){
		while(cur->left!=null)
			cur=cur->left;
		root=splay(cur->value,root);
		return cur->value;
	}
	inline bool contains(const T& v){
		root=splay(v,root);
		return root->value==v;
	}
	inline void clear(){
		root=null;
		alloc_ptr=0;
	}
	inline node* zig(node* k2){
		node* k1=k2->left;
		k2->left=k1->right;
		k1->right=k2;
		update(k2);		//order of updating
		update(k1);		//is important
		return k1;
	}
	inline node* zag(node* k2){
		node* k1=k2->right;
		k2->right=k1->left;
		k1->left=k2;
		update(k2);
		update(k1);
		return k1;
	}
	inline int rank(const T& x){
		if(null == root)return 1;
		root=splay(x,root);
		if(root->value < x)
			return root->left->size+root->times+1;
		else
			return root->left->size+1;
	}
	T select(int x){
		node* cur=root;
		if(x > cur->size)return 0x11111111;
		int l,r;
		while(1){
			l=cur->left->size;
			r=l+cur->times;
			if(x > l && x <= r){
				return cur->value;
			}else if( x > r ){
				cur=cur->right;
				x-=r;
			}else{
				cur=cur->left;
			}
		}
	}
	//return min element greater than or equal to x
	T find_next(const T& x){
		root=splay(x,root);
		if(x <= root->value)return root->value;
		else return find_min(root->right);
	}
	//return max element smaller than or equal to x
	T find_prev(const T& x){
		root=splay(x,root);
		if(x >= root->value)return root->value;
		else return find_max(root->left);
	}
	//return the number of elements smaller than or equal to x
	int count_prev(const T& x){
		root=splay(x,root);
		if(x < root->value){
			return root->left->size;
		}else{	//	x == root->value or max of root->left is the prev of x
			return root->left->size+root->times;
		}
	}
	//return the number of elements greater than or equal to x
	int count_next(const T& x){
		root=splay(x,root);
		if(x > root->value){
			return root->right->size;
		}else{	//	x == root->value or min of root->right is the next of x
			return root->right->size+root->times;
		}
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
	SplayTree<client> tree;
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
