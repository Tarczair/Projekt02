#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

class BST {
private:
	struct Element {
		int value;
		unique_ptr<Element> lewy;
		unique_ptr<Element> prawy;
		Element(int v) : value(v) {}
	};

	unique_ptr<Element> korzen;

public:
	void insert(int value) {
		if (!korzen) {

		}
	}
	void remove(int value) {}
	void findPath(int value) {}
	void displayPreorder() {}
	void displayInorder() {}
	void displayPostorder() {}
	void saveToFile(const string& filename) {}
	void clear() {}



};

void menu() {
	BST tree;
	int choice, value;

	do {
		cout << "\n=== MENU DRZEWA BST ===\n";
		cout << "1. Dodaj element\n";
		cout << "2. Usun element\n";
		cout << "3. Usun cale drzewo\n";
		cout << "4. Szukaj drogi do elementu\n";
		cout << "5. Wyswietl drzewo (preorder/inorder/postorder)\n";
		cout << "6. Zapisz drzewo do pliku\n";
		cout << "0. Wyjdz\n";
		cout << "Twoj wybor: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Podaj wartosc: ";
			cin >> value;
			tree.insert(value);
			break;
		case 2:
			cout << "Podaj wartosc do usuniecia: ";
			cin >> value;
			tree.remove(value);
			break;
		case 3:
			tree.clear();
			cout << "Drzewo zostalo usuniete.\n";
			break;
		case 4:
			cout << "Podaj wartosc do znalezienia: ";
			cin >> value;
			tree.findPath(value);
			break;
		case 5:
			int typ;
			cout << "Wybierz metode (1-preorder, 2-inorder, 3-postorder): ";
			cin >> typ;
			if (typ == 1) tree.displayPreorder();
			else if (typ == 2) tree.displayInorder();
			else if (typ == 3) tree.displayPostorder();
			else std::cout << "Nieznana metoda!\n";
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