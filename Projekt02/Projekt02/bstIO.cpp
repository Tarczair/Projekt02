#include "bstIO.h"
#include <fstream>
#include <cstdint>
#include <iostream>

using namespace std;

void bstIO::saveBinary(const string& filename, const bst& treeObj) {
    ofstream ofs(filename, ios::binary);
    if (!ofs.is_open()) {
        cout << "B£¥D: Nie mozna otworzyæ pliku binarnego: " << filename << endl;
        return;
    }

    const auto& tree = treeObj.getTree();

    int32_t levels = tree.size();
    ofs.write((char*)&levels, sizeof(levels));

    for (const auto& level : tree) {
        int32_t sz = level.size();
        ofs.write((char*)&sz, sizeof(sz));

        for (int val : level) {
            int32_t v = val;
            ofs.write((char*)&v, sizeof(v));
        }
    }

    cout << "Zapisano drzewo binarnie do pliku: " << filename << endl;
}

void bstIO::loadBinary(const string& filename, bst& treeObj) {
    ifstream ifs(filename, ios::binary);
    if (!ifs.is_open()) {
        cout << "B£¥D: Nie mozna otworzyæ pliku binarnego: " << filename << endl;
        return;
    }

    int32_t levels;
    ifs.read((char*)&levels, sizeof(levels));

    vector<vector<int>> newTree(levels);

    for (int i = 0; i < levels; i++) {
        int32_t sz;
        ifs.read((char*)&sz, sizeof(sz));
        newTree[i].resize(sz);

        for (int j = 0; j < sz; j++) {
            int32_t v;
            ifs.read((char*)&v, sizeof(v));
            newTree[i][j] = v;
        }
    }

    treeObj.setTree(newTree);

    cout << "Wczytano drzewo z pliku binarnego: " << filename << endl;
}

void bstIO::loadFromTextFile(const string& filename, bst& treeObj, bool append) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "B£¥D: Nie mozna otworzyæ pliku: " << filename << endl;
        return;
    }

    if (!append) {
        treeObj.clear();
        cout << "Drzewo wyczyszczone przed wczytaniem.\n";
    }

    int value;
    int count = 0;

    while (ifs >> value) {
        treeObj.add(value);
        count++;
    }

    cout << "Wczytano " << count << " wartoœci z pliku: " << filename << endl;
}
