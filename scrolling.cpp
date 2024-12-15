#include <iomanip>
#include <iostream>

#include "structures.h"

using namespace::std;


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
