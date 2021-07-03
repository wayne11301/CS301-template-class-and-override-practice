#include <iostream>

#include <exception>

using namespace std;

template <class T>

class Node {

public:

    T data;

    Node<T>* prev, * next;

    Node(const T& d = T(), Node<T>* n = nullptr, Node<T>* p = nullptr) {

        data = d;

        prev = p;

        if (n)
            n->prev = this;
        if (p)
            p->next = this;

        next = n;

    }
    //remove helper
    void unlink() {
        if (next) {
            next->prev = nullptr;	//next.prev = nullptr
            next = nullptr;		//next = nullptr
        }
        if (prev) {
            prev->next = nullptr;	//prev.next = nullptr
            prev = nullptr;		//prev = nullptr
        }
    }
};

template <class T>

class LinkedList {

    friend ostream& operator<<(ostream& out, const LinkedList<T>& list) {
        out << "{ ";
        Node<T>* current = list.headPtr;	//"friend" allows access to private member vars

        while (current != nullptr) {		//iterates head, next1, next2...
            out << current->data << " ";
            current = current->next;
        }
        out << "}";

        return out;
    }

private:

    Node<T>* headPtr, * tailPtr;

    int length;

    void  copyList(Node<T>* p) {

        if (p == nullptr) return headPtr = tailPtr = nullptr;

        headPtr = new Node<T>(p->data);

        for (Node<T>* q = headPtr; p->next != nullptr; q = q->next, p = p->next) {

            q->next = new Node<T>(p->next->data, q);

        }

        tailPtr = p;
    }

public:

	LinkedList() {
		headPtr = nullptr;
		tailPtr = nullptr;
		length = 0;
	}

    LinkedList(const LinkedList& other) {
        length = other.length;		
        if (other.tailPtr == nullptr)
            tailPtr = nullptr;
        if (other.headPtr == nullptr)
            headPtr = nullptr;
        else {
            headPtr = new Node<T>(other.headPtr->data);	
            Node<T>* otherCurrent = other.headPtr->next;
            Node<T>* pre = headPtr;	

            while (otherCurrent != nullptr) {
                pre->next = new Node<T>(otherCurrent->data);	
                pre = pre->next;					
                otherCurrent = otherCurrent->next;		
            }
            tailPtr = pre;		
        }
    }

    ~LinkedList() {
        clear();
    }

    T& operator[] (int index) {
    }

    void insertFirst(const T& d) {
        Node<T>* toInsert = new Node<T>(d, headPtr,nullptr);
        headPtr = toInsert;	
        length++;

        //1 element list
        if (length == 1)
            tailPtr = headPtr;
    }

    void insertLast(const T& d) {
        Node<T>* toInsert = new Node<T>(d, nullptr, tailPtr);
        tailPtr = toInsert;		
        length++;

        //1 element list
        if (length == 1)
            headPtr = tailPtr;
    }

    void removeFirst() {
        if (headPtr == nullptr)
            return;	
        Node<T>* temp = headPtr;	
        headPtr = headPtr->next;	

        temp->unlink();	
        delete temp;
        length--;

        //0 element list
        if (length == 0)
            tailPtr = nullptr;
    }

    void removeLast() {
        if (tailPtr == nullptr)
            return;	
        Node<T>* temp = tailPtr;	
        tailPtr = tailPtr->prev;

        temp->unlink();
        delete temp;
        length--;

        //0 element list
        if (length == 0)
            headPtr = nullptr;
    }

    int getLength() const {
        return length;
    }

    bool isEmpty() {
        return headPtr == nullptr;
    }

    void clear() {
        while (!isEmpty())
            removeFirst();	
    }

    void printBackwards() const {
        if (tailPtr == nullptr) return;
        Node<T>* cur = tailPtr;

        cout << "{ ";
        while (cur) {
            cout << cur->data<<" ";
            cur = cur->prev;
        }

        cout << "} "<<endl;
    }

    void reverse() {
        if (headPtr == nullptr)
            return;

        Node<T>* cur = headPtr;			//tmp store head
        headPtr = tailPtr;					//head = tail; (swap)
        tailPtr = cur;						//tail = head; (swap)

        while (cur) {
            Node<T>* temp = cur->next;		//tmp store old next
            cur->next = cur->prev;			//(swap)
            cur->prev = temp;				//(swap)
            cur = temp;	
        }
    }
    
};
