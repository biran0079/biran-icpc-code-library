/*
 *	translated from CS1102S text book code
 * */
#include<stdio.h>
struct splay_tree{
	struct node{
		node *left,*right;
		int value,times,size;
		node(int v){
			value=v;
			times=1;
			size=1;
			left=right=NULL;
		}
	};
	node *root;
	splay_tree(){
		root=NULL;
	}
	node* splay(int x,node* cur){
		while(1){
			if(cur->value > x){
				if(!cur->left)return cur;
				if(cur->left->value > x && cur->left->left){
					cur->left=zig(cur->left);
					cur=zig(cur);
				}else if(cur->left->value < x && cur->left->right){
					cur->left=zag(cur->left);
					cur=zig(cur);
				}else{
					return zig(cur);
				}
			}else if(cur->value < x){
				if(!cur->right)return cur;
				if(cur->right->value < x && cur->right->right){
					cur->right=zag(cur->right);
					cur=zag(cur);
				}else if(cur->right->value > x && cur->right->left){
					cur->right=zig(cur->right);
					cur=zag(cur);
				}else{
					return zag(cur);
				}
			}else	return cur;
		}
	}
	inline int get_size(node* cur){
		return cur?cur->size:0;
	}
	inline void update(node* cur){
		cur->size=cur->times+get_size(cur->left)+get_size(cur->right);
	}
	void insert(int v){
		node* new_node=new node(v);
		if(root==NULL){
			root=new_node;
		}else{
			root=splay(v,root);
			if(v < root->value){
				new_node->right=root;
				new_node->left=root->left;
				root->left=NULL;
				update(new_node);
				update(new_node->right);
				root=new_node;
			}else if(v > root->value){
				new_node->left=root;
				new_node->right=root->right;
				root->right=NULL;
				update(new_node);
				update(new_node->left);
				root=new_node;
			}else{
				root->times++;
				root->size++;
				delete new_node;
			}
		}
	}
	void remove(int v){
		if(!root)return;
		root=splay(v,root);
		if(root->value!=v)return;
		if(root->times>1){
			root->times--;
			return;
		}
		node* new_tree;
		if(!root->left){
			new_tree=root->right;
		}else{
			new_tree=root->left;
			new_tree=splay(v,new_tree);
			new_tree->right=root->right;
		}
		delete root;
		root=new_tree;
	}
	int find_max(){
		node* cur=root;
		while(cur->right)
			cur=cur->right;
		root=splay(cur->value,root);
		return cur->value;
	}
	int find_min(){
		node* cur=root;
		while(cur->left)
			cur=cur->left;
		root=splay(cur->value,root);
		return cur->value;
	}
	bool contains(int v){
		node* root=splay(v,root);
		return root->value==v;
	}
	void clear(node* cur){
		if(cur){
			clear(cur->left);
			clear(cur->right);
			delete cur;
		}
	}
	void clear(){
		clear(root);
		root=NULL;
	}
	node* zig(node* k2){
		node* k1=k2->left;
		k2->left=k1->right;
		k1->right=k2;
		update(k1);
		update(k2);
		return k1;
	}
	node* zag(node* k2){
		node* k1=k2->right;
		k2->right=k1->left;
		k1->left=k2;
		update(k1);
		update(k2);
		return k1;
	}
	int rank(int x){
		if(!root)return -1;
		root=splay(x,root);
		if(root->value!=x)return -1;
		return get_size(root->left)+1;
	}
	void print(node* cur){
		if(cur){
			print(cur->left);	
			for(int i=0;i<cur->times;i++)
				printf("%d(%d) ",cur->value,cur->size);
			print(cur->right);	
		}
	}
	void print(){
		print(root);
		putchar(10);
	}
};
int main(){
	int n,a,times;
	splay_tree tree;
	while(1){
		char s[20];
		scanf("%s%d",s,&a);
		if(s[0]=='I'){
			tree.insert(a);
		}else if(s[0]=='R'){
			tree.remove(a);
		}else if(s[0]=='Q'){
			printf("%d\n",tree.rank(a));
		}
		tree.print();
	}
	return 0;
}
