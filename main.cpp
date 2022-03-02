#include <iostream>

typedef struct Node{
	char value;
	Node* next;
} Node;





void push(Node*& s, Node* value){
	Node* head = s;

	if(head == NULL){
		head = value;
		return;
	}

	s = value;
	s->next = head;
}

Node* pop(Node*& s){
	Node* popped = s;
	if(s != NULL){
		s = s->next;
	}
	return popped;
}

Node* peek(Node* s){
	Node* popped = s;
	if(popped != NULL) popped->next = NULL;
	return popped;

}

Node* mknode(char value){
	Node* n = new Node();
	n->value = value;
	return n;
}



void enqueue(Node*& s, Node* value){

	if(s == NULL){
		s = value;	
		return;
	}

	Node* head = s;
	while(head->next != NULL){
		head = head->next;
	}
	head->next = value;
}

Node* dequeue(Node*& s){
	Node* popped = s;
	s = s->next;
	return popped;
}

typedef struct Tree{
	Node* value;
	Tree* left;
	Tree* right;
} Tree;



Node* str_to_queue(char* in){
	Node* head = mknode(*in);
	in++;
	while(*in != 0){
		enqueue(head, mknode(*in));
		in++;
	}
	return head;
	
}

void print_queue(Node* q){
	std::cout << "==\n";
	while(q != NULL){
		std::cout << "|" << dequeue(q)->value << "|\n";
		std::cout << "==\n";	
	}
}


int prec(char c) {
    if (c == '(')
	return 4;
    else if(c == '^')
        return 3;
    else if(c == '/' || c=='*')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else
        return -1;
}

Node* make_postfix(char* math){
	Node* stack = NULL;	
	Node* queue = NULL;


	for(int i = 0; i < strlen(math); i++){
		char c = math[i];
		if(c == '('){
			push(stack, mknode('('));
		}
		else if(c == ')'){
			while(true){
				Node* curr = pop(stack);
				if(curr->value == '('){
					break;
				}
				else{
					enqueue(queue, curr);
				}
			}
		}
		else{
			while(stack != NULL && prec(math[i]) <= prec(peek(stack)->value)){
				pop(stack);
			}
			enqueue(queue, mknode(c));
			std::cout << "nq: " << c << "\n";
		}
	}
	while(stack != NULL){
		enqueue(queue, pop(stack));
	}

	return queue;
}


bool isfunc(char c){
	return c == '+' || c == '-' || c == '/' || c == '*' || c == '^';
}

Node* postfix(char* input){
	Node* stack = NULL;
	Node* queue = NULL;

	while((*input) != 0){
		char token = *(input);
		input++;
		if(token >= '0' && token <= '9'){
			enqueue(queue, mknode(token));
		}
		else if(isfunc(token)){
			Node* o1 = mknode(token);
			while(true){
				if(stack == NULL){
					break;
				}
				Node* o2 = peek(stack);
				if(o1->value != '^' && prec(o1->value) == prec(o2->value)){
					break;
				}
				if(prec(o1->value) >= prec(o2->value)){
					break;
				}
				enqueue(queue, pop(stack));
				push(stack, o1);

			}


			while(stack != NULL && peek(stack)->value != '('){
				
			}
		}
		else if(token == '('){
			push(stack, mknode(token));
		}
		else if(token == ')'){
			while(peek(stack) != NULL && peek(stack)->value != '('){
				enqueue(queue, pop(stack));
			}
			pop(stack);
			enqueue(queue, pop(stack));
		}

	}
	while(stack != NULL){
		enqueue(queue, pop(stack));	
	}
	return queue;
}



int main(){
	//char* in = (char*)"hello";
	//Node* q = str_to_queue(in);
	//print_queue(q);
	
	//char* exp = "a+b*(c^d-e)^(f+g*h)-i";
	char* exp = "1+2*3+1-3/1";
	Node* out = postfix(exp);
	while(out != NULL){
		std::cout << dequeue(out)->value;
	}


}
