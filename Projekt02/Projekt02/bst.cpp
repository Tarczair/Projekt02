#include "BST.h"

bst::bst() {}

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

void BST::remove(int value) {}
void BST::findPath(int value) {}
void BST::saveToFile(const string& filename) {}
