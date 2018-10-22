#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
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
int FindCard(Deck*, int);
int FindSuit(Deck*, int);
void DeleteHead(Deck*);
void DeleteCard(Deck*, int);
void PrintDeck(Deck*);
void PrintHand(Deck*);
void RemoveDeck(Deck*);
void StartupDeck(Deck*);
void DrawCard(Deck*, Deck*);
int CountCards(Deck*);
void Console(Deck*);
bool EndGame();

string suits[4] = { "Diamonds", "Clubs", "Spades", "Hearts" };
int money = 5;

int main() {
	system("color f1");
	cout << "Welcome to Yitong Hu's Video Poker Game!!!" << endl;
	cout << "You start with $5." << endl;
	Deck* deck = CreateDeck();
	Deck* hand = CreateDeck();
	StartupDeck(deck);
	CurrentMoney(money);
	do {
		DrawCard(deck, hand);
		Console(deck);
		EndGame();
	} while (EndGame() == false);
	
	system("pause");
	return 0;
}

void CurrentMoney(int money) {
	money--;
	cout << "You payed $1 and currently have $" << money << "." << endl << endl;
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

int FindCard(Deck* deck, int index) {
	Poker* item = deck->head;
	while (index > 0) {
		item = item->next;
		index--;
	}
	return item->card;
}

int FindSuit(Deck* deck, int index) {
	Poker* item = deck->head;
	while (index > 0) {
		item = item->next;
		index--;
	}
	int suit;
	if (item->suit == "Diamonds")
		suit = 0;
	else if (item->suit == "Clubs")
		suit = 1;
	else if (item->suit == "Spades")
		suit = 2;
	else if (item->suit == "Hearts")
		suit = 3;
	return suit;
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
	while (index - 1 > 0) {
		prev = prev->next;
		index--;
	}
	Poker* item = prev->next;
	prev->next = item->next;
	delete item;
}

void PrintDeck(Deck* deck) {
	Poker* item = deck->head;
	while (item != NULL) {
		if (item->card == 1) {
			cout << "Ace" << " of " << item->suit;
		}
		else if (item->card == 11) {
			cout << "Jack" << " of " << item->suit;
		}
		else if (item->card == 12) {
			cout << "Queen" << " of " << item->suit;
		}
		else if (item->card == 13) {
			cout << "King" << " of " << item->suit;
		}
		else
			cout << item->card << " of " << item->suit;
		if (item->next != NULL)
			cout << ", ";
		item = item->next;
	}
	cout << endl << endl;
}

void PrintHand(Deck* hand) {
	Poker* item = hand->head;
	cout << "Your hand: " << endl;
	while (item != NULL) {
		if (item->card == 1) {
			cout << "Ace" << " of " << item->suit;
		}
		else if (item->card == 11) {
			cout << "Jack" << " of " << item->suit;
		}
		else if (item->card == 12) {
			cout << "Queen" << " of " << item->suit;
		}
		else if (item->card == 13) {
			cout << "King" << " of " << item->suit;
		}
		else
			cout << item->card << " of " << item->suit;
		if (item->next != NULL)
			cout << ";" << endl;
		else
			cout << "." << endl;
		item = item->next;
	}
	cout << endl << endl;
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

void StartupDeck(Deck* deck) {
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 13; j++) {
			AddTail(deck, j, i);
		}
	}
}

void DrawCard(Deck* deck, Deck* hand) {
	srand(time(0));
	for (int i = 0; i < 5; i++) {
		int item = 1 + (rand() % (52 - i));
		int card = FindCard(deck, item - 1);
		int suit = FindSuit(deck, item - 1);
		AddTail(hand, card, suit);
		DeleteCard(deck, item - 1);
	}
	PrintHand(hand);
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

void Console(Deck* deck) {
	cout << "Type 'deck' to view the cards in deck." << endl;
	string command;
	bool keepask = true;
	do {
		cout << "Input command: ";
		cin >> command;
		if (command == "deck" || command == "Deck" || command == "DECK") {
			PrintDeck(deck);
			keepask = false;
		}
		else
			cout << "Please type valid command." << endl;	
	} while (keepask == true);
}

bool EndGame() {
	return true;
}