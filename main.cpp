/*
 Implementation of the Shunting Yard Algorithm Written By Nikhil Nayak
 The Shunting Yard algorithm is used for parsing logical expressions like mathematical expressions
 This program uses Linked Lists and Trees for its implementation

 June 11, 2022
 */


#include <iostream>

typedef struct Node{ // used like a Linked List. Also used for stack/queue
	char value;
	Node* next;
} Node;



class Tree{ // Tree of chars
public:
Tree* left;
Tree* right;
Tree* more; // if we need more data (for stack object). Kinda like "middle" if we wanted to use our tree as a linked list
char data;

	Tree(char data){
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}

};

class Stack{
Node* head = NULL;
public:

	void pop(){ // removes an element
		this->head = head->next;
	}

	char peek(){ // prints an element
		return head->value;
	}

	void push(char c){ // adds an element
		Node* n = new Node();
		n->value = c;
		n->next = head;
		this->head = n;
	}
	bool empty(){ // checks if empty
		return head == NULL;
	}
};


class BTStack{ // holds a stack of binary tree nodes
Tree* head = NULL;
public:
	void pop(){
		if(head == NULL){
			//std::cout << "empty\n";
		}
		else{
			this->head = head->more;
		}
	}

	Tree* peek(){ // peeks (like stack)
		return head;
	}

	void push(Tree* in){ // pushes (like stack)
		in->more = head;
		this->head = in;
	}
	bool empty(){ // checks if empty
		return head == NULL;
	}
};



class Queue{ // stack but FIFO
Node* head = NULL;
public:
	void enqueue(char c){ // adds

		Node* n = new Node();
		n->value = c;
		n->next = NULL;

		if(this->head == NULL){
			this->head = n;
			return;
		}

		Node* curr = this->head;
		while(curr->next != NULL){
			//std::cout << curr->value;
			curr = curr->next;

		}
		curr->next = n;
	}

	char dequeue(){ // removes
		char c = head->value;
		head = head->next;
		return c;
	}

	bool empty(){
		return head == NULL;
	}

};


int pemdas(char c){ // precedence of operators (or 0 if not operator)
	if(c == '+' || c == '-') return 1;
	if(c == '*' || c == '/') return 2;
	if(c == '^') return 3;
	return 0;
}



Queue* make_postfix(char* input){ // infix -> postfix
	Queue* queue = new Queue(); // output queue
	Stack* stack = new Stack(); // output stack

	int len = strlen(input);
	for(int i = 0; i < len; i++){ // iter over tokens
		char token = input[i];
		if(token == ' '){
			continue;
		}
		if(isdigit(token)){ // shunt to queue
			queue->enqueue(token);
		}
		else if(token == '+' || token == '-' || token == '/' || token == '*' || token == '^'){ // shunt to stack
			char o1 = token;
			while(true){
				if(stack->empty()){
					break;
				}
				char o2 = stack->peek();
				if(o2 == '+' || o2 == '-' || o2 == '/' || o2 == '*' || o2 == '^' || o2 == ')'){
					if(pemdas(o2) > pemdas(o1)){ // operator precedence (old operator is > new operator)

					}
					else if(pemdas(o2) == pemdas(o1) && o1 != '^'){ // operators are the same (^ is right associative)

					}
					else{
						// otherwise dont shunt from stack -> queue
						break;
					}
					queue->enqueue(stack->peek());
					stack->pop(); // peek doesn't remove, pop does
				}
				else{
					break;
				}
			}
			stack->push(o1);
		}
		else if(token == '('){ // add ( as is
			stack->push('(');
		}
		else if(token == ')'){ // when 
			while(stack->peek() != '('){
				queue->enqueue(stack->peek());
				stack->pop();
			}
			stack->pop();
		}
	}
	while(!stack->empty()){
		queue->enqueue(stack->peek());
		stack->pop();
	}
	return queue;
}


Tree* treeify(char* infix){
	Queue* qHead = make_postfix(infix);
	


	BTStack* stack = new BTStack();

	Tree* head = new Tree(' ');
	while(!qHead->empty()){
		char data = qHead->dequeue();	
		Tree* t = new Tree(data);
		if(pemdas(data) == 0){ // if not operator
			stack->push(t);
		}
		else{

			t->right = stack->peek();
			stack->pop();

			t->left = stack->peek();
			stack->pop();

			stack->push(t);

			head = t;
		}
	}

	if(!stack->empty()){
	}

	return head;
}


void postfix(Tree* tree){
	if(tree->left != NULL){
		postfix(tree->left);
	}
	if(tree->right != NULL){
		postfix(tree->right);
	}
	std::cout << tree->data;
}

void prefix(Tree* tree){
	std::cout << tree->data;
	if(tree->left != NULL){
		prefix(tree->left);
	}
	if(tree->right != NULL){
		prefix(tree->right);
	}
}

void infix(Tree* tree){
	if(tree->right != NULL){
		infix(tree->right);
	}

	std::cout << tree->data;

	if(tree->left != NULL){
		infix(tree->left);
	}
	
}




void print_tree(Tree* tree, int depth){
	if(tree == NULL){
		return;
	}

	for(int i = 0; i < depth; i++){std::cout << "\t";}
	std::cout << tree->data << "\n";
	print_tree(tree->left, depth + 1);
	print_tree(tree->right, depth + 1);

}




int main(){
	while(true){
		std::cout << "infix: ";
		char in[256];
		std::cin >> in;

		Tree* t = treeify(in);

		while(true){
			std::cout << "Input letter (i=infix, p=postfix, r=prefix): ";
			char c;
			std::cin >> c;
			if(c == 'i'){
				infix(t);
				std::cout << "\n";
				break;	
			}
			else if(c == 'p'){
				postfix(t);
				std::cout << "\n";
				break;	
			}
			else if(c == 'r'){
				prefix(t);
				std::cout << "\n";
				break;	
			}

		}

	}

}
