/**
    list.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#ifndef _LIST_H
#define _LIST_H

template <class T> class ListNode {
	public:
		ListNode<T>(const T& inData) {
			data = inData;
			next = NULL;
			prev = NULL;
		}
	
		ListNode<T>() {
			next = NULL;
			prev = NULL;
		}
		
		~ListNode<T>() {
			if(next != NULL) {
				delete next;
			}
		}
		
		T &getData() {
			return data;
		}
		
		void setNext(ListNode<T> *n) {
			next = n;
		}
		
		void setPrevious(ListNode<T> *n) {
			prev = n;
		}
		
		ListNode<T> *getNext() {
			return next;
		}
		
		ListNode<T> *getPrevious() {
			return prev;
		}
		
		void removeFromList() {
			next->prev = prev;
			prev->next = next;
		}
		
		ListNode<T> *insertBefore(const T& toInsert, ListNode<T> *node) {
			ListNode<T> *newNode = new ListNode<T>(toInsert);
			if(node == NULL) {
				return newNode;
			}
			else {
				ListNode<T> *prev = node->getPrevious();
				node->setPrevious(newNode);
				if(prev != NULL) {
					prev->setNext(newNode);
				}
			}
			return newNode;
		}
		
		ListNode<T> *insertAfter(ListNode<T> *node) {
			ListNode<T> *nextNode = node->getNext();
			if(nextNode != NULL) {
				nextNode->setPrevious(this);
			}
			node->setNext(this);
			return this;
		}	
		
		ListNode<T>& operator=(const T &inData) {
			data = inData;
			return *this;
		}	
	
	private:
		ListNode<T> *next;
		ListNode<T> *prev;
		T data;

};

template <class T> class List {
	typedef ListNode<T> node;

	public:
		List<T>() : first(NULL), current(NULL), last(NULL), endOfList(false), count(0) {
		
		}
		
		~List<T>() {
			//A big problem with a lot of Linked List implementations is they leave
			// big chunks of memory lying around. Clean's the list prior to deletion.
			if(first != NULL && last != NULL) {
				node *tmp = last, tmp2;
				while(tmp != NULL) {
					tmp2 = tmp->getPrevious();
					delete tmp;
					tmp = tmp2;
				}	
			}
		}
		
		const unsigned int size() {
			return count;
		}
		
		node *getFirst() {
			return first;
		}
		
		node *getCurrent() {
			if(current == NULL) {
				current = first;
			}
			node *cN = current;
			current = current->getNext();
			return cN;
		}
		
		node *getLast() {
			return last;
		}
		
		bool EOL() {
			if(current == NULL) {
				endOfList = true;
				current = first;
				return true;
			}
			if(current == first && endOfList) {
				endOfList = false;
			}
			return endOfList;
		}
		
		void pushFront(const T &inData) {
			node *newNode = new ListNode<T>(inData);
			if(first != NULL) {
				first->setPrevious(newNode);
				newNode->setNext(first);
			}
			if(last == NULL) {
				last = first;
			}
			first = newNode;
			count++;
		}
		
		void pushBack(const T &inData) {
			node *newNode = new ListNode<T>(inData);
			if(last != NULL) {
				last->setNext(newNode);
				newNode->setPrevious(last);
				last = newNode;
				count++;
			}
			if(first == NULL && last == NULL) {
				first = newNode;
				last == newNode;
				count = 1;
			}
		}
		
		node *findInList(const T &inData) {
			if(first != NULL) {
				node *c = first;
				while(c != NULL) {
					if(c->getData() == inData) {
						return c;
					}
					c = c->getNext();
				}
			}
			return NULL;
		}
		
		void resetPos() {
			endOfList = false;
			current = first;
		}
		
		void recount() {
			unsigned int total = 0;
			node *c = first;
			while(c != NULL) {
				c = c->getNext();
				total++;
			}
			count = total;
		}
		
		void removeFromList(node *n) {
			n->getNext()->setPrevious(n->getPrevious());
			n->getPrevious()->setNext(n->getNext());
			n->setNext(NULL);
			n->setPrevious(NULL);
			delete n;
			count--;
		}
	
	private:
		bool endOfList;
		unsigned int count;
		
		node *first;
		node *current;
		node *last;
};

#endif //_LIST_H 
