

#include "LinkedList.h"

#include <iostream>

using namespace std;



int main()

{

    LinkedList<int> myList;

    myList.insertFirst(5);
    myList.insertFirst(6);
    myList.insertFirst(7);
    myList.insertFirst(7);
    myList.insertFirst(7);
    cout << myList << endl;
    myList.insertLast(3);
    cout << myList << endl;
    myList.removeLast();
    cout << myList << endl;
    cout << myList.getLength() << endl;
    myList.reverse();
    cout << myList << endl;
    myList.printBackwards();



    return 0;

}