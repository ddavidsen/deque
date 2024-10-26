#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_LEN 100

typedef struct node {
	char* data;
	struct node* next;
} node;

typedef struct singlylinkedlist {
	struct node* head;
	struct node* tail;
} Deque;

void push_back(Deque* q, char* data);
void push_front(Deque* q, char* data);
char* pop_back(Deque* q);
char* pop_front(Deque* q);

int main() {

	FILE* file = fopen("C:/Users/ddavi/OneDrive/CSE240/names.txt", "r");
	if (file == NULL) {
		printf("Error opening file.\n");
		return 1;
	}

	Deque names = {NULL, NULL};

	//adds names from file to deque
	bool done = false;
	while (!done) {
		char* name = malloc(MAX_NAME_LEN);
		if (fscanf(file, "%s", name) == 1) {
			push_back(&names, name);
		}
		else {
			done = true;
		}
	}
	fclose(file);


	//user control begins
	char userInput;
	bool done2 = false;

	printf("To scroll through the names type\n");
	printf("f: forwards, b: backwards, q: quit\n");
	while (!done2) {
		scanf(" %c", &userInput);

		if (userInput == 'f') {
			printf("%s\n", pop_front(&names));
		}

		else if (userInput == 'b') {
			printf("%s\n", pop_back(&names));
		}

		else if (userInput == 'q') {
			done2 = true;
			printf("Bye!\n");
		}

		else {
			printf("Invalid input, try again.\n");
		}
	}

}

void push_back(Deque* q, char* data) {

	//allocates a new node
	node* newNode = (node*)malloc(sizeof(node));

	//set nodes data (name) and next pointer
	newNode->data = data;
	newNode->next = NULL;

	//if the list is empty, sets both head and tail to this new node
	if (q->head == NULL) {
		q->head = newNode;
		q->tail = newNode;
	}

	//otherwise, set tail to this new node
	else {
		q->tail->next = newNode;
		q->tail = newNode;
	}

}

void push_front(Deque* q, char* data) {

	//allocates a new node
	node* newNode = (node*)malloc(sizeof(node*));

	//sets nodes data (name)
	newNode->data = data;

	//if the list is empty, sets both head and tail to this new node
	if (q->head == NULL) {
		q->head = newNode;
		q->tail = newNode;
		newNode->next = NULL;
	}

	//otherwise, links this new node to the current head and updates head
	else {
		newNode->next = q->head;
		q->head = newNode;
	}

}

char* pop_back(Deque* q) {

	//checks if the deque is empty
	if (q->head == NULL) {
		return NULL;
	}

	//creates node to travel the deque
	node* current = q->head;
	char* data;

	//special case for only one node
	if (q->head == q->tail) {
		data = q->head->data; //stores data
		free(q->head);
		q->head = NULL;
		q->tail = NULL;
		return data;
	}

	//finds second to last node
	while (current->next != q->tail) {
		current = current->next;
	}

	//stores data and removes it
	data = q->tail->data;
	free(q->tail);
	q->tail = current;
	q->tail->next = NULL;

	push_front(q, data);
	return data;

}

char* pop_front(Deque* q) {

	//checks if the deque is empty
	if (q->head == NULL) {
		return NULL;
	}

	//stores the data
	char* data = q->head->data;

	//makes the next node the head
	node* temp = q->head;
	q->head = q->head->next;

	//if there was only one element, makes the tail empty
	if (q->head == NULL) {
		q->tail = NULL;
	}

	free(temp);
	push_back(q, data);
	return data;

}