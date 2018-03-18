#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

template <typename T>
class Lnode{
public:
	T data;
	Lnode *lptr;
	Lnode *rptr;
};

template <typename T>
class Mlist{
public:
	Mlist();
	void add(T x);
	void add(int i, T x);
	void del(T x);
	void delet(int i);
	T getfront();
	T getback();
	T operator[](unsigned int i);
	
private:
	Lnode<T> *first;
	Lnode<T> *last;
	int lsize;
};

template<typename T>
Mlist<T>::Mlist(){
	first = 0;
	last = 0;
	lsize = 0;
}

template<typename T>
void Mlist<T>::add(T x){
	Lnode<T> *ptr = new Lnode<T>;
	ptr->data=x;
	if(lsize == 0) {
		first = ptr;
		last = ptr;
		ptr->lptr=0;
		ptr->rptr=0;
	}
	else{
		ptr->lptr=last;
		ptr->rptr=0;
		last->rptr=ptr;
		last=ptr;
	}
	lsize++;
}

template<typename T>
void Mlist<T>::add(int i, T x){
	assert(lsize>0);
	Lnode<T> * ptr;
	Lnode<T> * before;
	ptr = first;
	for(int j = 0; j< i; j++)
		ptr = ptr->rptr;
	before = ptr->lptr;
	Lnode<T> *newptr = new Lnode<T>;
	if(lsize == i){
		newptr->lptr=last;
		newptr->rptr=0;
		last->rptr=newptr;
		last=newptr;
		newptr->data=x;
	}
	else{
		newptr->rptr=ptr;
		ptr->lptr=newptr;
		before->rptr=newptr;
		newptr->data=x;
	}
	lsize++;
}

template<typename T>
void Mlist<T>::del(T x){
	assert(lsize>0);
	Lnode<T> * ptr = first;
	while(ptr!=0)
	{
		if(ptr->data == x)
		{
			Lnode<T> * next = ptr->rptr;
			Lnode<T> * previous = ptr->lptr;
			if(previous == 0 and next == 0)
			{
				delete first;
				first = 0;
				last = 0;
				lsize--;
				return;
			}
			if(next == 0 and previous != 0)
			{
				last = previous;
				last->rptr = 0;
				delete ptr;
				lsize--;
				return;
			}
			if(previous == 0 and next!=0)
			{
				first = ptr->rptr;
				first->lptr = 0;
				delete ptr;
				lsize--;
			}
			else if(previous!=0 and next!=0)
			{
				previous->rptr=ptr->rptr;
				delete ptr;
				ptr = next;
				lsize--;
			}
		}
		
		else
		{
			ptr=ptr->rptr;
		}
		
		


	}
}

template<typename T>
void Mlist<T>::delet(int i){
	assert(lsize>0);
	Lnode<T> * ptr = first;
	Lnode<T> * before;
	Lnode<T> * after;
	for(int j = 0; j< i; j++)
		ptr = ptr->rptr;
	if(ptr->rptr == 0)
	{
	before = ptr->lptr;
	before->rptr = 0;
	}
	else{
	before = ptr->lptr;
	after = ptr->rptr;
	after->lptr = before;
	before->rptr = after;
	}
	delete ptr;
	lsize--;
}

template<typename T>
T Mlist<T>::getfront(){
	return first->data;
}


template<typename T>
T Mlist<T>::getback(){
	return last->data;
}


template<typename T>
T Mlist<T>::operator[](unsigned int i){
	assert(lsize>0);
	Lnode<T> * ptr;
	ptr = first;
	for(int j = 0; j< i; j++)
		ptr = ptr->rptr;
	return ptr->data;
	delete ptr;
}

int main()
{
	Mlist<int> a;
	a.add(5);
	a.add(9);
	assert(a.getfront() == 5);
	assert(a.getback() == 9);
	a.add(10);
	assert(a.getback() == 10);
	a.del(9);
	assert(a.getfront() == 5);
	assert(a.getback() == 10); 
	a.add(1, 5);
	assert(a.getfront() == 5);
	assert(a.getback() == 10);

	cout << "All tests Passed. \n";


	return 0;	
}

