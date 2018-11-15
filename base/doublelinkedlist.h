#ifndef BASE_DOUBLELINKLIST_H_
#define BASE_DOUBLELINKLIST_H_
#include <stdio.h>
template<class T>
class TDoubleLinkedList;

/**
 * Double linked container for item added to the list
 * When the container is deleted then also the containing item is destroyed
 * 
 * \tparam T type of item.
 */

template<class T>
class TDoubleLinkedListItem
{
	friend class TDoubleLinkedList<T>;
private:
	T *item;   //Item
protected:	
        /**
        * The next item in the linked list.
        * NULL when item is last in list
        */
	TDoubleLinkedListItem<T> *next;	
	
	/**
	 * Previous item in linked list.
	 * NULL when first item in list
	 */
	TDoubleLinkedListItem<T> *prv;
	
	/**
	 *  Set next item in the list. This is called in TDoubleLinkedList because of friendship relation 
	 */
	inline void setNext(TDoubleLinkedListItem<T>* p_next) const{ next=p_next;}
	
	/**
	 * Set previous item in the list. This is called in TDoubleLinkedList because of friendship relation 
	 */
	inline void setPrv(TDoubleLinkedListItem<T>* p_prv) const{ prv=p_prv;}
public:		
	/**
	 * Get the item stored in the link list
	 * 
	 * \return link list item.
	 */
	
	inline T *getItem(){ return item;} //GetItem from container
	
	/**
	 *  Get the next item in linked list
	 * @see TDoubleLinkedListItem::next
	 */
	inline TDoubleLinkedListItem<T> *getNext(){ return next;} 	
	
	/**
	 *  Get the next item in linked list
	 * @see TDoubleLinkedListItem::next
	 */
	inline TDoubleLinkedListItem<T> *getPrv(){ return prv;}
	
	/**
	 * List item destructor
	 * The containing item is also deleted.
	 * When the list is deleted all the link list item are deleted and also the containing items.
	 */
	
	~TDoubleLinkedListItem()
	{
		delete item;
	}
	
/**
 * Constructor of container
 * When a item is added to the list, it is first wrapped in a container
 * and the container is added to the linkedlist.
 * 
 * \param p_item item added to the link list.
 */

	TDoubleLinkedListItem(T *p_item)
	{	
		item=p_item;
		next=nullptr;
		prv=nullptr;
	}
};


/**
 *  A double linked list.
 *  This list contains item of type T
 * 
 *  \tparam T type of item added to the list.
 */
template<class T>
class TDoubleLinkedList
{
private:
	
/**
 *  Start of list. When null the list is empty
 */
	TDoubleLinkedListItem<T> *start;   
/**
 * End of list, when null the list is empty.
 * Items are added to the end of the list
 */
	TDoubleLinkedListItem<T> *end;   

/**
 *  Length of list, is number of items
 */
	long length=0;
public:
/**
 * Get the start of the list
 * 
 * \return Start linked list item. 
 *         Can be null when the list is empty
 */
	inline TDoubleLinkedListItem<T> *getStart(){ return start;} 
/**
 * Get length of the list (stored in length property)
 * 
 * \return get the length of list in items.
 */
	inline long getLength(){ return length;}
	
/**
 * Checks if the list is empty
 * 
 * \return true  - the list is empty and contains no items
 *         false - the list contains items 
 */
	inline bool isEmpty(){ return start==nullptr;}
	
	
/**
 *  Initialize the linked list.
 */
	TDoubleLinkedList(){
		end=nullptr;
		start=nullptr;
	}
	
/**
 *  Deletes object.
 * 
 *  All items and linked list containers are cleared.
 */
	~TDoubleLinkedList(){
		clear();
	}
	
/**
 *  Clear the linked list.
 *  Also all containing items and their containers are deleted
 */
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
	
/**
 * Insert an container after another container (this can be used for moveing items  to another list or moving items inside the list)
 * 
 * \param p_at The new item is insert after this container item
 *             When p_at is null the item is added at the binning
 * \param p_item new container item is added to the list/ 
 */
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
	
/**
 * Move a linked list container up one item
 * 
 * \param p_item container item to move
 */
	void moveUp(TDoubleLinkedListItem<T> *p_item)
	{
		TDoubleLinkedListItem<T> *l_next=p_item->next;
		if(l_next != nullptr){
			cutOut(p_item);
			insertAfter(l_next,p_item);
		}
	}
	
/**
 * Move a linked list container down on item
 * 
 * \param p_item container item to move
 */

	void moveDown(TDoubleLinkedListItem<T> *p_item)
	{
		TDoubleLinkedListItem<T> *l_prv=p_item->prv;
		if(l_prv != nullptr){
			cutOut(p_item);
			insertAfter(l_prv->prv,p_item);
		}
	}

/**
 * CutOut a container from the linked list. The container and containing item are not delete
 * This route can be used to mvoe a item to another list of move the item to anther position
 * This can be done by calling fist cutout and than insertAt
 * 
 * \param p_item container item to cut out
 */
	
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
	
/**
 *  Delete item from the list. The item is deleted and also it's container
 * 
 * \param p_item item to delete
 */
	
	void del(TDoubleLinkedListItem<T> *p_item)
	{
		cutOut(p_item);
		delete p_item;
		length--;
	}
	
/**
 *  Append new item at the end of the list.
 *  The item is first wrapped in a double linked container and the the container is added tot he list.
 * 
 *  \param p_item item to add to the list.
 */
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

/**
 * Java style iterator for a double linked list
 * 
 * \tparam T Type of item of the list
 */

template<class T>
class TDoubleLinkedListIterator{
private:
/**
 *  Current item of iterator
 *  Can be null when end of list is reached
 */
	TDoubleLinkedListItem<T>  *current;
	
public:
/**
 *   Initialize linked list when list is a pointer
 *  
 *  \param p_list list to iterate
 */
	inline TDoubleLinkedListIterator(TDoubleLinkedList<T> &p_list){
		current=p_list.getStart();
	}
	
/**
 *  Initialize iterator when list is not  a pointer
 *  
 * \param p_list list to iterate
 */

	inline TDoubleLinkedListIterator(TDoubleLinkedList<T> *p_list){
		current=p_list->getStart();
	}
	
/**
 *  Checks if there is a next item or the end of the list is reached
 * 
 *  \return  true  there is a next item
 *           falee end of the list is reached
 */

	inline bool hasNext(){
		return current != nullptr;
	}

/**
 * Returns current item and forward the current item to the next item
 * 
 * \return returns current item. This method can return a null item when iterating after the end.
 */	
	inline  T * next(){
		if(current != nullptr){
			T *l_item=current->getItem();
			current=current->getNext();
			return l_item;
		}
		return nullptr;
	}
		
};

#endif //BASE_DOUBLELINKLIST_H_

