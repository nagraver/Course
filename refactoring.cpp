#include "iostream"
#include "service.h"
#include "structures.h"

using namespace std;

NII enter_container() {
    system("clear");
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
    system("clear");
    roster *temp = new roster();
    temp->info = content;
    temp->info.id = 0;
    temp->next = *begin;
    *begin = temp;
    fixId(begin);
}

void add_last(roster **begin, NII content) {
    system("clear");
    roster *temp = new roster();
    temp->info = content;
    temp->next = nullptr;
    if (!*begin) {
        *begin = temp;
    } else {
        roster *current = *begin;
        for (; current->next; current = current->next);
        current->next = temp;
    }
    fixId(begin);
}

void add_many(roster **begin) {
    system("clear");
    char value;
    while (true) {
        add_last(begin, enter_container());
        cout << "Continue organizing the list: 1\n";
        cout << "Finish organizing the list: Any other key\n";
        value = getch();
        if (value != '1') return;
    }
}

void clear_first(roster **begin) {
    system("clear");
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

// void clear_roster(roster **begin) {
//     system("clear");
//     if (*begin == nullptr) {
//         cout << "The list is empty.\n";
//         return;
//     }
//     for (roster *current = *begin; current; current = current->next) clear_first(begin);
// }

void edit(roster **begin) {
    system("clear");
    if (*begin == nullptr) {
        cout << "The list is empty.\n";
        return;
    }
    char _id;
    cout << "Enter id\n";
    cin >> _id;
    for (roster *current = *begin; current; current = current->next) {
        if (static_cast<char>(current->info.id) == _id) {
            current->info = enter_container();
            fixId(begin);
            return;
            ;
        }
    }
    cout << "ID not found\n";
}
