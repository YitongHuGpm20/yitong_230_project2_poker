#include<iostream>
using namespace std;

struct Poker {
	int card;
	Poker* next;
};

struct Deck {
	Poker* head;
};

void CurrentMoney(int);
Deck* CreateDeck();
void AddHead(Deck*, int);
void AddTail(Deck*, int);
void PrintDeck(Deck*);
int CountCards(Deck*);
int FindCard(Deck*, int);
void DeleteHead(Deck*);
void DeleteCard(Deck*, int);
void RemoveDeck(Deck*);

/*
Poker* CreateCard(Poker*, int);
void FindLastCard(Poker*);
Poker* AddCard_emptydeck(Poker*, int, Poker*);
Poker* AddCardAtEnd(int);
Poker* AddCardAtBegin(int, Poker*);
void PrintDeck(Poker*);*/

int main() {
	system("color f1");
	CurrentMoney(5);
	
	Deck* deck = CreateDeck();
	cout << deck->head << endl;//useage of creat a linked list

	AddTail(deck, 42);
	AddTail(deck, 55);
	AddTail(deck, 78);
	AddHead(deck, 111);
	DeleteCard(deck, 2);
	PrintDeck(deck);

	/*
	//test linked list
	Poker* deck = NULL;
	Poker* head = NULL;
	head = AddCard_emptydeck(deck, 1, head);
	head = AddCardAtEnd(2);
	head = AddCardAtEnd(3);
	PrintDeck(head);
	*/

	system("pause");
	return 0;
}

void CurrentMoney(int money) {
	cout << "You currently have $" << money << "." << endl;
}

Deck* CreateDeck() {
	Deck* deck = new Deck;
	deck->head = NULL;
	return deck;
}

void AddHead(Deck* deck, int card) {
	Poker* add = new Poker;
	add->card = card;
	add->next = deck->head;
	deck->head = add;
}

void AddTail(Deck* deck, int card) {
	if (deck->head == NULL) { //when the deck is empty
		AddHead(deck, card);
		return;
	}
	Poker* last = deck->head;
	while (last->next != NULL) {
		last = last->next;
	} //find the last card in the deck
	Poker* add = new Poker; //add the new card at the end
	add->card = card;
	add->next = NULL;
	last->next = add;
}

void PrintDeck(Deck* deck) {
	Poker* item = deck->head;
	while (item != NULL) {
		cout << item->card;
		if (item->next != NULL)
			cout << ", ";
		item = item->next;
	}
	cout << endl;
}

int CountCards(Deck* deck) {
	int count = 0;
	Poker* item = deck->head;
	while (item != NULL) {
		count++;
		item = item->next;
	}
	return count;
}

int FindCard(Deck* deck, int index) {
	Poker* item = deck->head;
	while (index > 0) {
		item = item->next;
		index--;
	}
	return item->card;
}

void DeleteHead(Deck* deck) {
	if (deck->head == NULL) {
		cout << "Deck already empty!" << endl;
		return;
	}
	Poker* item = deck->head;
	deck->head = item->next;
	delete item;
}

void DeleteCard(Deck* deck, int index) {
	if (index == 0) {
		DeleteHead(deck);
		return;
	}
	Poker* prev = deck->head;
	while (index-1 > 0) {
		prev = prev->next;
		index--;
	}
	Poker* item = prev->next;
	prev->next = item->next;
	delete item;
}

void RemoveDeck(Deck* deck) {
	Poker* item = deck->head;
	while (item != NULL) {
		Poker* temp = item;
		item = item->next;
		delete temp;
	}
	delete deck;
}

/*
Poker* CreateCard(Poker* cursor, int x) {
	cursor->card = x;
	cursor->next = NULL;
	return cursor;
}

void FindLastCard(Poker* find) {
	find = new Poker();
	while (find->next != NULL) {
		find = find->next;
	}
}

Poker* AddCard_emptydeck(Poker* deck, int x, Poker* head) {
	Poker* cursor = new Poker();
	CreateCard(cursor, x);
	deck = cursor;
	head = cursor;
	return head;
}

Poker* AddCardAtEnd(int x) {
	Poker* cursor = new Poker();
	CreateCard(cursor, x);
	Poker* find = new Poker();
	FindLastCard(find);
	find->next = cursor;
	return cursor;
}

Poker* AddCardAtBegin(int x, Poker* head) {
	Poker* cursor = new Poker();
	cursor->card = x;
	cursor->next = NULL;
	if (head != NULL)
		cursor->next = head;
	head = cursor;
	return head;
}

void PrintDeck(Poker* head) {
	Poker* cursor = new Poker();
	cursor = head;
	while (cursor != NULL) {
		cout << cursor->next << endl;
		cursor = cursor->next;
	}
}

void DrawCard() {
	cout << "----------  " << endl;
	cout << "|1       |  " << endl;
	cout << "|   /\\   |  " << endl;
	cout << "|  /  \\  |  " << endl;
	cout << "|  \\  /  |  " << endl;
	cout << "|   \\/   |  " << endl;
	cout << "|       1|  " << endl;
	cout << "----------  " << endl;
}*/