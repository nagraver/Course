#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include "./headers/service.h"
#include "./headers/structures.h"

using namespace std;

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

        cout << "Page " << page + 1 << " of " << (total_items + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE << endl;
        char choice = getChoice("1 - Previous\n2 - Next\n", "12");

        if (choice == '1') {
            if (page > 0) page--;
        } else if (choice == '2') {
            if (end_index < total_items) page++;
        } else if (choice == ESC) break;
    }
}

void findByField(roster **begin) {
    if (*begin == nullptr) {
        cout << "List is empty.\n";
        return;
    }
    string prompt =
        "Search by:\n1 - ID\n2 - Department\n3 - name\n4 - Theme\n5 - Experience\n6 - Position\n7 - Salary\n";
    char choice = getChoice(prompt, "1234567");
    if (choice == ESC) return;
    system("clear");
    if (choice == '3') {
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
                case '1':
                    match = (current->info.id == searchValue);
                    break;
                case '2':
                    match = (current->info.department == searchValue);
                    break;
                case '4':
                    match = (current->info.theme_number == searchValue);
                    break;
                case '5':
                    match = (current->info.work_duration == searchValue);
                    break;
                case '6':
                    match = (current->info.position == searchValue);
                    break;
                case '7':
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

void analyzeThemes(roster **begin) {
    if (*begin == nullptr) {
        cout << "List is empty.\n";
        return;
    }
    int rosterCount;
    for (roster *current = *begin; current; current = current->next) rosterCount++;

    int themeCount = 0;
    int *themes = new int[rosterCount];
    int *employeeCount = new int[rosterCount];
    int *salaryFund = new int[rosterCount];

    for (roster *current = *begin; current; current = current->next) {
        int themeNumber = current->info.theme_number;
        int salary = current->info.salary;

        bool found = false;
        for (int i = 0; i < themeCount; i++) {
            if (themes[i] == themeNumber) {
                employeeCount[i]++;
                salaryFund[i] += salary;
                found = true;
                break;
            }
        }

        if (!found) {
            themes[themeCount] = themeNumber;
            employeeCount[themeCount] = 1;
            salaryFund[themeCount] = salary;
            themeCount++;
        }
    }

    cout << center("Theme Number", 15) << " | " << center("Employee Count", 15) << " | " << center("Salary Fund", 18)
         << endl;

    cout << string(15, '-') << "-+-" << string(15, '-') << "-+-" << string(18, '-') << endl;

    for (int i = 0; i < themeCount; i++) {
        cout << setw(15) << themes[i] << " | " << setw(15) << employeeCount[i] << " | " << setw(18) << salaryFund[i]
             << endl;
    }
    delete[] themes;
    delete[] employeeCount;
    delete[] salaryFund;
}
