#include <iostream>

#include "files.h"
#include "refactoring.h"
#include "scrolling.h"
#include "sort.h"
#include "structures.h"

using namespace std;

int main() {
    char choice;
    roster *begin = nullptr;

    while (true) {
        cout << endl;
        cout << "1) Add to the beginning of the list\n";
        cout << "2) Add to the end of the list\n";
        cout << "3) Organize the list\n";
        cout << "4) Display data\n";
        cout << "5) Sort list\n";
        cout << "6) Search\n";
        cout << "e) Edit\n";
        cout << "d) Delete first element\n";
        cout << "s) Save data\n";
        cout << "l) Load data\n";
        cout << "q) Exit\n";

        cout << "Input: ";
        cin >> choice;

        switch (choice) {
            case '1':
                add_first(&begin, enter_container());
                cout << "Element added to the beginning\n";
                break;
            case '2':
                add_last(&begin, enter_container());
                cout << "Element added to the end\n";
                break;
            case '3':
                add_many(&begin);
                break;
            case '4':
                scrolling(&begin);
                break;
            case '5':
                insertionSort(&begin);
                break;
            case '6':
                searchByField(&begin);
                break;
            case 'e':
            case 'E':
                edit(&begin);
                break;
            case 'd':
            case 'D':
                clear_first(&begin);
                cout << "First element deleted\n";
                break;
            case 's':
            case 'S':
                save_roster(&begin);
                break;
            case 'l':
            case 'L':
                load_roster(&begin);
                break;
            case 'q':
            case 'Q':
                while (begin) clear_first(&begin);
                cout << "List cleared\n";
                return 0;
            default:
                cout << "Error\n";
                break;
        }
    }
}
