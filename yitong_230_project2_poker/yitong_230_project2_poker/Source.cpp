#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;

struct Poker {
	int card;
	string suit;
	Poker* next;
	Poker* prev;
	bool keep = false;
};

struct Deck {
	Poker* head;
	Poker* tail;
};

void CurrentMoney(int);
Deck* CreateDeck();
void AddHead(Deck*, int, int);
void AddTail(Deck*, int, int);
Poker* FindPoker(Deck*, int);
int FindCard(Deck*, int);
int FindSuit(Deck*, int);
int CountPokers(Deck*);
void DeleteHead(Deck*);
void DeleteTail(Deck*);
void DeletePoker(Deck*, int);
void PrintDeck(Deck*);
void PrintHand(Deck*);
void RemoveDeck(Deck*);
void StartupDeck(Deck*);
void DrawPokers(Deck*, Deck*);
void Console(Deck*, Deck*);
void DrawNewPokers(char, Deck*);
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
		DrawPokers(deck, hand);
		Console(deck, hand);
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
	deck->tail = NULL;
	return deck;
}

void AddHead(Deck* deck, int card, int suit) {
	Poker* add = new Poker;
	add->card = card;
	add->suit = suits[suit];
	add->next = deck->head;
	add->prev = NULL;
	deck->head = add;
}

void AddTail(Deck* deck, int card, int suit) {
	if (deck->head == NULL) {
		AddHead(deck, card, suit);
		return;
	}
	Poker* last = deck->head;
	while (last->next != NULL) {
		last = last->next;
	}
	Poker* add = new Poker;
	add->card = card;
	add->suit = suits[suit];
	add->next = NULL;
	add->prev = last;
	last->next = add;
	deck->tail = add;
}

void AddPoker(Deck* deck, int index, int card, int suit, bool keep) {
	if (deck->head == NULL || index == 0) {
		AddHead(deck, card, suit);
		return;
	}
	else if (index == CountPokers(deck) - 1) {
		AddTail(deck, card, suit);
		return;
	}
	Poker* temp = FindPoker(deck, index);
	Poker* item = new Poker;
	item->card = card;
	item->suit = suit;
	item->keep = keep;
	item->next = temp;
	item->prev = temp->prev;
	temp->prev->next = item;
	temp->prev = item;
}

void ReplacePoker(Deck* deck, int index, int card, int suit, bool keep) {
	AddPoker(deck, index, card, suit, keep);
	DeletePoker(deck, index + 1);
}

Poker* FindPoker(Deck* deck, int index) {
	Poker* item = deck->head;
	while (index > 0) {
		item = item->next;
		index--;
	}
	return item;
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

int CountPokers(Deck* deck) {
	int count = 0;
	Poker* item = deck->head;
	while (item != NULL) {
		count++;
		item = item->next;
	}
	return count;
}

void DeleteHead(Deck* deck) {
	if (deck->head == NULL) {
		cout << "Deck already empty!" << endl;
		return;
	}
	Poker* item = deck->head;
	deck->head = item->next;
	item->next->prev = NULL;
	delete item;
}

void DeleteTail(Deck* deck) {
	if (deck->head == NULL) {
		cout << "Deck already empty!" << endl;
		return;
	}
	Poker* item = deck->tail;
	deck->tail = item->prev;
	item->prev->next = NULL;
	delete item;
}

void DeletePoker(Deck* deck, int index) {
	if (deck->head == NULL) {
		cout << "Deck already empty!" << endl;
		return;
	}
	else if (index == 0) {
		DeleteHead(deck);
		return;
	}
	else if (index == CountPokers(deck) - 1) {
		DeleteTail(deck);
		return;
	}
	Poker* item = FindPoker(deck, index);
	item->prev->next = item->next;
	item->next->prev = item->prev;
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
	char letter = 'A';
	int i = 0;
	while (item != NULL) {
		cout << char(letter + i) << ". ";
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
		if (item->keep == true) {
			cout << " (Kept)";
		}
		if (item->next != NULL)
			cout << ";" << endl;
		else
			cout << "." << endl;
		item = item->next;
		i++;
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

void DrawPokers(Deck* deck, Deck* hand) {
	srand(time(0));
	for (int i = 0; i < 5; i++) {
		int item = 1 + (rand() % (52 - i));
		int card = FindCard(deck, item - 1);
		int suit = FindSuit(deck, item - 1);
		AddTail(hand, card, suit);
		DeletePoker(deck, item - 1);
	}
	PrintHand(hand);
}

void Console(Deck* deck, Deck* hand) {
	cout << "Type 'deck' to view the cards in deck." << endl;
	cout << endl;
	string command;
	bool keepask = true;
	do {
		cout << "Input command: ";
		cin >> command;
		if (command == "deck" || command == "Deck" || command == "DECK") {
			PrintDeck(deck);
			keepask = false;
		}
		else {
			for (char & letter : command) {
				if (letter == 'a' || letter == 'A' || letter == 'b' || letter == 'B' || letter == 'c' || letter == 'C' || letter == 'd' || letter == 'D' || letter == 'e' || letter == 'E') {
					DrawNewPokers(letter, hand);
					keepask = false;
				}
				else {
					cout << "Please type valid command." << endl;
					keepask = true;
					break;
				}
			}
		}
	} while (keepask == true);
}

void DrawNewPokers(char letter, Deck* hand) {
	int index;
	for (int i = 0; i < 5; i++) {
		if (letter == char('a' + i) || letter == char('A' + i)) {
			index = i;
		}
	}
	Poker* item = new Poker;
	item->card = FindCard(hand, index);
	item->suit = FindSuit(hand, index);
	ReplacePoker(hand, index, item->card, item->suit, true);
}

bool EndGame() {
	return true;
}