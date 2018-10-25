#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<limits>
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

void CurrentMoney();
Deck* CreateDeck();
void AddHead(Deck*, int, int, bool);
void AddTail(Deck*, int, int, bool);
void AddPoker(Deck*, int, int, int, bool);
void ReplacePoker(Deck*, int, int, int, bool);
Poker* FindPoker(Deck*, int);
int FindCard(Deck*, int);
int FindSuit(Deck*, int);
int SwitchSuit(Poker*);
int CountPokers(Deck*);
void PrintCount(Deck*);
void DeleteHead(Deck*);
void DeleteTail(Deck*);
void DeletePoker(Deck*, int);
void PrintDeck(Deck*);
void PrintHand(Deck*);
void RemoveDeck(Deck*);
void StartupDeck(Deck*);
void SortPokers(Deck*);
void RecreateDeck(Deck*, Deck*);
void DrawPokers(Deck*, Deck*);
void Console(Deck*, Deck*);
void KeepPoker(char, Deck*, Deck*);
void DrawNewPoker(Deck*, Deck*);
void PokerHand(Deck*);
bool EndGame(Deck*);

string suits[4] = { "Diamonds", "Clubs", "Spades", "Hearts" };
int money = 5;
bool exitGame = false;
bool exitConsole = false;

int main() {
	Deck* deck = CreateDeck();
	Deck* hand = CreateDeck();
	system("color f1");
	StartupDeck(deck);
	do {
		system("cls");
		CurrentMoney();
		RecreateDeck(deck, hand);
		DrawPokers(deck, hand);
		PrintCount(deck);
		do {
			exitConsole = false;
			Console(deck, hand);
		} while (exitConsole == false);
		if (EndGame(hand) == true)
			cout << "Game is Overrrrrrrrrrrrrr~" << endl;
		system("pause");
	} while (EndGame(hand) == false && exitGame == false);
	return 0;
}

void CurrentMoney() {
	cout << "Welcome to Yitong Hu's Video Poker Game!!!" << endl;
	cout << "You start with $" << money << "." << endl;
	money--;
	cout << "You payed $1 and currently have $" << money << "." << endl << endl;
}

Deck* CreateDeck() {
	Deck* deck = new Deck;
	deck->head = NULL;
	deck->tail = NULL;
	return deck;
}

void AddHead(Deck* deck, int card, int suit, bool keep) {
	Poker* add = new Poker;
	add->card = card;
	add->suit = suits[suit];
	add->keep = keep;
	add->next = deck->head;
	add->prev = NULL;
	if (deck->head == NULL)
		deck->tail = add;
	else if(deck->head != NULL)
		deck->head->prev = add;
	deck->head = add;
}

void AddTail(Deck* deck, int card, int suit, bool keep) {
	if (deck->head == NULL) {
		AddHead(deck, card, suit, keep);
		return;
	}
	Poker* add = new Poker;
	add->card = card;
	add->suit = suits[suit];
	add->keep = keep;
	add->next = NULL;
	add->prev = deck->tail;
	deck->tail->next = add;
	deck->tail = add;
}

void AddPoker(Deck* deck, int index, int card, int suit, bool keep) {
	if (deck->head == NULL || index == 0) {
		AddHead(deck, card, suit, keep);
		return;
	}
	Poker* temp = FindPoker(deck, index);
	Poker* item = new Poker;
	item->card = card;
	item->suit = suits[suit];
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
	return SwitchSuit(item);
}

int SwitchSuit(Poker* item) {
	int suit = 0;
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

void PrintCount(Deck* deck) {
	cout << "There are " << CountPokers(deck) << " cards in the deck" << endl << endl;
}

void DeleteHead(Deck* deck) {
	if (deck->head == NULL) {
		cout << "Deck already empty!" << endl;
		return;
	}
	Poker* item = deck->head;
	deck->head = item->next;
	if(item->next != NULL)
		item->next->prev = NULL;
	delete item;
}

void DeleteTail(Deck* deck) {
	if (deck->head == NULL) {
		cout << "Deck already empty!" << endl;
		return;
	}
	else if (CountPokers(deck) == 1) {
		Poker* item = deck->tail;
		deck->tail = NULL;
		deck->head = NULL;
		delete item;
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
	cout << endl;
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
			AddTail(deck, j, i, false);
		}
	}
}

void SortPokers(Deck* hand) {
	Poker* item = hand->head;
	Poker* compare = item->next;
	Poker* temp = new Poker;
	int n = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 1 + n; j < 5; j++) {
			if (item->card > compare->card || (item->card == compare->card && SwitchSuit(item) > SwitchSuit(compare))) {
				temp->card = compare->card;
				temp->suit = compare->suit;
				temp->keep = compare->keep;
				ReplacePoker(hand, j, item->card, SwitchSuit(item), item->keep);
				ReplacePoker(hand, i, temp->card, SwitchSuit(temp), temp->keep);
				item = FindPoker(hand, i);
				compare = FindPoker(hand, j);
			}
			compare = compare->next;
		}
		item = item->next;
		compare = item->next;
		n++;
	}
}

void RecreateDeck(Deck* deck, Deck* hand) {
	if (CountPokers(deck) <= 5) {
		while(deck->head != NULL) {
			DeleteTail(deck);
		}
		StartupDeck(deck);
		if (CountPokers(hand) != 0) {
			int n = 0;
			Poker* minus = hand->head;
			for (int i = 0; i < CountPokers(hand); i++) {
				Poker* item = deck->head;
				for (int j = 0; j < 52 - n; j++) {
					if (minus->card == item->card && minus->suit == item->suit) {
						DeletePoker(deck, j);
						n++;
						item = FindPoker(deck, j - 1);
					}
					item = item->next;
				}
				minus = minus->next;
			}
		}
	}
}

void DrawPokers(Deck* deck, Deck* hand) {
	srand(time(0));
	for (int i = 0; i < 5; i++) {
		RecreateDeck(deck, hand);
		int item = 1 + (rand() % (CountPokers(deck) - i));
		int card = FindCard(deck, item - 1);
		int suit = FindSuit(deck, item - 1);
		AddTail(hand, card, suit, false);
		DeletePoker(deck, item - 1);
	}
	SortPokers(hand);
	PrintHand(hand);
}

void Console(Deck* deck, Deck* hand) {
	cout << "- Type the letters of the cards that you want to keep." << endl;
	cout << "- Type 'deck' to view the cards in deck." << endl;
	cout << "- Type 'none' to discard all cards in hand." << endl;
	cout << "- Type 'all' to keep all cards in hand." << endl;
	cout << "- Type 'exit' to exit the game." << endl;
	cout << "- Type 'swap' to switch the cards in hand.[CHEATING]" << endl;
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
		else if (command == "none" || command == "None" || command == "NONE") {
			DrawNewPoker(hand, deck);
			keepask = false;
			exitConsole = true;
		}
		else if (command == "all" || command == "All" || command == "ALL") {
			for (int i = 0; i < 5; i++) {
				ReplacePoker(hand, i, FindCard(hand, i), FindSuit(hand, i), true);
			}
			DrawNewPoker(hand, deck);
			keepask = false;
			exitConsole = true;
		}
		else if (command == "exit" || command == "Exit" || command == "EXIT") {
			exitGame = true;
			keepask = false;
			exitConsole = true;
		}
		else if (command == "swap" || command == "Swap" || command == "SWAP") {
			char swapIndex, swapSuit;
			int swapCard, suitIndex, index;
			bool askAgain1 = false, askAgain2 = false, askAgain3 = false;
			//which card
			cout << "Which card in hand do you want to switch?" << endl;
			do {
				cin >> swapIndex;
				askAgain1 = false;
				if (swapIndex == 'a' || swapIndex == 'A' || swapIndex == 'b' || swapIndex == 'B' || swapIndex == 'c' || swapIndex == 'C' || swapIndex == 'd' || swapIndex == 'D' || swapIndex == 'e' || swapIndex == 'E') {
					for (int i = 0; i < 5; i++) {
						if (swapIndex == char('a' + i) || swapIndex == char('A' + i)) {
							index = i;
							askAgain1 = false;
							break;
						}
					}
				}
				else {
					askAgain1 = true;
					cout << "Please type valid index." << endl;
					cin.clear();
					cin.ignore(10000, '\n');
				}
			} while (askAgain1 == true);
			cin.clear();
			cin.ignore(10000, '\n');
			//which number
			cout << "What number do you want?" << endl;
			do {
				cin >> swapCard;
				askAgain2 = false;
				while (!cin.good()) {
					cout << "Please type valid number." << endl;
					cin.clear();
					cin.ignore(10000, '\n');
					cin >> swapCard;
				}
				cin.ignore(10000, '\n');
				if (swapCard > 13 || swapCard <= 0) {
					askAgain2 = true;
					cout << "Please type valid number." << endl;
				}
			} while (askAgain2 == true);
			//which suit
			cout << "What suit do you want?" << endl;
			cout << "(d = Diamonds, c = Clubs, s = Spades, h = Hearts)" << endl;
			do {
				cin >> swapSuit;
				askAgain3 = false;
				if (swapSuit == 'd' || swapSuit == 'D') {
					suitIndex = 0;
				}
				else if (swapSuit == 'c' || swapSuit == 'C') {
					suitIndex = 1;
				}
				else if (swapSuit == 's' || swapSuit == 'S') {
					suitIndex = 2;
				}
				else if (swapSuit == 'h' || swapSuit == 'H') {
					suitIndex = 3;
				}
				else {
					askAgain3 = true;
					cout << "Please type valid suit." << endl;
					cin.clear();
					cin.ignore(10000, '\n');
				}
			} while (askAgain3 == true);
			cin.clear();
			cin.ignore(10000, '\n');
			//now you can swap the card
			Poker* temp = FindPoker(hand, index);
			ReplacePoker(hand, index, swapCard, suitIndex, false);
			Poker* find = deck->head;
			int n;
			for (int i = 0; i < CountPokers(deck); i++) {
				if (find->card == swapCard || find->suit == suits[suitIndex]) {
					n = i;
					break;
				}
				find = find->next;
			}
			ReplacePoker(deck, n, temp->card, SwitchSuit(temp), false);
			system("cls");
			CurrentMoney();
			PrintHand(hand);
			PrintCount(deck);
			keepask = false;
		}
		else { //select the cards you want to keep
			for (char & letter : command) {
				if (letter == 'a' || letter == 'A' || letter == 'b' || letter == 'B' || letter == 'c' || letter == 'C' || letter == 'd' || letter == 'D' || letter == 'e' || letter == 'E') {
					KeepPoker(letter, hand, deck);
					exitConsole = true;
					keepask = false;
				}
				else {
					cout << "Please type valid command." << endl;
					keepask = true;
					break;
				}
			}
			RecreateDeck(deck, hand);
			DrawNewPoker(hand, deck);
		}
	} while (keepask == true);
}

void KeepPoker(char letter, Deck* hand, Deck* deck) {
	int index;
	for (int i = 0; i < 5; i++) {
		if (letter == char('a' + i) || letter == char('A' + i)) {
			index = i;
			break;
		}
	}
	ReplacePoker(hand, index, FindCard(hand, index), FindSuit(hand, index), true);
}

void DrawNewPoker(Deck* hand, Deck* deck) {
	Poker* item = hand->head;
	int count = 0;
	for (int i = 0; i < 5; i++) {
		if (item->keep == false) {
			srand(time(0));
			RecreateDeck(deck, hand);
			int draw = 1 + (rand() % (CountPokers(deck) - count));
			int card = FindCard(deck, draw - 1);
			int suit = FindSuit(deck, draw - 1);
			ReplacePoker(hand, i, card, suit, false);
			item = FindPoker(hand, i);
			DeletePoker(deck, draw - 1);
			count++;
		}
		item = item->next;
	}
	SortPokers(hand);
	system("cls");
	cout << "Welcome to Yitong Hu's Video Poker Game!!!" << endl;
	cout << "You start with $" << money + 1 << "." << endl;
	cout << "You payed $1 and currently have $" << money << "." << endl << endl;
	PrintHand(hand);
	PrintCount(deck);
	PokerHand(hand);
}

void PokerHand(Deck* hand) {
	Poker* item = hand->head;
	Poker* compare = item->next;
	int n = 0, count = 1, pair = 0, flush = 1;
	bool isThree = false, isFour = false, isOnePair = false;
	for (int i = 0; i < 4; i++) {
		if (flush == 5)
			break;
		else
			flush = 1;
		for (int j = 1 + n; j < 5; j++) {
			if (item->card == compare->card) {
				count++;
				if (item->card > 10 || item->card == 1)
					isOnePair = true;
			}
			if (item->suit == compare->suit)
				flush++;
			compare = compare->next;
		}
		if (count == 2)
			pair++;
		else if (count == 3) {
			isThree = true;
			break;
		}
		else if (count == 4) {
			isFour = true;
			break;
		}
		item = item->next;
		compare = item->next;
		n++;
		count = 1;
		if (pair == 2)
			break;
	}
	if (isFour) {
		cout << "Congratulations! You got Four of a Kind and earned $25!" << endl << endl;
		money += 25;
	}
	else if (isThree) {
		cout << "Congratulations! You got Three of a Kind and earned $3!" << endl << endl;
		money += 3;
	}
	else if (pair == 2) {
		cout << "Congratulations! You got Two Pair and earned $2!" << endl << endl;
		money += 2;
	}
	else if (isOnePair) {
		cout << "Congratulations! You got One Pair and earned $1!" << endl << endl;
		money += 1;
	}
	else if (flush == 5) {
		cout << "Congratulations! You got Flush and earned $6!" << endl << endl;
		money += 6;
	}
	else
		cout << "Oh you lost! No money for you!" << endl << endl;
}

bool EndGame(Deck* hand) {
	if (money == 0)
		return true;
	else {
		while (CountPokers(hand) != 0) {
			DeleteTail(hand);
		}
		return false;
	}
}