#include<stdio.h>
#include<algorithm>
using namespace std;
inline int max(int a,int b){
	return a>b?a:b;
}
inline int abs(int a){
	return a>=0?a:-a;
}
template<class T>
struct AVLtree{
	struct node{
		T value;
		node *left,*right;	
		int height,times,size;	  
	}*root,*null,*pool;
	int alloc_point;
	AVLtree(){
		alloc_point=0;
		pool=new node[1000000];
		null=new node();
		null->left=null->right=null;
		null->height=-1;
		null->size=0;
		root=null;
	}
	void clear(){
		alloc_point=0;
		root=null;
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
	~AVLtree(){
		delete[] pool;	  
	}

	inline node* new_node(const T &value){
		node *res=&pool[alloc_point++];
		res->value=value;
		res->left=res->right=null;
		res->height=0;
		res->times=1;
		res->size=1;
		return res;		  
	}
	inline void update(node* cur){
		cur->height=1+max(cur->right->height,cur->left->height);
		cur->size=cur->times+cur->left->size+cur->right->size;	   
	}
	inline node* left_rotate(node* cur){
		node* res=cur->left;
		cur->left=res->right;
		res->right=cur;
		update(res->right);
		return res;		 
	}       
	inline node* right_rotate(node* cur){
		node* res=cur->right;
		cur->right=res->left;
		res->left=cur;
		update(res->left);
		return res;		 
	}
	node* keep_balance(node* cur){
		int dif=cur->left->height - cur->right->height;
		if(dif > 1){
			if(cur->left->left->height > cur->left->right->height)
				cur=left_rotate(cur);	
			else {
				cur->left=right_rotate(cur->left);	 
				cur=left_rotate(cur);
			}
		}else if(dif < -1){
			if(cur->right->right->height > cur->right->left->height)
				cur=right_rotate(cur);
			else{
				cur->right=left_rotate(cur->right);	 
				cur=right_rotate(cur); 					 
			}    
		}//else, tree is balanced initially
		update(cur);
		return cur;
	}
	node* insert(node* cur,const T &x){ 
		if(cur==null)
			return new_node(x);	 
		else {
			if(x < cur->value)
				cur->left=insert(cur->left,x);
			else if(cur->value < x)
				cur->right=insert(cur->right,x);
			else  ++cur->times;
			return keep_balance(cur);
		}
	}
	inline node* seccor(node *cur){
		cur=cur->right;
		while(cur->left!=null)
			cur=cur->left;
		return cur;		  
	}
	node* remove_min(node *cur){
		if(cur->left==null)return cur->right;
		else {
			cur->left=remove_min(cur->left);
			return keep_balance(cur);
		}
	}
	node* remove(node *cur, const T &x){
		if(cur==null)return null;
		if(cur->value == x){
			if((--cur->times) > 0) 
				return keep_balance(cur);
			if(cur->left==null)
				return cur->right;
			if(cur->right==null)
				return cur->left;
			node *next=seccor(cur);         	//如果左右孩子都有，找到后继结点，复制过来（包括times域） 
			cur->value=next->value;	
			cur->times=next->times;
			cur->right=remove_min(cur->right);// 删除后继结点（无论有多少个） 
		}else if(x < cur->value)
			cur->left = remove(cur->left,x);	
		else
			cur->right = remove(cur->right,x);	
		return keep_balance(cur);
	}
	inline void remove(const T &x){
		root=remove(root,x);  
	}
	T select(node*cur, int x){
		if(x > cur->size)return 0x11111111;
		int l=cur->left->size+1,r=l+cur->times-1;
		if(x >= l && x <=r)
			return cur->value;
		else if( x > r )
			return select(cur->right,x - r);	
		else 
			return select(cur->left , x);	 
	}
	inline T select(int x){
		return select(root,x);  			 
	}
	int rank(const T& x,node* cur){
		if(cur->value < x)
			return cur->left->size + cur->times + rank(x,cur->right);
		else if(x < cur->value)	   
			return rank(x,cur->left);
		else return cur->left->size + 1;
	}
	int rank(const T& x){
		return rank(x,root);
	}
	inline void insert(const T &x){
		root=insert(root,x);	
	}
	T* find(const T& x){
		node *cur=root;
		while(cur!=null){
			if(cur->value < x)cur=cur->right;
			else if(x < cur->value)cur=cur->left;
			else return &cur->value;			  
		} 
		return NULL;	  
	}
	inline bool contains(const T& x){
		return find(x)!=NULL;
	}
	//following commented code for debug
	/*
	   void print(node *cur){
	   if(cur==null)return;
	   print(cur->left);
	   printf(" %d:%d ",cur->value,cur->times);
	   print(cur->right);			
	   }
	   void print(){
	   print(root);
	   putchar(10);
	   }
	   bool valid_AVL(node *cur){
	   if(cur==null)return true;
	   return 	
	   valid_AVL(cur->left)
	   && valid_AVL(cur->right)
	   && cur->height == 1+max(cur->left->height,cur->right->height);	
	   }
	   bool valid_size(node* cur){
	   if(cur==null)return true;
	   return 	valid_size(cur->left)
	   && valid_size(cur->right)
	   &&	cur->size == cur->times+ cur->left->size+cur->right->size;
	   }
	   bool valid(){
	   return valid_size(root) && valid_AVL(root);
	   }	
	   */
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
	AVLtree<client> tree;
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
