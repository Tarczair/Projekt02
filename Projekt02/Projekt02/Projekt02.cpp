#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

void menu() {
	bst tree;
	int choice, value;
	string method;

	do {
		cout << "\n=== MENU DRZEWA BST ===\n";
		cout << "1. Dodaj nowy element\n";
		cout << "2.Usun element\n";
		cout << "3. Usun cale drzewo\n";
		cout << "4. Szukaj drogi do elementu\n";
		cout << "5. Wyswietl drzewo (preorder/inorder/postorder)\n";
		cout << "6. Zapisz drzewo do pliku\n";
		cout << "0. Wyjdz\n";
		cout << "Twoj wybor: ";

		cout << "0. Wyjdz\n";
		cout << "Twoj wybor: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Podaj calkowita liczbe: ";
			cin >> value;
			tree.add(value);
			break;
		case 2:
			cout << "Podaj calkowita liczbe do usuniecia: ";
			cin >> value;
			tree.remove(value);
			break;
		case 3:
			tree.clear();
			cout << "Drzewo zostalo usuniete.\n";
			break;
		case 4:
			cout << "Podaj calkowita liczbe do znalezienia: ";
			cin >> value;
			tree.findPath(value);
			break;
		case 5:
			cout << "Podaj metode (preorder/inorder/postorder): ";
			cin >> method;
			tree.printTree(method);
			break;
		case 6:
			tree.saveToFile("drzewo.txt");
			break;
		case 0:
			cout << "Koniec programu.\n";
			break;
		default:
			cout << "Niepoprawny wybor!\n";
		}
	} while (choice != 0);
}

int main() {
	menu();
	return 0;
}
