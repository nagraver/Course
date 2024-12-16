#include <iomanip>
#include <iostream>

#include "structures.h"

using namespace ::std;

char getChoice(const string &prompt, const char *validChoices) {
    char choice;
    while (true) {
        cout << endl;
        cout << prompt << "Input: ";
        cin >> choice;

        bool isValid = false;
        for (int i = 0; i < sizeof(validChoices); i++) {
            if (choice == validChoices[i]) {
                isValid = true;
                break;
            }
        }

        if (isValid) break;
        cout << "Wrong choice, please try again.\n";
    }

    return choice;
}

void fixId(roster **begin) {
    roster *current = *begin;
    int _id = 0;
    for (; current; current = current->next) {
        current->info.id = _id;
        _id++;
    }
}

string center(const string &text, int width) {
    if (width <= text.length()) return text;

    int left_padding = (width - text.length()) / 2;
    int right_padding = width - text.length() - left_padding;

    return string(left_padding, ' ') + text + string(right_padding, ' ');
}

void printRosterHeader() {
    cout << center("id", 4) << " | " << setw(12) << center("Department", 12) << " | " << setw(15)
         << center("Full Name", 15) << " | " << setw(10) << center("Position", 10) << " | " << setw(10)
         << center("Salary", 10) << " | " << setw(15) << center("Theme Number", 15) << " | " << setw(18)
         << center("Work Experience", 18) << endl;

    cout << string(4, '-') << "-+-" << string(12, '-') << "-+-" << string(15, '-') << "-+-" << string(10, '-') << "-+-"
         << string(10, '-') << "-+-" << string(15, '-') << "-+-" << string(18, '-') << endl;
}

void printRoster(roster *current) {
    cout << left << setw(4) << current->info.id << " | " << setw(12) << current->info.department << " | " << setw(15)
         << current->info.name << " | " << setw(10) << current->info.position << " | " << setw(10)
         << current->info.salary << " | " << setw(15) << current->info.theme_number << " | " << setw(18)
         << current->info.work_duration << endl;
}
