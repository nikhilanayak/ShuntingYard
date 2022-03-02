#include <iostream>

typedef struct Node{
	char value;
	Node* next;
} Node;


class Stack{
Node* head = NULL;
public:

	void pop(){
		this->head = head->next;	
	}

	char peek(){
		return head->value;
	}

	void push(char c){
		Node* n = new Node();
		n->value = c;
		n->next = head;
		this->head = n;
	}
	bool empty(){
		return head == NULL;
	}
};


class Queue{
Node* head = NULL;
public:
	void enqueue(char c){

		Node* n = new Node();
		n->value = c;
		n->next = NULL;

		if(this->head == NULL){
			this->head = n;
			return;
		}

		Node* curr = this->head;
		while(curr->next != NULL){
			std::cout << curr->value;
			curr = curr->next;

		}
		curr->next = n;
	}

	char dequeue(){
		char c = head->value;
		head = head->next;
		return c;
	}

	bool empty(){
		return head == NULL;
	}

};


int pemdas(char c){
	if(c == '+' || c == '-') return 1;
	if(c == '*' || c == '/') return 2;
	if(c == '^') return 3;
	return 0;
}

Queue* postfix(char* input){
	Queue* q = new Queue();
	Stack* s = new Stack();


	int size = strlen(input);
	for(int i = 0; i < size; i++){
		char token = input[i];
		if(isdigit(token)){
			q->enqueue(token);
		}
		else if(token == '^' || token == '*' || token == '+' || token == '-' || token == '/'){
			while(!s->empty() && s->peek() != '(' && pemdas(s->peek()) > pemdas(token) && token != '^'){
				q->enqueue(s->peek());
				s->pop();
			}
			s->push(token);
		}
		else if(token == '('){
			s->push(token);
		}
		else if(token == ')'){
			while(true){
				if(s->peek() == '('){
					s->pop();
					break;
				}
				else{
					q->enqueue(s->peek());
					s->pop();
				}
			}
		}
		else{
			while(!s->empty()){
				q->enqueue(s->peek());
				s->pop();
			}
		}
	}
	return q;
}


int main(){
	char* input = "3*1+2";
	Queue* q = postfix(input);
	while(!q->empty()){
		std::cout << q->dequeue();
	}
}
