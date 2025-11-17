/**
 * @file bstIO.cpp
 * @brief Implementacja funkcji wczytywania i zapisywania drzewa BST do plikow binarnych i tekstowych.
 */

#include "bstIO.h"
#include <fstream>
#include <cstdint>
#include <iostream>

using namespace std;

/**
 * @brief Zapisuje cale drzewo BST do pliku binarnego.
 *
 * Format pliku:
 * - liczba poziomow (int32_t),
 * - dla kazdego poziomu: liczba elementow (int32_t),
 * - kolejne wartosci wezlow danego poziomu (int32_t).
 *
 * @param filename Nazwa pliku binarnego.
 * @param treeObj Obiekt drzewa BST do zapisania.
 */
void bstIO::saveBinary(const string& filename, const bst& treeObj) {
    ofstream ofs(filename, ios::binary);
    if (!ofs.is_open()) {
        cout << "BLAD: Nie mozna otworzyc pliku binarnego: " << filename << endl;
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

/**
 * @brief Wczytuje drzewo BST z pliku binarnego.
 *
 * Oczekiwany format zgodny z saveBinary():
 * - liczba poziomow,
 * - dla kazdego poziomu liczba wezlow,
 * - wartosci wezlow.
 *
 * Po wczytaniu struktura drzewa jest w calosci nadpisywana.
 *
 * @param filename Nazwa pliku do wczytania.
 * @param treeObj Obiekt drzewa, do ktorego dane maja zostac wczytane.
 */
void bstIO::loadBinary(const string& filename, bst& treeObj) {
    ifstream ifs(filename, ios::binary);
    if (!ifs.is_open()) {
        cout << "BLAD: Nie mozna otworzyc pliku binarnego: " << filename << endl;
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

/**
 * @brief Wczytuje liczby z pliku tekstowego i dodaje je do drzewa.
 *
 * Kazda liczba jest odczytywana sekwencyjnie i dodawana przez standardowa funkcje add().
 *
 * @param filename Nazwa pliku tekstowego.
 * @param treeObj Obiekt drzewa BST, do ktorego dane maja zostac wczytane.
 * @param append Okresla czy dopisywac dane do istniejacego drzewa (true), czy je wyczyscic przed wczytaniem (false).
 */
void bstIO::loadFromTextFile(const string& filename, bst& treeObj, bool append) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "BLAD: Nie mozna otworzyc pliku: " << filename << endl;
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

    cout << "Wczytano " << count << " wartosci z pliku: " << filename << endl;
}
