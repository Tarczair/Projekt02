#include "bst.h"

/**
 * @brief Konstruktor klasy bst. Tworzy puste drzewo.
 */
bst::bst() {}


/**
 * @brief Usuwa cale drzewo (czyœci wszystkie poziomy).
 */
void bst::clear() {
    tree.clear();
}


/**
 * @brief Przejscie inorder (lewo - korzen - prawo).
 * @param level Aktualny poziom w drzewie.
 * @param index Indeks wezla na danym poziomie.
 */
void bst::inorder(int level, int index) {
    if (level >= tree.size() || index >= tree[level].size() || tree[level][index] == -1) return;
    inorder(level + 1, index * 2);
    cout << tree[level][index] << " ";
    inorder(level + 1, index * 2 + 1);
}


/**
 * @brief Przejscie postorder (lewo - prawo - korzen).
 * @param level Aktualny poziom w drzewie.
 * @param index Indeks wezla.
 */
void bst::postorder(int level, int index) {
    if (level >= tree.size() || index >= tree[level].size() || tree[level][index] == -1) return;
    postorder(level + 1, index * 2);
    postorder(level + 1, index * 2 + 1);
    cout << tree[level][index] << " ";
}


/**
 * @brief Przejscie preorder (korzen - lewo - prawo).
 * @param level Aktualny poziom w drzewie.
 * @param index Indeks wezla.
 */
void bst::preorder(int level, int index) {
    if (level >= tree.size() || index >= tree[level].size() || tree[level][index] == -1) return;
    cout << tree[level][index] << " ";
    preorder(level + 1, index * 2);
    preorder(level + 1, index * 2 + 1);
}


/**
 * @brief Zapewnia istnienie okreslonego poziomu drzewa.
 * @param level Poziom wymagany.
 */
void bst::ensureLevel(int level) {
    if (level >= tree.size()) tree.resize(level + 1);
}


/**
 * @brief Dodaje wartosc do drzewa BST.
 * @param value Wartosc do dodania.
 */
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


/**
 * @brief Wypisuje drzewo w wybranym porzadku oraz jego forme graficzna.
 * @param method "preorder", "inorder" lub "postorder".
 */
void bst::printTree(string method) {
    cout << "Drzewo (" << method << "): ";
    if (method == "preorder") preorder(0, 0);
    else if (method == "inorder") inorder(0, 0);
    else if (method == "postorder") postorder(0, 0);
    cout << endl;
    printGraphical();
}


/**
 * @brief Wyswietla drzewo w formie graficznej w konsoli.
 */
void bst::printGraphical() {
    if (tree.empty()) {
        cout << "Drzewo jest puste!\n";
        return;
    }

    int height = tree.size();
    int baseSpacing = 32;

    for (int level = 0; level < height; ++level) {
        int nodes = tree[level].size();
        int spacing = baseSpacing >> level;
        if (spacing < 2) spacing = 2;

        // drukowanie wartosci
        cout << string(spacing / 2, ' ');
        for (int i = 0; i < nodes; ++i) {
            if (tree[level][i] != -1)
                cout << tree[level][i];
            else
                cout << " ";
            cout << string(spacing, ' ');
        }
        cout << endl;

        // drukowanie galezi
        if (level < height - 1) {
            cout << string(spacing / 2, ' ');
            for (int i = 0; i < nodes; ++i) {
                int leftIdx = i * 2;
                int rightIdx = i * 2 + 1;
                bool hasLeft = leftIdx < tree[level + 1].size() && tree[level + 1][leftIdx] != -1;
                bool hasRight = rightIdx < tree[level + 1].size() && tree[level + 1][rightIdx] != -1;

                if (hasLeft && hasRight) cout << "/ \\";
                else if (hasLeft) cout << "/";
                else if (hasRight) cout << "\\";
                else cout << " ";

                cout << string(spacing, ' ');
            }
            cout << endl;
        }
    }
}


/**
 * @brief Wyszukuje wartosc i wypisuje sciezke od korzenia do wezla.
 * @param value Szukana wartosc.
 */
void bst::findPath(int value) {
    if (tree.empty()) {
        cout << "Drzewo jest puste. " << endl;
        return;
    }

    cout << "Sciezka do: " << value << ": ";

    int level = 0;
    int index = 0;

    while (true) {

        if (level >= tree.size() || index >= tree[level].size() || tree[level][index] == -1) {
            cout << "\nElementu nie zostal znaleziono." << endl;
            return;
        }

        int currentValue = tree[level][index];
        cout << currentValue;

        if (currentValue == value) {
            cout << "\nElement zostal znaleziony." << endl;
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


/**
 * @brief Zapisuje zawartosc drzewa do pliku tekstowego.
 * @param filename Nazwa pliku.
 */
void bst::saveToFile(const string& filename) {

    ofstream plik(filename);

    if (!plik.is_open()) {
        cout << "BLAD: Nie mozna otworzyc pliku do zapisu: " << filename << endl;
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


/**
 * @brief Pobiera wartosc wezla.
 * @param level Poziom wezla.
 * @param index Indeks wezla.
 * @return Wartosc lub -1 jesli nie istnieje.
 */
int bst::getNodeValue(int level, int index) const {
    if (level >= tree.size() || index >= tree[level].size()) {
        return -1;
    }
    return tree[level][index];
}


/**
 * @brief Ustawia wartosc w wezle. Rozszerza drzewo w razie potrzeby.
 * @param level Poziom wezla.
 * @param index Indeks wezla.
 * @param value Wartosc do ustawienia.
 */
void bst::setNodeValue(int level, int index, int value) {
    ensureLevel(level);
    if (index >= tree[level].size()) {
        tree[level].resize(index + 1, -1);
    }
    tree[level][index] = value;
}


/**
 * @brief Znajduje wezel o podanej wartosci.
 * @param value Szukana wartosc.
 * @param level Poziom znalezionego wezla (wynik).
 * @param index Indeks znalezionego wezla (wynik).
 * @param found Czy znaleziono wartosc.
 */
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


/**
 * @brief Znajduje nastepnika danego wezla (minimum w prawym poddrzewie).
 * @param startLevel Poziom wezla.
 * @param startIndex Indeks wezla.
 * @param sLevel Poziom nastepnika (wynik).
 * @param sIndex Indeks nastepnika (wynik).
 */
void bst::findSuccessor(int startLevel, int startIndex, int& sLevel, int& sIndex) const {

    sLevel = startLevel + 1;
    sIndex = startIndex * 2 + 1;

    while (getNodeValue(sLevel + 1, sIndex * 2) != -1) {
        sLevel++;
        sIndex = sIndex * 2;
    }
}


/**
 * @brief Zbiera wartosci z poddrzewa i usuwa je z drzewa.
 * @param level Poziom aktualnego wezla.
 * @param index Indeks aktualnego wezla.
 * @param values Wektor wynikowy.
 */
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


/**
 * @brief Usuwa wezel na danej pozycji zgodnie z zasadami BST.
 * @param level Poziom wezla.
 * @param index Indeks wezla.
 */
void bst::removeNodeAt(int level, int index) {

    int leftChildVal = getNodeValue(level + 1, index * 2);
    int rightChildVal = getNodeValue(level + 1, index * 2 + 1);

    // przypadek: brak dzieci
    if (leftChildVal == -1 && rightChildVal == -1) {
        setNodeValue(level, index, -1);
        cout << "Informacja: Usunieto lisc." << endl;
    }

    // przypadek: dwoje dzieci
    else if (leftChildVal != -1 && rightChildVal != -1) {
        cout << "Informacja: Usuwanie wezla z 2 dziecmi (przez kopiowanie)." << endl;

        int sLevel = 0, sIndex = 0;
        findSuccessor(level, index, sLevel, sIndex);
        int successorValue = getNodeValue(sLevel, sIndex);

        setNodeValue(level, index, successorValue);
        removeNodeAt(sLevel, sIndex);
    }

    // przypadek: jedno dziecko
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


/**
 * @brief Usuwa wartosc z drzewa BST.
 * @param value Wartosc do usuniecia.
 */
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
    cout << "Pomyslnie zakonczono usuwanie " << value << "." << endl;
}
