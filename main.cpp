#ifndef H_UnorderedLinkedList
#define H_UnorderedLinkedList

#include "linkedList.h"

using namespace std;

template <class Type>
class unorderedLinkedList: public linkedListType<Type>
{
public:
bool search(const Type& searchItem) const;
//Function to determine whether searchItem is in the list.
//Postcondition: Returns true if searchItem is in the
// list, otherwise the value false is
// returned.

void insertFirst(const Type& newItem);
//Function to insert newItem at the beginning of the list.
//Postcondition: first points to the new list, newItem is
// inserted at the beginning of the list,
// last points to the last node in the
// list, and count is incremented by 1.

void insertLast(const Type& newItem);
//Function to insert newItem at the end of the list.
//Postcondition: first points to the new list, newItem
// is inserted at the end of the list,
// last points to the last node in the
// list, and count is incremented by 1.

void deleteNode(const Type& deleteItem);
//Function to delete deleteItem from the list.
//Postcondition: If found, the node containing
// deleteItem is deleted from the list.
// first points to the first node, last
// points to the last node of the updated
// list, and count is decremented by 1.
};


template <class Type>
bool unorderedLinkedList<Type>::
search(const Type& searchItem) const
{
nodeType<Type> *current; //pointer to traverse the list
bool found = false;

current = this->first; //set current to point to the first
//node in the list

while (current != nullptr && !found) //search the list
if (current->info == searchItem) //searchItem is found
found = true;
else
current = current->link; //make current point to
//the next node
return found;
}//end search

template <class Type>
void unorderedLinkedList<Type>::insertFirst(const Type& newItem)
{
nodeType<Type> *newNode; //pointer to create the new node

newNode = new nodeType<Type>; //create the new node

newNode->info = newItem; //store the new item in the node
newNode->link = this->first; //insert newNode before first
this->first = newNode; //make first point to the
//actual first node
this->count++; //increment count

if (this->last == nullptr) //if the list was empty, newNode is also
//the last node in the list
this->last = newNode;
}//end insertFirst

template <class Type>
void unorderedLinkedList<Type>::insertLast(const Type& newItem)
{
nodeType<Type> *newNode; //pointer to create the new node

newNode = new nodeType<Type>; //create the new node

newNode->info = newItem; //store the new item in the node
newNode->link = nullptr; //set the link field of newNode
//to nullptr

if (this->first == nullptr) //if the list is empty, newNode is
//both the first and last node
{
this->first = newNode;
this->last = newNode;
this->count++; //increment count
}
else //the list is not empty, insert newNode after last
{
this->last->link = newNode; //insert newNode after last
this->last = newNode; //make last point to the actual
//last node in the list
this->count++; //increment count
}
}//end insertLast


template <class Type>
void unorderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
nodeType<Type> *current; //pointer to traverse the list
nodeType<Type> *trailCurrent; //pointer just before current
bool found;

if (this->first == nullptr) //Case 1; the list is empty.
cout << "Cannot delete from an empty list."
<< endl;
else
{
if (this->first->info == deleteItem) //Case 2
{
current = this->first;
this->first = this->first->link;
this->count--;
if (this->first == nullptr) //the list has only one node
this->last = nullptr;
delete current;
}
else //search the list for the node with the given info
{
found = false;
trailCurrent = this->first; //set trailCurrent to point to the first node
current = this->first->link; //set current to point to the second node

while (current != nullptr && !found)
{
if (current->info != deleteItem)
{
trailCurrent = current;
current = current-> link;
}
else
found = true;
}//end while

if (found) //Case 3; if found, delete the node
{
trailCurrent->link = current->link;
this->count--;

if (this->last == current) //node to be deleted was the last node
this->last = trailCurrent; //update the value of last
delete current; //delete the node from the list
}
else
cout << "The item to be deleted is not in "
<< "the list." << endl;
}//end else
}//end else
}//end deleteNode


#endif
intLinkedList.cpp:

#include <iostream>
#include "intLinkedList.h"

using namespace std;

void intLinkedList:: splitEvensOddsList(intLinkedList &evensList, intLinkedList &oddsList)
{
nodeType<int> *current, *evensFirst, *evensLast, *oddsFirst, *oddsLast;
current = first;
first = first->link;



while (current != nullptr)
{
if (current->info %2 != 0)
{
if (oddsList.first == nullptr)
{
oddsList.first = current;
oddsList.last = current;
oddsList.count ++;
oddsList.last->link = nullptr;
}
else
{
oddsList.last->link = current;
oddsList.last = current;
oddsList.count ++;
oddsList.last->link = nullptr;
}
}
else if (current->info%2 == 0)
{
if (evensList.first == nullptr)
{
evensList.first = current;
evensList.last = current;
evensList.count ++;
evensList.last->link = nullptr;
}
else
{
evensList.last->link = current;
evensList.last = current;
evensList.count ++;
evensList.last->link = nullptr;
}
}
current = first;
if (first == nullptr)
{
break;
}
first = first->link;
}

cout << "Evens List: ";
evensList.print();
cout << endl;
cout << "Odds list: ";
oddsList.print();

}

intLinkedList::intLinkedList()
{
first = nullptr;
nodeType<int> *last = nullptr;
nodeType<int> *current = first;
int count = 0;
};

intLinkedList.h:

#ifndef H_intLinkedList
#define H_intLinkedList

#include "unorderedLinkedList.h"

#include <iostream>

using namespace std;

class intLinkedList: public unorderedLinkedList<int>
{
public:
void splitEvensOddsList (intLinkedList &evensList, intLinkedList &oddsList);
//This function rearranges the nodes of the linked list so that
// evensList consists of even integers and oddsList consists of
// odd integers
//Postcondition: evensList consists of even integers. oddsList
// consists of odd integers. The original list is empty.

intLinkedList();
//constructor


};
#endif
linkedList.h:

#ifndef H_LinkedListType
#define H_LinkedListType

#include <iostream>
#include <cassert>

using namespace std;

//Definition of the node

template <class Type>
struct nodeType
{
Type info;
nodeType<Type> *link;
};

template <class Type>
class linkedListIterator
{
public:
linkedListIterator();
//Default constructor
//Postcondition: current = nullptr;

linkedListIterator(nodeType<Type> *ptr);
//Constructor with a parameter.
//Postcondition: current = ptr;

Type operator*();
//Function to overload the dereferencing operator *.
//Postcondition: Returns the info contained in the node.

linkedListIterator<Type> operator++();
//Overload the pre-increment operator.
//Postcondition: The iterator is advanced to the next
// node.

bool operator==(const linkedListIterator<Type>& right) const;
//Overload the equality operator.
//Postcondition: Returns true if this iterator is equal to
// the iterator specified by right,
// otherwise it returns the value false.

bool operator!=(const linkedListIterator<Type>& right) const;
//Overload the not equal to operator.
//Postcondition: Returns true if this iterator is not
// equal to the iterator specified by
// right; otherwise it returns the value
// false.

private:
nodeType<Type> *current; //pointer to point to the current
//node in the linked list
};

template <class Type>
linkedListIterator<Type>::linkedListIterator()
{
current = nullptr;
}
template <class Type>
linkedListIterator<Type>::
linkedListIterator(nodeType<Type> *ptr)
{
current = ptr;
}
template <class Type>
Type linkedListIterator<Type>::operator*()
{
return current->info;
}
template <class Type>
linkedListIterator<Type> linkedListIterator<Type>::
operator++()
{
current = current->link;

return *this;
}
template <class Type>
bool linkedListIterator<Type>::operator==
(const linkedListIterator<Type>& right) const
{
return (current == right.current);
}
template <class Type>
bool linkedListIterator<Type>::operator!=
(const linkedListIterator<Type>& right) const
{
return (current != right.current);
}


//***************** class linkedListType ****************

template <class Type>
class linkedListType
{
public:
const linkedListType<Type>& operator=
(const linkedListType<Type>&);
//Overload the assignment operator.

void initializeList();
//Initialize the list to an empty state.
//Postcondition: first = nullptr, last = nullptr,
// count = 0;

bool isEmptyList() const;
//Function to determine whether the list is empty.
//Postcondition: Returns true if the list is empty,
// otherwise it returns false.

void print() const;
//Function to output the data contained in each node.
//Postcondition: none

void reversePrint() const;
//Function to output the data in reverse (starting from the first)
void reversePrint(nodeType<Type> *current) const;
//Function to output the data in reverse starting from current)


int length() const;
//Function to return the number of nodes in the list.
//Postcondition: The value of count is returned.

void destroyList();
//Function to delete all the nodes from the list.
//Postcondition: first = nullptr, last = nullptr,
// count = 0;

Type front() const;
//Function to return the first element of the list.
//Precondition: The list must exist and must not be
// empty.
//Postcondition: If the list is empty, the program
// terminates; otherwise, the first
// element of the list is returned.

Type back() const;
//Function to return the last element of the list.
//Precondition: The list must exist and must not be
// empty.
//Postcondition: If the list is empty, the program
// terminates; otherwise, the last
// element of the list is returned.

virtual bool search(const Type& searchItem) const = 0;
//Function to determine whether searchItem is in the list.
//Postcondition: Returns true if searchItem is in the
// list, otherwise the value false is
// returned.

virtual void insertFirst(const Type& newItem) = 0;
//Function to insert newItem at the beginning of the list.
//Postcondition: first points to the new list, newItem is
// inserted at the beginning of the list,
// last points to the last node in the list,
// and count is incremented by 1.

virtual void insertLast(const Type& newItem) = 0;
//Function to insert newItem at the end of the list.
//Postcondition: first points to the new list, newItem
// is inserted at the end of the list,
// last points to the last node in the
// list, and count is incremented by 1.

virtual void deleteNode(const Type& deleteItem) = 0;
//Function to delete deleteItem from the list.
//Postcondition: If found, the node containing
// deleteItem is deleted from the list.
// first points to the first node, last
// points to the last node of the updated
// list, and count is decremented by 1.

linkedListIterator<Type> begin();
//Function to return an iterator at the begining of
//the linked list.
//Postcondition: Returns an iterator such that current
// is set to first.

linkedListIterator<Type> end();
//Function to return an iterator one element past the
//last element of the linked list.
//Postcondition: Returns an iterator such that current
// is set to nullptr.

linkedListType();
//Default constructor
//Initializes the list to an empty state.
//Postcondition: first = nullptr, last = nullptr,
// count = 0;

linkedListType(const linkedListType<Type>& otherList);
//copy constructor

~linkedListType();
//Destructor
//Deletes all the nodes from the list.
//Postcondition: The list object is destroyed.

protected:
int count; //variable to store the number of
//elements in the list
nodeType<Type> *first; //pointer to the first node of the list
nodeType<Type> *last; //pointer to the last node of the list

private:
void copyList(const linkedListType<Type>& otherList);
//Function to make a copy of otherList.
//Postcondition: A copy of otherList is created and
// assigned to this list.
};


template <class Type>
bool linkedListType<Type>::isEmptyList() const
{
return (first == nullptr);
}

template <class Type>
linkedListType<Type>::linkedListType() //default constructor
{
first = nullptr;
last = nullptr;
count = 0;
}

template <class Type>
void linkedListType<Type>::destroyList()
{
nodeType<Type> *temp; //pointer to deallocate the memory
//occupied by the node
while (first != nullptr) //while there are nodes in
{ //the list
temp = first; //set temp to the current node
first = first->link; //advance first to the next node
delete temp; //deallocate the memory occupied by temp
}
last = nullptr; //initialize last to nullptr; first has
//already been set to nullptr by the while loop
count = 0;
}

template <class Type>
void linkedListType<Type>::initializeList()
{
destroyList(); //if the list has any nodes, delete them
}

template <class Type>
void linkedListType<Type>::print() const
{
nodeType<Type> *current; //pointer to traverse the list

current = first; //set current so that it points to
//the first node
while (current != nullptr) //while more data to print
{
cout << current->info << " ";
current = current->link;
}
}//end print

template <class Type>
void linkedListType<Type>::reversePrint() const
{
reversePrint(first);
}

template <class Type>
void linkedListType<Type>::reversePrint(nodeType<Type> *current) const
{
if (current != nullptr)
{
reversePrint(current->link); //print the tail
cout << current->info << " "; //print the node
}
}

template <class Type>
int linkedListType<Type>::length() const
{
return count;
} //end length

template <class Type>
Type linkedListType<Type>::front() const
{
assert(first != nullptr);

return first->info; //return the info of the first node
}//end front

template <class Type>
Type linkedListType<Type>::back() const
{
assert(last != nullptr);

return last->info; //return the info of the last node
}//end back

template <class Type>
linkedListIterator<Type> linkedListType<Type>::begin()
{
linkedListIterator<Type> temp(first);

return temp;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::end()
{
linkedListIterator<Type> temp(nullptr);

return temp;
}

template <class Type>
void linkedListType<Type>::copyList
(const linkedListType<Type>& otherList)
{
nodeType<Type> *newNode; //pointer to create a node
nodeType<Type> *current; //pointer to traverse the list

if (first != nullptr) //if the list is nonempty, make it empty
destroyList();

if (otherList.first == nullptr) //otherList is empty
{
first = nullptr;
last = nullptr;
count = 0;
}
else
{
current = otherList.first; //current points to the list to be copied
count = otherList.count;
//copy the first node
first = new nodeType<Type>; //create the node
first->info = current->info; //copy the info
first->link = nullptr; //set the link field of the node to nullptr
last = first; //make last point to the first node
current = current->link; //make current point to the next node
//copy the remaining list
while (current != nullptr)
{
newNode = new nodeType<Type>; //create a node
newNode->info = current->info; //copy the info
newNode->link = nullptr; //set the link of newNode to nullptr
last->link = newNode; //attach newNode after last
last = newNode; //make last point to the actual last node
current = current->link; //make current point to the next node
}//end while
}//end else
}//end copyList

template <class Type>
linkedListType<Type>::~linkedListType() //destructor
{
destroyList();
}//end destructor

template <class Type>
linkedListType<Type>::linkedListType
(const linkedListType<Type>& otherList)
{
first = nullptr;
copyList(otherList);
}//end copy constructor

//overload the assignment operator
template <class Type>
const linkedListType<Type>& linkedListType<Type>::operator=
(const linkedListType<Type>& otherList)
{
if (this != &otherList) //avoid self-copy
{
copyList(otherList);
}//end else

return *this;
}

#endif
main.cpp:

#include <iostream>
#include "unorderedLinkedList.h"
#include "intLinkedList.h"

using namespace std;

int main()
{
intLinkedList mainList, evensList, oddsList;

int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};


for (int i = 0; i < 10; i ++)
{
int item = values[i];
mainList.insertLast(item);
}

cout << "Main list after initiating: ";
mainList.print();
cout << endl;

mainList.splitEvensOddsList(evensList, oddsList);
cout << endl;
cout << "Main list after processing: ";
mainList.print();
return 0;
}
