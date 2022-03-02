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
	Queue* queue = new Queue();
	Stack* stack = new Stack();

	int len = strlen(input);
	for(int i = 0; i < len; i++){
		char token = input[i];
		if(isdigit(token)){
			queue->enqueue(token);
		}
		else if(token == '+' || token == '-' || token == '/' || token == '*' || token == '^'){
			char o1 = token;
			/*while(true){
				if(stack->empty()){
					break;
				}
				char o2 = stack->peek();
				if(o2 == '+' || o2 == '-' || o2 == '/' || o2 == '*' || o2 == '^' || o2 == ')'){
					if(pemdas(o2) > pemdas(o1)){

					}
					else if(pemdas(o2) == pemdas(o1) && o1 != '^'){

					}
					else{
						break;
					}
					queue->enqueue(stack->peek());
					stack->pop();
				}
				else{
					break;
				}
			}*/
			stack->push(o1);
		}
		else if(token == '('){
			stack->push('(');
		}
		else if(token == ')'){
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


int main(){
	char* input = "3*1+2";
	std::cout << "parsing " << input << "\n";
	Queue* q = postfix(input);
	while(!q->empty()){
		std::cout << q->dequeue();
	}
	std::cout << "\n";
}
