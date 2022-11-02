/*
Powered by Hizitok
#include"list.cpp"

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

template<class elemType>
class list_{
	public:
		virtual void clear() = 0;
		virtual int length() const = 0;
		virtual void insert(int i, const elemType &x) = 0;
		virtual void remove(int i) = 0;
		virtual int search(const elemType &x) const = 0;
		virtual elemType visit(int i) const = 0;
		virtual void traverse() const = 0;
		virtual ~list_(){};
	
};

template<class elemType>
class seqList: public list_< elemType >
{
	private:
		elemType *data;
		int currentLength;
		int maxSize;
		void doubleSpace();
	public:
		seqList(int initSize = 10)
		{
			data = new elemType[initSize];
			currentLength = 0;
			maxSize = initSize;
		}
		~seqList() { delete [] data; }
		void clear(){ currentLength = 0; }
		int length() const { return currentLength; }
		void insert(int i, const elemType &x);
		void remove(int i);

		int search(const elemType &x) const;

		elemType visit(int i) const{
			return data[i];
		}
		void traverse() const
		{
			std::cout << std::endl;
			for(int i = 0; i < currentLength ; i++)
				std::cout << data[i] << " ";
		}
};

template<class T>
void seqList< T >:: insert(int i, const T &x)
{
	if(currentLength == maxSize) doubleSpace();
	for(int j = currentLength; j < i ; j-- )
		data[j] = data[j-1];
	data[i] = x;
	currentLength++;
}

template<class T>
void seqList< T >:: remove(int i)
{
	for(int j = i; j < currentLength-1 ; j++ )
		data[j] = data[j+1];

	currentLength--;
}

template<class T>
int seqList< T >:: search(const T &x) const
{
	int i;
	for( i = 0 ; i < currentLength && data[i] != x ; i++ ) ;
	if(i == currentLength)
		return -1; 
	else
		return i;
} 
template<class T>
void seqList< T >:: doubleSpace()
{
	T *tmp = data;
	maxSize *= 2;
	data = new T[maxSize];
	for(int i =0; i < currentLength ; ++i )
		data[i] = tmp[i];
	delete [] tmp;
}

void hello()
{
	std::cout << "Hello World!";
}
