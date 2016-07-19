#ifndef __LINKLIST_H_
#define __LINKLIST_H_
#include <stdio.h>
template<class T>
class TLinkList;

template<class T>
class TLinkListItem
{
	friend class TLinkList<T>;
private:
	T *item;
protected:
	TLinkListItem<T> *next;	
public:		
	inline T *getItem(){ return item;}
	inline TLinkListItem<T> *getNext(){ return next;}	
	~TLinkListItem()
	{
		delete item;
	}
	
	TLinkListItem(T *p_item)
	{	
		item=p_item;
		next=nullptr;	
	}
};


template<class T>
class TLinkList
{
private:
	TLinkListItem<T> *start;
	TLinkListItem<T> *top;
public:
		
	inline TLinkListItem<T> *getStart(){ return start;}
	
	TLinkList(){
		top=nullptr;
		start=nullptr;
	}
	~TLinkList(){
		TLinkListItem<T> *l_current=start;
		TLinkListItem<T> *l_next;
		while(l_current !=nullptr){
			l_next=l_current->next;
			delete l_current;
			l_current=l_next;
		}
	}
	
	void append(T *p_item)
	{
		TLinkListItem<T> *l_item=new TLinkListItem<T>(p_item);
		
		if(start==nullptr){
			start=l_item;
		} else {
			top->next=l_item;
		}
		top=l_item;
	}


	int getLength()
	{
		TLinkListItem<T> *l_current=start;
		int l_length=0;
		while(l_current){
			l_length++;
			l_current=l_current->getNext();
		}
		return l_length;
	}
};






#endif