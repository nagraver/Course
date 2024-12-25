#include <cstdlib>
#include <iostream>
#include <string>

#include "./headers/service.h"
#include "./headers/structures.h"

using namespace ::std;

void scrolling(roster **begin) {
    const int ITEMS_PER_PAGE = 5;
    int page = 0;
    int total_items = 0;

    for (roster *current = *begin; current; current = current->next) total_items++;

    if (total_items == 0) {
        cout << "List is empty.\n";
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
    printRosterHeader();
    cout << "Choose column (i/d/n/p/s/t/w)\nQuit - q\n";
    char choice = getch();

    if (choice == 'q' || choice == 'Q') return;

    system("clear");
    if (choice == 'n') {
        string searchValue = nameInputCheck("Enter value");
        for (roster *current = *begin; current; current = current->next) {
            if (current->info.name == searchValue) {
                printRosterHeader();
                printRoster(current->info);
            }
        }
    } else {
        int searchValue = intInputCheck("Enter value");

        for (roster *current = *begin; current; current = current->next) {
            bool match = false;

            switch (choice) {
                case 'i':
                    match = (current->info.id == searchValue);
                    break;
                case 'd':
                    match = (current->info.department == searchValue);
                    break;
                case 't':
                    match = (current->info.theme_number == searchValue);
                    break;
                case 'w':
                    match = (current->info.work_duration == searchValue);
                    break;
                case 'p':
                    match = (current->info.position == searchValue);
                    break;
                case 's':
                    match = (current->info.salary == searchValue);
                    break;
            }

            if (match) {
                printRosterHeader();
                printRoster(current->info);
            }
        }
    }
}
