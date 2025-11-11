#ifndef bst_H
#define bst_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <fstream> 

using namespace std;

class bst {
private:
	vector<vector<int>> tree; // 2D vector: tree[level][index]

	void preorder(int level, int index);
	void inorder(int level, int index);
	void postorder(int level, int index);
	void ensureLevel(int level);

	// Funkcje pomocnicze do usuwania
	void findNode(int value, int& level, int& index, bool& found) const;
	void findSuccessor(int startLevel, int startIndex, int& sLevel, int& sIndex) const;
	void removeNodeAt(int level, int index);
	void collectSubtree(int level, int index, vector<int>& values);

	// Funkcje pomocnicze do obs³ugi wektora
	int getNodeValue(int level, int index) const;
	void setNodeValue(int level, int index, int value);

	

public:
	bst();

	void add(int value);
	void remove(int value);
	void clear();
	void printTree(string method);
	void printGraphical();
	void saveToFile(const string& filename);
	void findPath(int value);
};

#endif
