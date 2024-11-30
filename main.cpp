#include <iostream>
#include <iomanip>
#include <string>

#include "files.h"
#include "structures.h"
#include "adding.h"
#include "removing.h"

using namespace std;

void print_roster(roster **begin);


int main() {
    char value;
    roster *begin = nullptr;

    while (true) {
        cout << "1) Add to the beginning of the list\n";
        cout << "2) Add to the end of the list\n";
        cout << "3) Organize the list\n";
        cout << "4) Display data\n";
        cout << "5) Delete the first element\n";
        cout << "6) Save data\n";
        cout << "7) Load data\n";
        cout << "0) Exit\n";

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
            case '5':
                clear_first(&begin);
                cout << "First element deleted\n";
                break;
            case '6':
                save_roster(&begin);
                break;
            case '7':
                load_roster(&begin);
                break;
            case '0':
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
    cout << left << setw(12) << "Department" << " | "
         << setw(15) << "Full Name" << " | "
         << setw(10) << "Position" << " | "
         << setw(10) << "Salary" << " | "
         << setw(15) << "Theme Number" << " | "
         << setw(18) << "Work Experience" << endl;

    cout << string(12, '-') << "-+-"
         << string(15, '-') << "-+-"
         << string(10, '-') << "-+-"
         << string(10, '-') << "-+-"
         << string(15, '-') << "-+-"
         << string(18, '-') << endl;

    for (roster *current = *begin; current; current = current->next) {
        cout << setw(12) << current->info.department << " | "
             << setw(15) << current->info.name << " | "
             << setw(10) << current->info.position << " | "
             << setw(10) << current->info.salary << " | "
             << setw(15) << current->info.theme_number << " | "
             << setw(18) << current->info.work_duration << endl;
    }
}
