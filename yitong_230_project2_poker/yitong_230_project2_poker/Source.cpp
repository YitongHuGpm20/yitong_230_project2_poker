#include<iostream>

using namespace std;

struct Node {
	int data;
	Node* next;
};

void CreateNode(Node*, int);
void FindLastNode();
void AddNode_emptylist(Node*, int);

int main() {
	Node* A; //create a list called A
	
	Node* cursor = new Node(); //add a node carries 2 
	cursor->data = 2;
	cursor->next = NULL;
	A = cursor;

	cursor = new Node();
	cursor->data = 4;
	cursor->next = NULL;

	Node* find = new Node(); //find the last node in the list
	while (find->next != NULL) {
		find = find->next;
	}
	find->next = cursor; //link the last node to the new node

	system("pause");
	return 0;
}

void CreateNode(Node* cursor, int x) {
	cursor = new Node();
	cursor->data = x;
	cursor->next = NULL;
}

void FindLastNode() {
	Node* find = new Node();
	while (find->next != NULL) {
		find = find->next;
	}
}

void AddNode_emptylist(Node* A, int x) {
	Node* cursor;
	CreateNode(cursor, x);
	A = cursor;
}

void AddNode() {
	FindLastNode();

}