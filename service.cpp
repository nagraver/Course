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
