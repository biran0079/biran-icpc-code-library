#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
template<class T>
class BinarySearchTree{
	public:
		virtual void clear()=0;
		virtual void insert(const T& x)=0;
		virtual void remove(const T& x)=0;
		virtual const T& findMin()=0;
		virtual const T& findMax()=0;
		virtual const T* find(const T& x)=0;
		virtual bool contains(const T& x)=0;
};
#endif
