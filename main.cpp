#include <iomanip>
#include <iostream>
#include <string>

#include "files.h"
#include "refactoring.h"
#include "structures.h"

using namespace std;

void print_roster(roster **begin);

int main() {
    char value;
    roster *begin = nullptr;

    while (true) {
        cout << endl;
        cout << "1) Add to the beginning of the list\n";
        cout << "2) Add to the end of the list\n";
        cout << "3) Organize the list\n";
        cout << "4) Display data\n";
        cout << "d) Delete the first element\n";
        cout << "s) Save data\n";
        cout << "l) Load data\n";
        cout << "q) Exit\n";

        cout << "Input: ";
        cin >> value;

        switch (value) {
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
                print_roster(&begin);
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

void print_roster(roster **begin) {
    const int ITEMS_PER_PAGE = 5;
    int page = 0;
    int total_items = 0;

    for (roster *current = *begin; current; current = current->next)
        total_items++;

    if (total_items == 0) {
        cout << "The list is empty.\n";
        return;
    }

    while (true) {
        int start_index = page * ITEMS_PER_PAGE;
        int end_index = min(start_index + ITEMS_PER_PAGE, total_items);

        cout << left << setw(12) << "Department"
             << " | " << setw(15) << "Full Name"
             << " | " << setw(10) << "Position"
             << " | " << setw(10) << "Salary"
             << " | " << setw(15) << "Theme Number"
             << " | " << setw(18) << "Work Experience" << endl;

        cout << string(12, '-') << "-+-" << string(15, '-') << "-+-"
             << string(10, '-') << "-+-" << string(10, '-') << "-+-"
             << string(15, '-') << "-+-" << string(18, '-') << endl;

        int index = 0;
        for (roster *current = *begin; current;
             current = current->next, index++) {
            if (index >= start_index && index < end_index) {
                cout << setw(12) << current->info.department << " | "
                     << setw(15) << current->info.name << " | " << setw(10)
                     << current->info.position << " | " << setw(10)
                     << current->info.salary << " | " << setw(15)
                     << current->info.theme_number << " | " << setw(18)
                     << current->info.work_duration << endl;
            }
        }

        char command;
        cout << "\nPage " << page + 1 << " of "
             << (total_items + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE << "\n";
        cout << "Enter command (n/p/q): ";
        cin >> command;

        if (command == 'N' || command == 'n') {
            if (end_index < total_items) page++;
        } else if (command == 'P' || command == 'p') {
            if (page > 0) page--;
        } else if (command == 'Q' || command == 'q') {
            break;
        } else {
            cout << "Invalid command. Try again.\n";
        }
    }
}
