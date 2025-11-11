#ifndef bst_H
#define bst_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

class bst {
private:
	vector<vector<int>> tree; // 2D vector: tree[level][index]

	void preorder(int level, int index);
	void inorder(int level, int index);
	void postorder(int level, int index);
	void ensureLevel(int level);

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
