#include <cstdlib>
#include <iostream>
#include <string>

#include "service.h"
#include "structures.h"

using namespace ::std;

void scrolling(roster **begin) {
    const int ITEMS_PER_PAGE = 5;
    int page = 0;
    int total_items = 0;

    for (roster *current = *begin; current; current = current->next) total_items++;

    if (total_items == 0) {
        cout << "The list is empty.\n";
        return;
    }

    while (true) {
        system("clear");
        int start_index = page * ITEMS_PER_PAGE;
        int end_index = min(start_index + ITEMS_PER_PAGE, total_items);
        printRosterHeader();
        int index = 0;
        for (roster *current = *begin; current; current = current->next, index++) {
            if (index >= start_index && index < end_index) { printRoster(current->info); }
        }

        cout << "Page " << page + 1 << " of " << (total_items + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE << " (n/p/q): \n";

        char command;
        command = getch();

        if (command == 'N' || command == 'n') {
            if (end_index < total_items) page++;
        } else if (command == 'P' || command == 'p') {
            if (page > 0) page--;
        } else if (command == 'Q' || command == 'q') {
            break;
        } else {
            cout << "Invalid command\n";
        }
    }
}

void searchByField(roster **begin) {
    char choice =
        getChoice("ID - 1\nDepartment - 2\nName - 3\nTheme - 4\nDuration - 5\nPosition - 6\nSalary - 7\nCancel - q\n",
                  "1234567q");

    if (choice == 'q' || choice == 'Q') return;

    if (choice == '1' || choice == '2' || choice == '4' || choice == '5' || choice == '6' || choice == '7') {
        int value;
        cout << "Enter value\nInput: ";
        cin >> value;
        system("clear");
        printRosterHeader();
        for (roster *current = *begin; current; current = current->next) {
            if ((choice == '1' && current->info.id == value) || (choice == '2' && current->info.department == value) ||
                (choice == '4' && current->info.theme_number == value) ||
                (choice == '5' && current->info.work_duration == value) ||
                (choice == '6' && current->info.position == value) ||
                (choice == '7' && current->info.salary == value)) {
                printRoster(current->info);
            }
        }
    } else if (choice == '3') {
        string _value;
        cout << "Enter value\nInput: ";
        cin.ignore();
        getline(cin, _value);
        system("clear");

        printRosterHeader();
        for (roster *current = *begin; current; current = current->next) {
            if (choice == '3' && current->info.name == _value) printRoster(current->info);
        }
    } else {
        cout << "Error\n";
    }
}
