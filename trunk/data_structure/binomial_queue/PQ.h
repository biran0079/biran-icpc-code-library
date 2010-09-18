#ifndef __PQ__
#define __PQ__
#include<vector>
#include<algorithm>
using namespace std;
template<class T>
class PQ{
public:
	typedef pair<T,int> PTI;

	//return key-id pair
	virtual PTI min()=0;
	
	//return the id of element deleted
	virtual int delete_min()=0;

	virtual void insert(int i,const T& key)=0;
	virtual void decrease_key(int i,const T& k)=0;
	virtual bool empty()=0;
};
#endif
