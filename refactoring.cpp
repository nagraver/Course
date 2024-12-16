#include "iostream"
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
    temp->info.id = 0;
    temp->next = *begin;
    for (roster *current = *begin; current; current = current->next) current->info.id++;
    *begin = temp;
}

void add_last(roster **begin, NII content) {
    roster *temp = new roster();
    temp->info = content;
    temp->next = nullptr;
    temp->info.id = 0;
    if (!*begin) {
        *begin = temp;
    } else {
        roster *current = *begin;
        for (; current->next; current = current->next);
        current->next = temp;
        current->next->info.id = current->info.id + 1;
    }
}

void add_many(roster **begin) {
    char value;
    while (true) {
        add_last(begin, enter_container());
        cout << "Continue organizing the list: 1" << endl;
        cout << "Finish organizing the list: Any other key" << endl;
        cin >> value;
        if (value != '1') return;
    }
}

void clear_first(roster **begin) {
    if (!*begin) return;
    roster *temp = *begin;
    for (roster *current = *begin; current; current = current->next) current->info.id--;
    *begin = (*begin)->next;
    delete temp;
}
