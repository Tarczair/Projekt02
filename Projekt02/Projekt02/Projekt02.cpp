#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

void menu() {
	bst tree;
	int choice, value;
	string method;

	do {

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
