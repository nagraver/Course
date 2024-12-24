#include <cmath>
#include <cstdlib>
#include <ostream>
#include <stdexcept>

#include "iostream"
#include "service.h"
#include "structures.h"

using namespace std;

NII enter_container() {
    NII container;

    cout << "Department: ";
    cin >> container.department;

    cout << "Full Name: ";
    cin.ignore();
    getline(cin, container.name);

    cout << "Position: ";
    cin >> container.position;

    cout << "Salary: ";
    cin >> container.salary;

    cout << "Theme number: ";
    cin >> container.theme_number;

    cout << "Work experience: ";
    cin >> container.work_duration;

    return container;
}

void add_first(roster **begin, NII content) {
    roster *temp = new roster();
    temp->info = content;
    temp->next = *begin;
    *begin = temp;
    fixId(begin);
}

void add_last(roster **begin, NII content) {
    roster *temp = new roster();
    temp->info = content;
    temp->next = nullptr;
    if (!*begin) *begin = temp;
    else {
        roster *current = *begin;
        for (; current->next; current = current->next);
        current->next = temp;
    }
    fixId(begin);
}

void clear_first(roster **begin) {
    if (*begin == nullptr) {
        cout << "The list is empty.\n";
        return;
    }

    roster *temp = *begin;
    for (roster *current = *begin; current; current = current->next) current->info.id--;
    *begin = (*begin)->next;
    delete temp;
    fixId(begin);
    cout << "First element deleted\n";
}

void edit(roster **begin) {
    if (*begin == nullptr) {
        cout << "The list is empty.\n";
        return;
    }
    int _id;

    while (true) {
        cout << "Chooese ID to edit\n";
        try {
            cin >> _id;
            if (cin.fail()) throw invalid_argument("Input must be integer\n");
            break;
        } catch (exception &e) {
            system("clear");
            cin.clear();
            cin.ignore();
            cerr << e.what();
        }
    }
    for (roster *current = *begin; current; current = current->next) {
        if (current->info.id == _id) {
            printRosterHeader();
            printRoster(current->info);
            cout << "Enter new values\n";
            NII content = enter_container();
            system("clear");
            content.id = _id;
            current->info = content;
            printRosterHeader();
            printRoster(content);
            return;
        }
    }
    system("clear");
    cout << "ID not found\n";
}
