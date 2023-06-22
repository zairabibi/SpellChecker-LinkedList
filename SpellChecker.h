
#include <iostream>
#include <string>

template <typename T>
class Node {
public:
	T data; //to store the value
	Node<T> *next; //to store the address of the successor node

};

template <typename T>
class Dictionary
{
	Node<T> *head; //to indicate the head node
	Node<T> *last; //to indicate the end node
	Node<T> *ploc; //to store the location of the predecessor of a particular node
	int dictionarySize;

public:
	static int compareCorrect, compareMisspelled;

	Dictionary()
	{
		head = NULL;
		ploc = NULL;
		last = NULL;
		dictionarySize = 0;
	}

	void printList()
	{
		Node<T> *temp = head;

		//prints only when the list is not empty
		if (!isEmpty()) {
			while (temp != NULL) {
				std::cout << temp->data << " ";
				temp = temp->next;
			}
			return;
		}

		//if the list is empty, this message is printed.
		std::cout << "List is empty." << std::endl;
	}

	int getSize()
	{
		return --dictionarySize;
	}

	//function to indicate whether the list is empty
	//returns true if the list is empty
	bool isEmpty()
	{
		return head == NULL;
	}

	void insertAtFront(T value)
	{
		//newNode will store the value that we want to insert
		Node<T> *newNode = new Node<T>;
		newNode->data = value;

		//if the list isn't empty, only the start pointer will be updated
		//the start pointer will now point to newNode
		if (!isEmpty()) {
			newNode->next = head;
			head = newNode;
		}//end if

		//otherwise, both the start and last pointers will be updated
		//both the pointers will point to newNode as the list contains only one Node after insertion
		else {
			head = newNode;
			last = newNode;
		}//end else
	}

	void insertAtEnd(T value)
	{
		//newNode will store the value that we want to insert
		Node<T>* newNode = new Node<T>;
		newNode->data = value;

		//if the list isn't empty, then only the last pointer will be updated
		//the last pointer will now point to newNode
		if (!isEmpty()) {
			last->next = newNode;
		}

		//otherwise, both the start and last pointers will be updated
		//both the pointers will point to newNode as the list contains only one Node after insertion
		else {
			head = newNode;
		}
		last = newNode;
	}

	//find the position where the new value is to be inserted
	int compare(T value)
	{
		Node<T>* temp = head;
		ploc = NULL; //for head node, ploc is NULL 

		//while loop to search the value until we reach the end of list and the value remains greater than the values existing in the list
		while (temp != NULL && temp->data.compare(value) < 0) {

			compareCorrect++;

			//advancing temp and ploc if the value is not found
			ploc = temp;
			temp = temp->next;

			//if found, return 1
			if (temp->data.compare(value) == 0)
				return 1;

			compareMisspelled++;
		}

		return -1;
	}

	//find the position where the new value is to be inserted
	void find(T value)
	{
		Node<T>* temp = head;
		ploc = NULL; //for head node, ploc is NULL 

		//while loop to search the value until we reach the end of list and the value remains greater than the values existing in the list
		while (temp != NULL && temp->data.compare(value) < 0) {

			//advancing temp and ploc if the value is not found
			ploc = temp;
			temp = temp->next;
		}
	}

	void insert(T value)
	{
		//first the value will be searched to see if it already exists or not
		find(value);

		//ploc is equal to NULL, so the value will be inserted at front.
		if (ploc == NULL)
			insertAtFront(value);

		//ploc is not NULL. that means 
		// A) either the value should be inserted somewhere between the head node and end node
		// B) or the value should be inserted at the very end of the list
		else {

			//if the next field ploc does not point to any address, then the logical position of newNode is at the tail end of list
			if (ploc->next == NULL) {
				insertAtEnd(value); //call to function
			}//end if

			//otherwise, the logical position is somewhere between the list
			else
			{
				Node<T> *newNode = new Node<T>;
				newNode->data = value;

				//the pointers will be updated/
				newNode->next = ploc->next;
				ploc->next = newNode;
			}//end else
		}//end  else

		std::cout << "last: " << last->data << std::endl;
		dictionarySize++;
		std::cout << "size: " << dictionarySize << std::endl;


	}
};

template <typename T>
int Dictionary<T>::compareCorrect{ 0 };

template <typename T>
int Dictionary<T>::compareMisspelled = 0;