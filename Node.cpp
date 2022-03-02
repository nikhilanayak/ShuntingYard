#include "Node.h"

// implementation for methods in Node.h

Node* Node::getNext(){
	return this->next;
}

char Node::getValue(){
	return this->value;
}

void Node::setNext(Node* next){
	this->next = next;
}

Node::Node(char s){
	this->value = s;
}

Node::~Node(){
}
