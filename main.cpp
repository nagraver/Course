#include <cstdlib>
#include <iostream>

#include "files.h"
#include "refactoring.h"
#include "scrolling.h"
#include "service.h"
#include "sort.h"
#include "structures.h"

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
        cout << "1) Add to the beginning of the list\n";
        cout << "2) Add to the end of the list\n";
        cout << "3) Organize the list\n";
        cout << "4) Display data\n";
        cout << "5) Sort list\n";
        cout << "6) Search\n";
        cout << "e) Edit\n";
        cout << "d) Delete first element\n";
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
                add_first(&begin, content);

                printRosterHeader();
                printRoster(content);
                anyKeyToContiniue();
                break;
            case '2':
                system("clear");
                content = enter_container();
                add_last(&begin, content);
                printRosterHeader();
                printRoster(content);
                anyKeyToContiniue();
                break;
            case '3':
                system("clear");
                while (true) {
                    content = enter_container();
                    add_last(&begin, content);
                    cout << "Continue organizing the list: any key\n";
                    cout << "Finish organizing the list: q\n";
                    c = getch();
                    system("clear");
                    if (c != 'q') continue;
                    break;
                }
                break;
            case '4':
                system("clear");
                scrolling(&begin);
                break;
            case '5':
                system("clear");
                insertionSort(&begin);
                cout << "List been sorted\n";
                anyKeyToContiniue();
                break;
            case '6':
                system("clear");
                searchByField(&begin);
                anyKeyToContiniue();
                break;
            case '7':
            case 'e':
            case 'E':
                system("clear");
                edit(&begin);
                anyKeyToContiniue();
                break;
            case 'd':
                system("clear");
                cout << "Delete firts element\nPress d to confirm\nPress any key to cancel\n";
                c = getch();
                if (c != 'd') break;
                clear_first(&begin);
                anyKeyToContiniue();
                break;
            case 'D':
                system("clear");
                cout << "You are going to delete roster\nPress D to confirm\nPress any key to cancel\n";
                c = getch();
                if (c != 'D') break;
                while (begin) clear_first(&begin);
                system("clear");
                anyKeyToContiniue();
                break;
            case 's':
            case 'S':
                system("clear");
                save_roster(&begin);
                break;
            case 'l':
            case 'L':
                system("clear");
                load_roster(&begin);
                break;
            case 'Q':
            case 'q':
                system("clear");
                cout << "All unsaved data will be lost.\nContiniue - q\nCancel - any key\n";
                c = getch();
                if (c != 'q' and c != 'Q') break;
                while (begin) clear_first(&begin);
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
