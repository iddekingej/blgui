#ifndef __DOUBLELINKLIST_H_
#define __DOUBLELINKLIST_H_
#include <stdio.h>
template<class T>
class TDoubleLinkedList;

// Container class for item with T
// Container is added to TLinklist

template<class T>
class TDoubleLinkedListItem
{
	friend class TDoubleLinkedList<T>;
private:
	T *item;   //Item
protected:
	TDoubleLinkedListItem<T> *next;	
	TDoubleLinkedListItem<T> *prv;
	inline void setNext(TDoubleLinkedListItem<T>* p_next){ next=p_next;}
	inline void setPrv(TDoubleLinkedListItem<T>* p_prv){ prv=p_prv;}
public:		
	inline T *getItem(){ return item;} //GetItem from container
	inline TDoubleLinkedListItem<T> *getNext(){ return next;} 	
	inline TDoubleLinkedListItem<T> *getPrv(){ return prv;}
	
	
	~TDoubleLinkedListItem()
	{
		delete item;
	}
	
//Constructor
//p_item : Item to add to list:
//See TLinkList::Append

	TDoubleLinkedListItem(T *p_item)
	{	
		item=p_item;
		next=nullptr;
		prv=nullptr;
	}
};


//Linkedlist 
//Create:  TLinkList<TMyObject> l_list()
//Append item  l_list->append(myObject) (myObject of type TMyObject)
//Get top:     l_link->getStart()
//When listis is destoyes item is also deleted

template<class T>
class TDoubleLinkedList
{
private:
	TDoubleLinkedListItem<T> *start;   //start of linklist
	TDoubleLinkedListItem<T> *end;     //last in linkedlist
	long length=0;
public:
	typedef TDoubleLinkedListItem<T> itemType;
	inline TDoubleLinkedListItem<T> *getStart(){ return start;} //start of linked list
	inline long getLength(){ return length;}
	inline bool isEmpty(){ return start==nullptr;}
	
	TDoubleLinkedList(){
		end=nullptr;
		start=nullptr;
	}
	~TDoubleLinkedList(){
		clear();
	}
	
	void clear()
	{
		TDoubleLinkedListItem<T> *l_current=start;
		TDoubleLinkedListItem<T> *l_next;
		while(l_current !=nullptr){
			l_next=l_current->next;
			delete l_current;
			l_current=l_next;
		}
		end=nullptr;
		start=nullptr;
		length=0;
	}
	
	void insertAfter(TDoubleLinkedListItem<T> *p_at,TDoubleLinkedListItem<T> *p_item)
	{
		if(p_at != nullptr){
			p_item->prv=p_at;
			p_item->next=p_at->next;
			if(p_at->next == nullptr){
				end=p_item;
			} else{
				p_at->next->prv=p_item;
			}
			p_at->next=p_item;			
		} else {
			p_item->next=start;
			start->prv=p_item;
			start=p_item;
			if(end==nullptr) end=p_item;
		}
		
	}
	
	void moveUp(TDoubleLinkedListItem<T> *p_item)
	{
		TDoubleLinkedListItem<T> *l_next=p_item->next;
		if(l_next != nullptr){
			cutOut(p_item);
			insertAfter(l_next,p_item);
		}
	}
	
	void moveDown(TDoubleLinkedListItem<T> *p_item)
	{
		TDoubleLinkedListItem<T> *l_prv=p_item->prv;
		if(l_prv != nullptr){
			cutOut(p_item);
			insertAfter(l_prv->prv,p_item);
		}
	}
	
	void cutOut(TDoubleLinkedListItem<T> *p_item)
	{
		if(p_item->prv != nullptr) p_item->prv->next=p_item->next;
		if(p_item->next != nullptr) p_item->next->prv=p_item->prv;
		if(p_item==start) start=p_item->next;
		if(p_item==end) end=p_item->prv;
		p_item->prv=nullptr;
		p_item->next=nullptr;
		length--;
	}
	
	void del(TDoubleLinkedListItem<T> *p_item)
	{
		cutOut(p_item);
		delete p_item;
		length--;
	}
	
	void append(T *p_item)
	{
		TDoubleLinkedListItem<T> *l_item=new TDoubleLinkedListItem<T>(p_item);
		
		if(start==nullptr){
			start=l_item;
		} else {
			end->next=l_item;
			l_item->prv=end;
		}
		end=l_item;
		length++;
	}

};

template<class T>
class TDoubleLinkedListIterator{
private:
	TDoubleLinkedListItem<T> *current;
	
public:
	inline TDoubleLinkedListIterator(TDoubleLinkedList<T> &p_list){
		current=p_list.getStart();
	}

	inline TDoubleLinkedListIterator(TDoubleLinkedList<T> *p_list){
		current=p_list->getStart();
	}
	
	inline bool hasNext(){
		return current != nullptr;
	}
	inline T* next(){
		if(current != nullptr){
			T *l_item=current->getItem();
			current=current->getNext();
			return l_item;
		}
		return nullptr;
	}
		
};




#endif

