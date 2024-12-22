#include <cstdlib>
#include <iostream>

#include "files.h"
#include "refactoring.h"
#include "scrolling.h"
#include "service.h"
#include "sort.h"
#include "structures.h"

using namespace std;

int main() {
    char choice;
    char c;
    roster *begin = nullptr;

    while (true) {
        system("clear");
        cout << "1) Add to the beginning of the list\n";
        cout << "2) Add to the end of the list\n";
        cout << "3) Organize the list\n";
        cout << "4) Display data\n";
        cout << "5) Sort list\n";
        cout << "6) Search\n";
        cout << "7) Delete roster\n";
        cout << "e) Edit\n";
        cout << "d) Delete first element\n";
        cout << "s) Save data\n";
        cout << "l) Load data\n";
        cout << "q) Exit\n";

        choice = getch();
        switch (choice) {
            case '1':
                add_first(&begin, enter_container());
                break;
            case '2':
                add_last(&begin, enter_container());
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
            case '7':
                // cout << "You are going to delete roster.\nPress d to confirm\n";
                // c = getch();
                // if (choice == 'd')
                //     while (begin) clear_first(&begin);
                // else cout << "Canceled\n";
                // break;
                while (begin) clear_first(&begin);
            case 'e':
            case 'E':
                edit(&begin);
                break;
            case 'd':
            case 'D':
                // cout << "You are going to firts element.\nPress any key to confirm\nPress q to cancel\n";
                // c = getch();
                // if (c == 'q') {
                //     cout << "Canceled\n";
                //     break;
                // }
                clear_first(&begin);
                break;
            case 's':
            case 'S':
                save_roster(&begin);
                break;
            case 'l':
            case 'L':
                load_roster(&begin);
                break;
            case 'Q':
            case 'q':
                while (begin) clear_first(&begin);
                cout << "List cleared\n";
                return 0;
            default:
                cout << "Unknown command\n";
                break;
        }
    }
}
