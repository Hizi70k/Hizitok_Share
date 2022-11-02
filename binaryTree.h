/*
Hizitok's Binary Tree

The MIT License (MIT)
Copyright (c) <year> <copyright holders>
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the software”),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
	The Software is provided "as is" ,without warranty of any kind, express or implied, including but not limited to the warranties of merchantability,
fitness for a particular purpose and noninfringement.
In no event shall the authors or copyright holders be liable for any claim, damages or other liability,
whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other dealings in the Software.

*/

#include<iostream>
#include<cstdlib>
#include<cstring>

int full_check(int num);

template< class T >
class biTree
{
	public:
		virtual void clear() = 0;
		virtual bool isEmpty() const = 0;
//		virtual T root(T flag) const = 0; 	
//		virtual T parent(T x, T flag) const = 0;
//		virtual biTree *lchild() = 0;
//		virtual biTree *rchild() = 0;
		
		virtual void delLeft() = 0;
		virtual void delRight() = 0;
		
		virtual void preOrder() const = 0;
		virtual void midOrder() const = 0;
		virtual void postOrder() const = 0;
		virtual void levelOrder() = 0;
				
		~biTree(){}
};

template< class T >
class binaryTree : public biTree< T >
{
	private:
		static binaryTree *arr[1024];
		static int leaf_max;
		binaryTree<T> *l_child,*r_child;
		T *data;
		
		void statIndex( int index = 1 )
		{
			if ( this == nullptr ) return;
			if( index == 1 ) 
			{
				memset(arr,0,sizeof(arr));
				leaf_max = 1;
			}
			
			arr[ index ] = this;
			leaf_max = ( leaf_max > index )?leaf_max:index;
			if(l_child) l_child->statIndex( 2*index   );
			if(r_child) r_child->statIndex( 2*index+1 );
		}
		
	public:
		binaryTree()
		{
			l_child = nullptr;
			r_child = nullptr;
			data = nullptr;
		}
		~binaryTree()	{	clear();	}

		bool isEmpty() const	{	return data == nullptr;	}
		binaryTree<T> *lchild() const {	return l_child;	}
		binaryTree<T> *rchild() const {	return r_child;	}
		
		binaryTree *copy()
		{
			if( this == nullptr ) return nullptr; 
			
			binaryTree *newTree;
			newTree = new binaryTree<T>;
			
			newTree->set_data( *data );
			if(l_child)	newTree->l_child = l_child->copy();
			if(r_child)	newTree->r_child = r_child->copy();	
			return newTree;
		}
		
		void clear()
		{
			if( this == nullptr ) return;
			delLeft();
			delRight();
			delete data;
		}
		void delLeft()	{	if(l_child)	{	l_child->clear();	delete l_child;	}	}
		void delRight()	{	if(r_child) {	r_child->clear();	delete r_child;	} 	}
		
		void set_data( T datus )
		{
			if( this == nullptr ) return;
			if( data != nullptr ) delete data;
			data = new T(datus);
		}
		void set_left( T datus )
		{
			if(l_child == nullptr) l_child = new binaryTree<T>;
			l_child -> set_data(datus);
		}
		void set_right( T datus )
		{
			if(r_child == nullptr) r_child = new binaryTree<T>;
			r_child -> set_data(datus);
		}
		
		void set_left( binaryTree<T> *sonTree )
		{
			l_child = sonTree -> copy();
		}
		void set_right( binaryTree<T> *sonTree )
		{
			r_child = sonTree -> copy();
		}
		
		void swap() 
		{
			if( this == nullptr ) return;
			binaryTree<T> *t;
			
			l_child -> swap();
			r_child -> swap();
			
			t = l_child; l_child = r_child; r_child = t;
		}

		void preOrder() const
		{
			if( this == nullptr ) return;
			std::cout << *data;	
			if(l_child)	l_child->preOrder();
			if(r_child) r_child->preOrder();

		}
		void midOrder() const
		{
			if( this == nullptr ) return;	
			if(l_child)	l_child -> midOrder();
			std::cout << *data;
			if(r_child) r_child -> midOrder();
		}
		void postOrder() const
		{
			if( this == nullptr ) return;
			if(l_child)	l_child -> postOrder();
			if(r_child) r_child -> postOrder();
			std::cout << *data;
		}
		
		int weight() const
		{
			int ans=1;
			if(l_child) ans += l_child->weight();
			if(r_child) ans += r_child->weight();
			return ans;
		}
		
		int max_index() const
		{
			statIndex();
			return leaf_max;
		}
		
		void levelOrder()
		{
			if( this == nullptr ) return;
			statIndex();
			
			for(int i = 1; i <= leaf_max; i++ )
				if( arr[i] )	std::cout << *(arr[i]->data);	
		}
		
		int is_complete()
		{
			if( this == nullptr ) return 1;
			
			statIndex();
			for(int i = 1; i <= leaf_max; i++ )
				if(arr[i] == nullptr) return 0;
			return 1;
 		}
		int is_full()
		{
			if( this == nullptr ) return 1;
			
			if( is_complete() == 0 ) return 0;
			return full_check(leaf_max);
		}
		
		bool compare(const binaryTree<T> *a, const binaryTree<T> *b)
		{
			if( (a == nullptr) ^ (b == nullptr) ) 	return 0;
			if( (a == nullptr) & (b == nullptr) ) 	return 1;
			
			if( *a->data != *b->data ) return 0;
			
			if( !compare( a->l_child , b->l_child ) ) return 0;
			if( !compare( a->r_child , b->r_child ) ) return 0;
				
			return 1;
		}
	
		bool operator ==(binaryTree<T> &a)
		{
			return compare( &a,this );
		}

};

template< class T >
binaryTree<T> *binaryTree<T>::arr[1024];

template< class T >
int binaryTree<T>::leaf_max;

template<class T>
void fullOrder(binaryTree<T> *p_)
{
	p_ -> preOrder();
	std::cout << std::endl;
	p_ -> midOrder();
	std::cout << std::endl;
	p_ -> postOrder();
	std::cout << std::endl;
	p_ -> levelOrder();
}


int full_check(int num)
{
	while(num & 1)
		num = num >> 1;
	if(num == 0) return 1;
	return 0;
}

binaryTree<int> *example()
{
	static binaryTree<int> *p;
	p = new binaryTree<int>;
	p -> set_data(1);
	p -> set_left(2);
	p -> set_right(3);
	p -> lchild() -> set_left(4);
	p -> lchild() -> set_right(5);
	
	return p;
}

