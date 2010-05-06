//pass:pku2761
#include<stdio.h>
template<class T>
struct splay_tree{
	struct node{
		node *left,*right;
		T value;
		int times,size;
		node(int v,node* l,node* r):value(v),left(l),right(r),
		times(1),size(1){}
	};
	node *root,*null;
	splay_tree(){
		null=new node(0,0,0);
		null->left=null->right=0;
		null->times=null->size=0;
		root=null;
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
			root=new node(v,null,null);
		}else{
			root=splay(v,root);
			if(v == root->value){
				root->times++;
				root->size++;
				return;
			}
			node* new_node=new node(v,null,null);
			if(v < root->value){
				new_node->right=root;
				new_node->left=root->left;
				root->left=null;
				update(new_node->right);
				update(new_node);
			}else{
				new_node->left=root;
				new_node->right=root->right;
				root->right=null;
				update(new_node->left);
				update(new_node);
			}
			root=new_node;
		}
	}
	void remove(const T& v){
		if(null == root)return;
		root=splay(v,root);
		if(root->value != v)return;
		if(root->times>1){
			root->times--;
		}else{
			node* new_tree;
			if(null == root->left){
				new_tree=root->right;
			}else{
				new_tree=splay(v,root->left);
				new_tree->right=root->right;
			}
			delete root;
			root=new_tree;
			update(root);
		}
	}
	T find_max(){
		node* cur=root;
		while(cur->right)
			cur=cur->right;
		root=splay(cur->value,root);
		return cur->value;
	}
	T find_min(){
		node* cur=root;
		while(cur->left)
			cur=cur->left;
		root=splay(cur->value,root);
		return cur->value;
	}
	inline bool contains(const T& v){
		root=splay(v,root);
		return root->value==v;
	}
	void clear(node* cur){
		if(null != cur){
			clear(cur->left);
			clear(cur->right);
			delete cur;
		}
	}
	inline void clear(){
		clear(root);
		root=null;
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
};
int main(){
	int n,a,times,t;
	splay_tree<int> tree;
	char s[20];
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%s%d",s,&t);
		if(s[0]=='I')tree.insert(t);
		else if(s[0]=='D')tree.remove(t);
		else if(s[0]=='R')printf("%d\n",tree.rank(t));
		else if(s[0]=='K')printf("%d\n",tree.select(t));
	}
	return 0;
}
