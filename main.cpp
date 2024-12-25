#include <cstdlib>
#include <iostream>

#include "./headers/files.h"
#include "./headers/refactoring.h"
#include "./headers/scrolling.h"
#include "./headers/service.h"
#include "./headers/structures.h"

using namespace std;

void anyKeyToContiniue() {
    cout << "Press any key to continiue\n";
    char c = getch();
    system("clear");
}

int main() {
    char c, choice;
    roster *begin = nullptr;
    NII content;
    while (true) {
        cout << "1) Add to the beginning of List\n";
        cout << "2) Add to the end of List\n";
        cout << "3) Organize List\n";
        cout << "4) Display data\n";
        cout << "5) Sort list\n";
        cout << "6) Search\n";
        cout << "e) Edit\n";
        cout << "d) Delete selected element\n";
        cout << "D) Delete roster\n";
        cout << "s) Save data\n";
        cout << "l) Load data\n";
        cout << "q) Exit\n";

        choice = getch();
        switch (choice) {
            case '1':
                system("clear");
                content = enter_container();
                content.id = 0;
                addFirst(&begin, content);
                system("clear");
                printRosterHeader();
                printRoster(content);
                anyKeyToContiniue();
                break;
            case '2':
                system("clear");
                content = enter_container();
                addLast(&begin, content);
                system("clear");
                printRosterHeader();
                printRoster(content);
                anyKeyToContiniue();
                break;
            case '3':
                system("clear");
                while (true) {
                    content = enter_container();
                    addLast(&begin, content);
                    system("clear");
                    printRosterHeader();
                    printRoster(content);
                    cout << "Continue - any key\n";
                    cout << "Cancel - q\n";
                    c = getch();
                    system("clear");
                    if (c != 'q' and c != 'Q') continue;
                    break;
                }
                break;
            case '4':
                system("clear");
                scrolling(&begin);
                anyKeyToContiniue();
                break;
            case '5':
                system("clear");
                insertionSort(&begin);
                anyKeyToContiniue();
                break;
            case '6':
                system("clear");
                searchByField(&begin);
                anyKeyToContiniue();
                break;
            case 'e':
            case 'E':
                system("clear");
                edit(&begin);
                anyKeyToContiniue();
                break;
            case 'd':
                system("clear");
                cout << "Delete selected element\n";
                cout << "Confirm - d\n";
                cout << "Cancel - any key\n";
                c = getch();
                if (c != 'd') break;
                system("clear");
                clearSelected(&begin);
                anyKeyToContiniue();
                break;
            // case 'd':
            //     system("clear");
            //     cout << "Delete firts element\n";
            //     cout << "Confirm - d\n";
            //     cout << "Cancel - any key\n";
            //     c = getch();
            //     if (c != 'd') break;
            //     clearFirst(&begin);
            //     anyKeyToContiniue();
            //     break;
            case 'D':
                system("clear");
                cout << "Delete roster\nPress D to confirm\n";
                cout << "Confirm - D\n";
                cout << "Cancel - any key\n";
                c = getch();
                if (c != 'D') break;
                while (begin) clearFirst(&begin);
                system("clear");
                cout << "List cleared\n";
                anyKeyToContiniue();
                break;
            case 's':
            case 'S':
                system("clear");
                save_roster(&begin);
                anyKeyToContiniue();
                break;
            case 'l':
            case 'L':
                system("clear");
                load_roster(&begin);
                anyKeyToContiniue();
                break;
            case 'Q':
            case 'q':
                system("clear");
                cout << "All unsaved data will be lost.\n";
                cout << "Continiue - q\n";
                cout << "Cancel - any key\n";
                c = getch();
                if (c != 'q' and c != 'Q') break;
                while (begin) clearFirst(&begin);
                system("clear");
                cout << "List cleared\n";
                return 0;
            default:
                system("clear");
                cout << "Unknown command\n";
                anyKeyToContiniue();
                break;
        }
    }
}
