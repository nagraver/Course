#include <iomanip>
#include <iostream>

#include "structures.h"

using namespace ::std;

string center(const string &text, int width) {
    if (width <= text.length()) return text;

    int left_padding = (width - text.length()) / 2;
    int right_padding = width - text.length() - left_padding;

    return string(left_padding, ' ') + text + string(right_padding, ' ');
}

void print_roster(roster **begin) {
    const int ITEMS_PER_PAGE = 5;
    int page = 0;
    int total_items = 0;

    for (roster *current = *begin; current; current = current->next) total_items++;

    if (total_items == 0) {
        cout << "The list is empty.\n";
        return;
    }

    while (true) {
        int start_index = page * ITEMS_PER_PAGE;
        int end_index = min(start_index + ITEMS_PER_PAGE, total_items);

        cout << center("id", 4) << " | " << setw(12) << center("Department", 12) << " | " << setw(15)
             << center("Full Name", 15) << " | " << setw(10) << center("Position", 10) << " | " << setw(10)
             << center("Salary", 10) << " | " << setw(15) << center("Theme Number", 15) << " | " << setw(18)
             << center("Work Experience", 18) << endl;

        cout << string(4, '-') << "-+-" << string(12, '-') << "-+-" << string(15, '-') << "-+-" << string(10, '-')
             << "-+-" << string(10, '-') << "-+-" << string(15, '-') << "-+-" << string(18, '-') << endl;

        int index = 0;
        for (roster *current = *begin; current; current = current->next, index++) {
            if (index >= start_index && index < end_index) {
                cout << left << setw(4) << current->info.id << " | " << setw(12) << current->info.department << " | "
                     << setw(15) << current->info.name << " | " << setw(10) << current->info.position << " | "
                     << setw(10) << current->info.salary << " | " << setw(15) << current->info.theme_number << " | "
                     << setw(18) << current->info.work_duration << endl;
            }
        }

        char command;
        cout << "\nPage " << page + 1 << " of " << (total_items + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE << "\n";
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
