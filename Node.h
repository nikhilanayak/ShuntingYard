#ifndef NODE_H
#define NODE_H


class Node{
	char value; // holds the student
	Node* next; // pointer to next node
public:	
	Node* getNext(); // getter for next
	char getValue(); // getter for student
	void setNext(Node*); // setter for next
	Node(char); // constructor
	~Node(); // destructor

};

#endif
