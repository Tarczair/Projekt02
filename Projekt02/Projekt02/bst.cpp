#include "bst.h"

bst::bst() {}


//Sortowanie Inorder
void bst::inorder(int level, int index) {
	if (level >= tree.size() || index >= tree[level].size() || tree[level][index] == -1) return;
	inorder(level + 1, index * 2);
	cout << tree[level][index] << " ";
	inorder(level + 1, index * 2 + 1);
}

//Sortowanie postorder
void bst::postorder(int level, int index) {
	if (level >= tree.size() || index >= tree[level].size() || tree[level][index] == -1) return;
	postorder(level + 1, index * 2);
	postorder(level + 1, index * 2 + 1);
	cout << tree[level][index] << " ";
}

//Sortowanie preorder
void bst::preorder(int level, int index) {
	if (level >= tree.size() || index >= tree[level].size() || tree[level][index] == -1) return;
	cout << tree[level][index] << " ";
	preorder(level + 1, index * 2);
	preorder(level + 1, index * 2 + 1);
}

void bst::ensureLevel(int level) {
	if (level >= tree.size()) tree.resize(level + 1);
}

//Dodawanie do drzewa
void bst::add(int value) {
	if (tree.empty()) {
		tree.push_back({ value });
		return;
	}

	int level = 0;
	int index = 0;

	while (true) {
		ensureLevel(level + 1);
		if (index >= tree[level].size())
			tree[level].resize(index + 1, -1);

		if (tree[level][index] == -1) {
			tree[level][index] = value;
			break;
		}

		if (value < tree[level][index]) {
			level++;
			index = index * 2;
		}
		else {
			level++;
			index = index * 2 + 1;
		}

		ensureLevel(level);
		if (index >= tree[level].size())
			tree[level].resize(index + 1, -1);
	}
}

//Czyszczenie drzewa
void bst::clear() {
	tree.clear();
}

//Wyœwietlanie drzewa za pomoc¹ metod preorder, inorder, postorder
void bst::printTree(string method) {
	cout << "Drzewo (" << method << "): ";
	if (method == "preorder") preorder(0, 0);
	else if (method == "inorder") inorder(0, 0);
	else if (method == "postorder") postorder(0, 0);
	cout << endl;
	printGraphical();
}


//Wyœwietlanie drzewa graficzne
void bst::printGraphical() {
	if (tree.empty()) {
		cout << "Drzewo jest puste.\n";
		return;
	}

	int height = tree.size();
	int maxWidth = pow(2, height) * 2 - 1;

	for (int level = 0; level < height; ++level) {
		int nodesInLevel = tree[level].size();
		int spacing = maxWidth / (nodesInLevel + 1);

		for (int i = 0; i < nodesInLevel; ++i) {
			if (tree[level][i] != -1)
				cout << setw(spacing) << tree[level][i];
			else
				cout << setw(spacing) << " ";
		}
		cout << endl;

		if (level < height - 1) {
			bool hasChildren = false;
			for (int i = 0; i < nodesInLevel; ++i) {
				int leftIdx = i * 2;
				int rightIdx = i * 2 + 1;
				if (level + 1 < tree.size()) {
					if ((leftIdx < tree[level + 1].size() && tree[level + 1][leftIdx] != -1) ||
						(rightIdx < tree[level + 1].size() && tree[level + 1][rightIdx] != -1)) {
						hasChildren = true;
						break;
					}
				}
			}

			if (hasChildren) {
				cout << " ";
				for (int i = 0; i < nodesInLevel; ++i) {
					int leftIdx = i * 2;
					int rightIdx = i * 2 + 1;
					bool hasLeft = (level + 1 < tree.size() && leftIdx < tree[level + 1].size() && tree[level + 1][leftIdx] != -1);
					bool hasRight = (level + 1 < tree.size() && rightIdx < tree[level + 1].size() && tree[level + 1][rightIdx] != -1);

					string branch;
					if (hasLeft && hasRight)
						branch = "/ \\ ";
					else if (hasLeft)
						branch = "/";
					else if (hasRight)
						branch = " \\ ";
					else
						branch = " ";

					cout << setw(spacing) << branch;
				}
				cout << endl;
			}
		}
	}
}








//Znajdowanie elementu w drzewie
void bst::findPath(int value) {
	if (tree.empty()) {
		cout << "Drzewo jest puste." << endl;
		return;
	}

	cout << "Sciezka do " << value << ": ";

	int level = 0;
	int index = 0;

	while (true) {
		// Sprawdzenie, czy nie wyszliœmy poza drzewo
		if (level >= tree.size() || index >= tree[level].size() || tree[level][index] == -1) {
			cout << "\nElementu nie znaleziono." << endl;
			return;
		}

		int currentValue = tree[level][index];
		cout << currentValue;

		if (currentValue == value) {
			cout << "\nElement znaleziony." << endl;
			return;
		}

		cout << " -> "; // Strza³ka do nastêpnego elementu

		if (value < currentValue) {
			// IdŸ w lewo
			level++;
			index = index * 2;
		}
		else {
			// IdŸ w prawo
			level++;
			index = index * 2 + 1;
		}
	}
}

//Zapisywanie do pliku
void bst::saveToFile(const string& filename) {
	// 1. Otwórz strumieñ pliku do zapisu (output file stream)
	ofstream plik(filename);

	// 2. SprawdŸ, czy plik na pewno uda³o siê otworzyæ
	if (!plik.is_open()) {
		cout << "B£¥D: Nie mozna otworzyc pliku do zapisu: " << filename << endl;
		return; // Zakoñcz funkcjê, jeœli siê nie uda³o
	}

	// 3. SprawdŸ, czy drzewo nie jest puste
	if (tree.empty()) {
		plik << "Drzewo jest puste." << endl;
		plik.close(); // Zamknij plik
		cout << "Zapisano (puste drzewo) do pliku: " << filename << endl;
		return;
	}

	// 4. PrzejdŸ pêtl¹ po wektorze wektorów i zapisz zawartoœæ
	// Zewnêtrzna pêtla idzie po poziomach (level)
	for (int i = 0; i < tree.size(); ++i) {
		// Wewnêtrzna pêtla idzie po wêz³ach na danym poziomie
		for (int j = 0; j < tree[i].size(); ++j) {
			// Zapisz wartoœæ do pliku, a po niej spacjê
			plik << tree[i][j] << " ";
		}
		// Zrób now¹ liniê w pliku po zakoñczeniu ka¿dego poziomu
		plik << endl;
	}

	// 5. Zamknij plik
	plik.close();

	cout << "Drzewo zostalo poprawnie zapisane do pliku: " << filename << endl;
}



// ####### POCZ¥TEK BRAKUJ¥CYCH FUNKCJI #######

// Bezpiecznie pobiera wartoœæ z drzewa, obs³uguje wyjœcie poza zakres
int bst::getNodeValue(int level, int index) const {
	if (level >= tree.size() || index >= tree[level].size()) {
		return -1; // Poza zakresem traktujemy jak pusty wêze³
	}
	return tree[level][index];
}

// Bezpiecznie ustawia wartoœæ, w razie potrzeby rozszerzaj¹c wektor
void bst::setNodeValue(int level, int index, int value) {
	ensureLevel(level); // U¿ywamy Twojej istniej¹cej funkcji
	if (index >= tree[level].size()) {
		tree[level].resize(index + 1, -1);
	}
	tree[level][index] = value;
}

// Znajduje wêze³ i zwraca jego pozycjê przez referencjê
void bst::findNode(int value, int& level, int& index, bool& found) const {
	if (tree.empty()) {
		found = false;
		return;
	}

	level = 0;
	index = 0;
	found = false;

	while (true) {
		int currentVal = getNodeValue(level, index);
		if (currentVal == -1) {
			return; // Nie znaleziono
		}
		if (currentVal == value) {
			found = true;
			return; // Znaleziono
		}

		if (value < currentVal) {
			level++;
			index = index * 2;
		}
		else {
			level++;
			index = index * 2 + 1;
		}
	}
}

// Znajduje nastêpnika (najmniejszy wêze³ w prawym poddrzewie)
void bst::findSuccessor(int startLevel, int startIndex, int& sLevel, int& sIndex) const {
	// Idziemy raz w prawo
	sLevel = startLevel + 1;
	sIndex = startIndex * 2 + 1;

	// A potem maks w lewo, dopóki istnieje lewe dziecko
	while (getNodeValue(sLevel + 1, sIndex * 2) != -1) {
		sLevel++;
		sIndex = sIndex * 2;
	}
}



// Funkcja pomocnicza do zbierania wszystkich potomków danego wêz³a
void bst::collectSubtree(int level, int index, vector<int>& values) {
	// 1. Pobierz wartoœæ bie¿¹cego wêz³a
	int currentValue = getNodeValue(level, index);

	// 2. Warunek stopu
	if (currentValue == -1) {
		return;
	}

	// 3. Dodaj bie¿¹c¹ wartoœæ do wektora "zebranych"
	values.push_back(currentValue);

	// 4. Natychmiast usuñ wêze³, który w³aœnie zebraliœmy.   
	setNodeValue(level, index, -1);

	// 5. Rekurencyjnie zejdŸ do dzieci
	collectSubtree(level + 1, index * 2, values);     // Szukaj w lewym poddrzewie
	collectSubtree(level + 1, index * 2 + 1, values); // Szukaj w prawym poddrzewie
}

// Logika usuwania pojedynczego wêz³a
void bst::removeNodeAt(int level, int index) {
	// 1. Sprawdzamy dzieci wêz³a do usuniêcia
	int leftChildVal = getNodeValue(level + 1, index * 2);
	int rightChildVal = getNodeValue(level + 1, index * 2 + 1);

	// Przypadek 1: Wêze³ jest liœciem (brak dzieci)
	// Bez zmian: po prostu ustawiamy na -1
	if (leftChildVal == -1 && rightChildVal == -1) {
		setNodeValue(level, index, -1);
		cout << "Informacja: Usunieto lisc." << endl;
	}

	// Przypadek 2: Wêze³ ma DWOJE dzieci
	// Bez zmian: u¿ywamy "remove by copying" z nastêpc¹
	else if (leftChildVal != -1 && rightChildVal != -1) {
		cout << "Informacja: Usuwanie wezla z 2 dzieci (przez kopiowanie)." << endl;

		int sLevel = 0, sIndex = 0;
		findSuccessor(level, index, sLevel, sIndex);
		int successorValue = getNodeValue(sLevel, sIndex);

		setNodeValue(level, index, successorValue);
		removeNodeAt(sLevel, sIndex); // Rekurencyjnie usuñ nastêpnika
	}

	// Przypadek 3: Wêze³ ma TYLKO JEDNO dziecko (NOWA LOGIKA)
	// Realizujemy pomys³ Twojego kolegi
	else {
		cout << "Informacja: Usuwanie wezla z 1 dzieckiem (przez ponowne dodanie)." << endl;

		// a) ZnajdŸ, które dziecko istnieje
		int childLevel = level + 1;
		int childIndex = (leftChildVal != -1) ? (index * 2) : (index * 2 + 1);

		// b) Stwórz wektor na zebrane wartoœci
		vector<int> descendants;

		// c) Wype³nij wektor, zbieraj¹c wszystkich potomków tego jednego dziecka
		collectSubtree(childLevel, childIndex, descendants);

		// d) "Usuñ" bie¿¹cy wêze³ (ustaw na -1). 
		//    To skutecznie "usuwa" te¿ wszystkie stare pozycje potomków.
		setNodeValue(level, index, -1);

		// e) Dodaj wszystkich zebranych potomków na nowo do drzewa
		cout << "Informacja: Ponowne dodawanie " << descendants.size() << " potomkow..." << endl;
		for (int value : descendants) {
			add(value); // U¿ywamy istniej¹cej funkcji add()
		}
	}
}

// Publiczna funkcja remove, któr¹ wywo³uje menu
void bst::remove(int value) {
	int level = 0;
	int index = 0;
	bool found = false;

	// 1. ZnajdŸ pozycjê wêz³a
	findNode(value, level, index, found);

	if (!found) {
		cout << "Elementu " << value << " nie ma w drzewie." << endl;
		return;
	}

	// 2. Wywo³aj w³aœciw¹ logikê usuwania na tej pozycji
	removeNodeAt(level, index);
	cout << "Zakonczono usuwanie " << value << "." << endl;
}