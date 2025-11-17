/**
 * @file main.cpp
 * @brief Plik zawierajacy funkcje menu oraz funkcje main programu obslugujacego drzewo BST.
 */

#include "bst.h"
#include "bstIO.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Wyswietla menu programu i umozliwia wykonywanie operacji na drzewie BST.
 *
 * Menu obsluguje operacje:
 * - dodawanie elementu,
 * - usuwanie elementu,
 * - usuwanie calego drzewa,
 * - wyszukiwanie sciezki do elementu,
 * - wyswietlanie drzewa w wybranym porzadku,
 * - zapisywanie drzewa do pliku tekstowego,
 * - zapisywanie i wczytywanie z pliku binarnego,
 * - wczytywanie liczb z pliku tekstowego.
 */
void menu() {
    bst tree;
    int choice, value;
    string method;

    do {
        cout << "\n=== MENU DRZEWA BST ===\n";
        cout << "1. Dodaj nowy element\n";
        cout << "2.Usun element\n";
        cout << "3. Usun cale drzewo\n";
        cout << "4. Szukaj drogi do elementu\n";
        cout << "5. Wyswietl drzewo (preorder/inorder/postorder)\n";
        cout << "6. Zapisz drzewo do pliku\n";
        cout << "7. Zapisz drzewo do pliku binarnego\n";
        cout << "8. Wczytaj drzewo z pliku binarnego\n";
        cout << "9. Wczytaj plik tekstowy z liczbami do drzewa\n";
        cout << "0. Wyjdz\n";
        cout << "Twoj wybor: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Podaj calkowita liczbe: ";
            cin >> value;
            tree.add(value);
            break;
        }
        case 2: {
            cout << "Podaj calkowita liczbe do usuniecia: ";
            cin >> value;
            tree.remove(value);
            break;
        }
        case 3: {
            tree.clear();
            cout << "Drzewo zostalo usuniete.\n";
            break;
        }
        case 4: {
            cout << "Podaj calkowita liczbe do znalezienia: ";
            cin >> value;
            tree.findPath(value);
            break;
        }
        case 5: {
            cout << "Podaj metode (preorder/inorder/postorder): ";
            cin >> method;
            tree.printTree(method);
            break;
        }
        case 6: {
            tree.saveToFile("drzewo.txt");
            break;
        }
        case 7: {
            string fname;
            cout << "Podaj nazwe pliku BIN: ";
            cin >> fname;
            bstIO::saveBinary(fname, tree);
            break;
        }
        case 8: {
            string fname;
            cout << "Podaj nazwe pliku BIN: ";
            cin >> fname;
            bstIO::loadBinary(fname, tree);
            break;
        }
        case 9: {
            string fname;
            cout << "Podaj nazwe pliku TXT: ";
            cin >> fname;

            char mode;
            cout << "Dodac do istniejacego drzewa? (t/n): ";
            cin >> mode;

            bstIO::loadFromTextFile(fname, tree, mode == 't' || mode == 'T');
            break;
        }
        case 0:
            cout << "Koniec programu.\n";
            break;
        default:
            cout << "Niepoprawny wybor!\n";
        }
    } while (choice != 0);
}

/**
 * @brief Glowna funkcja programu. Uruchamia menu obslugi drzewa BST.
 * @return Kod zakonczenia programu.
 */
int main() {
    menu();
    return 0;
}
