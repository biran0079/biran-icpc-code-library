#include<stdio.h>
#include<algorithm>
using namespace std;
const int maxn=1000000;
template<class T>
struct LeftistHeap{                //max heap
	struct node{
		T value;
		node *left,*right;
		int npl;
	}*root,*null,*pool;
	int alloc_pt;
	LeftistHeap(){
		null=new node();
		null->npl=-1; 		 
		root=null;	
		alloc_pt=0;	
		pool=new node[maxn];	
	}
	inline bool empty(){
		return root==null;  
	}
	inline node* new_node(const T &x){
		node* res=&pool[alloc_pt++];
		res->value=x;
		res->left=res->right=null;
		res->npl=0;
		return res;
	}
	node* merge(node *h1,node *h2){
		if(h1==null)return h2;
		if(h2==null)return h1;
		if(h1->value < h2->value)   //make sure the root of h1 is bigger
			swap(h1,h2);
		h1->right=merge(h1->right,h2);
		if(h1->left->npl < h1->right->npl)
			swap(h1->left,h1->right);
		h1->npl=1+h1->right->npl;
		return h1;
	}
	void push(const T& x){
		root=merge(root,new_node(x));
	}
	T pop(){
		T res=root->value;
		root=merge(root->left,root->right);
		return res;
	}
};
int a[maxn],b[maxn];
int main(){
	for(int i=0;i<maxn;i++)b[i]=a[i]=rand();
	printf("STL sort starts...\n");
	sort(a,a+maxn);
	printf("STL sort ends...\n\n");
	printf("heap sort starts...\n");
	LeftistHeap<int> h;
	for(int i=0;i<maxn;i++)h.push(b[i]);
	int top=maxn-1;
	while(!h.empty()){
		b[top--]=h.pop();
	}
	printf("heap sort ends...\n");
	bool ac=1;
	for(int i=0;i<maxn;i++){
		if(a[i]!=b[i]){
			ac=0;
			break;
		}
	}
	printf(ac?"AC\n":"WA\n");
	return 0;
}
