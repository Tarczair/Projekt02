#include "bst.h"

bst::bst() {}

void bst::inorder(int level, int index) {
	if (level >= tree.size() || index >= tree[level].size() || tree[level][index] == -1) return;
	inorder(level + 1, index * 2);
	cout << tree[level][index] << " ";
	inorder(level + 1, index * 2 + 1);
}

void bst::postorder(int level, int index) {
	if (level >= tree.size() || index >= tree[level].size() || tree[level][index] == -1) return;
	postorder(level + 1, index * 2);
	postorder(level + 1, index * 2 + 1);
	cout << tree[level][index] << " ";
}

void bst::preorder(int level, int index) {
	if (level >= tree.size() || index >= tree[level].size() || tree[level][index] == -1) return;
	cout << tree[level][index] << " ";
	preorder(level + 1, index * 2);
	preorder(level + 1, index * 2 + 1);
}

void bst::ensureLevel(int level) {
	if (level >= tree.size()) tree.resize(level + 1);
}

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


void bst::clear() {
	tree.clear();
}

void bst::printTree(string method) {
	cout << "Drzewo (" << method << "): ";
	if (method == "preorder") preorder(0, 0);
	else if (method == "inorder") inorder(0, 0);
	else if (method == "postorder") postorder(0, 0);
	cout << endl;
	printGraphical();
}

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

void bst::findPath(int value) {
	if (tree.empty()) {
		cout << "Drzewo jest puste." << endl;
		return;
	}

	cout << "Sciezka do " << value << ": ";

	int level = 0;
	int index = 0;

	while (true) {
		
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

		cout << " -> "; 

		if (value < currentValue) {
			
			level++;
			index = index * 2;
		}
		else {
			
			level++;
			index = index * 2 + 1;
		}
	}
}

void bst::saveToFile(const string& filename) {
	
	ofstream plik(filename);

	if (!plik.is_open()) {
		cout << "B£¥D: Nie mozna otworzyc pliku do zapisu: " << filename << endl;
		return;
	}

	if (tree.empty()) {
		plik << "Drzewo jest puste." << endl;
		plik.close();
		cout << "Zapisano (puste drzewo) do pliku: " << filename << endl;
		return;
	}

	for (int i = 0; i < tree.size(); ++i) {
		
		for (int j = 0; j < tree[i].size(); ++j) {
			
			plik << tree[i][j] << " ";
		}
		
		plik << endl;
	}

	plik.close();

	cout << "Drzewo zostalo poprawnie zapisane do pliku: " << filename << endl;
}

int bst::getNodeValue(int level, int index) const {
	if (level >= tree.size() || index >= tree[level].size()) {
		return -1; 
	}
	return tree[level][index];
}

void bst::setNodeValue(int level, int index, int value) {
	ensureLevel(level); 
	if (index >= tree[level].size()) {
		tree[level].resize(index + 1, -1);
	}
	tree[level][index] = value;
}

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
			return; 
		}
		if (currentVal == value) {
			found = true;
			return; 
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

void bst::findSuccessor(int startLevel, int startIndex, int& sLevel, int& sIndex) const {
	
	sLevel = startLevel + 1;
	sIndex = startIndex * 2 + 1;

	while (getNodeValue(sLevel + 1, sIndex * 2) != -1) {
		sLevel++;
		sIndex = sIndex * 2;
	}
}

void bst::collectSubtree(int level, int index, vector<int>& values) {
	
	int currentValue = getNodeValue(level, index);
	
	if (currentValue == -1) {
		return;
	}
	
	values.push_back(currentValue);

	setNodeValue(level, index, -1);

	collectSubtree(level + 1, index * 2, values);     
	collectSubtree(level + 1, index * 2 + 1, values); 
}

void bst::removeNodeAt(int level, int index) {
	
	int leftChildVal = getNodeValue(level + 1, index * 2);
	int rightChildVal = getNodeValue(level + 1, index * 2 + 1);

	if (leftChildVal == -1 && rightChildVal == -1) {
		setNodeValue(level, index, -1);
		cout << "Informacja: Usunieto lisc." << endl;
	}

	else if (leftChildVal != -1 && rightChildVal != -1) {
		cout << "Informacja: Usuwanie wezla z 2 dzieci (przez kopiowanie)." << endl;

		int sLevel = 0, sIndex = 0;
		findSuccessor(level, index, sLevel, sIndex);
		int successorValue = getNodeValue(sLevel, sIndex);

		setNodeValue(level, index, successorValue);
		removeNodeAt(sLevel, sIndex);
	}

	
	else {
		cout << "Informacja: Usuwanie wezla z 1 dzieckiem (przez ponowne dodanie)." << endl;

		int childLevel = level + 1;
		int childIndex = (leftChildVal != -1) ? (index * 2) : (index * 2 + 1);

		vector<int> descendants;

		collectSubtree(childLevel, childIndex, descendants);

		setNodeValue(level, index, -1);

		cout << "Informacja: Ponowne dodawanie " << descendants.size() << " potomkow..." << endl;
		for (int value : descendants) {
			add(value);
		}
	}
}

void bst::remove(int value) {
	int level = 0;
	int index = 0;
	bool found = false;

	findNode(value, level, index, found);

	if (!found) {
		cout << "Elementu " << value << " nie ma w drzewie." << endl;
		return;
	}

	removeNodeAt(level, index);
	cout << "Zakonczono usuwanie " << value << "." << endl;
}