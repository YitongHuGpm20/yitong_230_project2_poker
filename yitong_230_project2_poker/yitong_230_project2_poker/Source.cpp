#include<iostream>
#include<string>
using namespace std;

struct Poker {
	int card;
	string suit;
	Poker* next;
};

struct Deck {
	Poker* head;
};

void CurrentMoney(int);
Deck* CreateDeck();
void AddHead(Deck*, int, int);
void AddTail(Deck*, int, int);
void StartupDeck(Deck*);
void PrintDeck(Deck*);
int CountCards(Deck*);
int FindCard(Deck*, int);
void DeleteHead(Deck*);
void DeleteCard(Deck*, int);
void RemoveDeck(Deck*);

string suits[4] = { "Diamonds", "Clubs", "Spades", "Hearts" };

int main() {
	system("color f1");
	CurrentMoney(5);
	Deck* deck = CreateDeck();
	StartupDeck(deck);
	PrintDeck(deck);

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

void AddHead(Deck* deck, int card, int suit) {
	Poker* add = new Poker;
	add->card = card;
	add->suit = suits[suit];
	add->next = deck->head;
	deck->head = add;
}

void AddTail(Deck* deck, int card, int suit) {
	if (deck->head == NULL) { //when the deck is empty
		AddHead(deck, card, suit);
		return;
	}
	Poker* last = deck->head;
	while (last->next != NULL) {
		last = last->next;
	} //find the last card in the deck
	Poker* add = new Poker; //add the new card at the end
	add->card = card;
	add->suit = suits[suit];
	add->next = NULL;
	last->next = add;
}

void StartupDeck(Deck* deck) {
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 13; j++) {
			AddTail(deck, j, i);
		}
	}
}

void PrintDeck(Deck* deck) {
	Poker* item = deck->head;
	while (item != NULL) {
		cout << item->card << " of " << item->suit;
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