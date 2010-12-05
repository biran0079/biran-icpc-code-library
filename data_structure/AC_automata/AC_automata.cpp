#include<cstdio>
#include<cstring>
#include<queue>
#include<list>
using namespace std;
int ans;
char s[10010][60],str[1000010];
struct prefix_trie{
	static const int letter_num=26; //number of total characters
	static const char start='a';    //smallest characters
	struct list{
		int id;
		int ct;
		list* next;
		list(int i,list* n):id(i),next(n){
			ct=1;
		}
	};
	struct node{
		node *child[letter_num],*fail;
		list *l;	//represent set of keywords
		node(){
			fail=0;
			l=0;
			memset(child,0,sizeof(child));
		}
	}*root;
	prefix_trie(){	
		root=new node();
		root->fail=root;
	}
	void insert(char *s,int id){  
		char *word=s;	
		node *cur=root;	
		for(;*s;s++){
			int j=*s-start;
			if(cur->child[j]==NULL)
				cur->child[j]=new node();
			cur=cur->child[j];
		}	
		if(cur->l)
			cur->l->ct++;
		else
			cur->l=new list(id,0);
	}
	void get_prefix(){                        //call this method before calling find
		queue<node*> Q;
		Q.push(root);
		while(!Q.empty()){
			node* q=Q.front(); //father
			Q.pop();  
			for(int i=0;i<letter_num;i++)
				if(q->child[i]){
					node* p=q->child[i],*tem=q;
					tem=tem->fail;
					while(tem!=root && !tem->child[i])
						tem=tem->fail;
					p->fail= tem->child[i] ? tem->child[i] : root;
					if(p==p->fail)p->fail=root;
					if(p->fail->l){
						if(p->l)
							p->l->next=p->fail->l;
						else
							p->l=p->fail->l;
					}
					Q.push(p);
				}		  
		}   	
	}
	void find(char *s){
		node *cur=root;
		for(;*s;s++){
			int i=*s-start;
			while(cur!=root && !cur->child[i])
			       	cur=cur->fail;
			if(cur->child[i]) cur=cur->child[i];
			if(cur->l){
				for(list* l=cur->l;l;l=l->next){
					ans+=l->ct;
					l->ct=0;
				}
			}
		}
	}
};
int main(){
	int n,times;
	scanf("%d",&times);
	while(times--){
		prefix_trie T;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%s",s[i]);
			T.insert(s[i],i);
		}
		T.get_prefix();
		scanf("%s",str);
		ans=0;
		T.find(str);
		printf("%d\n",ans);
	}
	return 0;
}
