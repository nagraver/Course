#include "headers/refactoring.h"

#include <cstdlib>
#include <iostream>
#include <ostream>

#include "./headers/service.h"
#include "./headers/structures.h"

using namespace std;

NII enterContainer() {
    NII container;
    container.department = intInputCheck("Department");
    system("clear");
    container.name = nameInputCheck("Full Name");
    system("clear");
    container.position = intInputCheck("Position");
    system("clear");
    container.salary = intInputCheck("Salary");
    system("clear");
    container.theme = intInputCheck("Theme number");
    system("clear");
    container.experience = intInputCheck("Work experience");
    system("clear");
    return container;
}

void addFirst(roster **begin, NII content) {
    roster *temp = new roster();
    temp->info = content;
    temp->next = *begin;
    if (*begin != nullptr) (*begin)->prev = temp;
    *begin = temp;
    fixId(begin);
    printRosterHeader();
    printRoster(content);
}

void addLast(roster **begin, NII content) {
    roster *temp = new roster();
    temp->info = content;
    temp->next = nullptr;
    if (!*begin) *begin = temp;
    else {
        roster *current = *begin;
        for (; current->next; current = current->next);
        current->next = temp;
        temp->prev = current;
    }
    fixId(begin);
    printRosterHeader();
    printRoster(temp->info);
}

void addMany(roster **begin) {
    char choice;
    while (true) {
        addLast(begin, enterContainer());
        choice = getChoice("1 - Continue\n", "1");
        if (choice == '1') addLast(begin, enterContainer());
        else if (choice == ESC) break;
    }
}

void deleteFirst(roster **begin) {
    if (*begin == nullptr) {
        cout << "List is empty.\n";
        return;
    }
    roster *temp = *begin;
    for (roster *current = *begin; current; current = current->next) current->info.id--;
    *begin = (*begin)->next;
    delete temp;
    fixId(begin);
    system("clear");
    cout << "First element deleted\n";
}

void deleteSelected(roster **begin) {
    if (*begin == nullptr) {
        cout << "List is empty.\n";
        return;
    }
    int _id = intInputCheck("Choose ID to delete");

    for (roster *current = *begin; current; current = current->next) {
        if (current->info.id == _id) {
            while (true) {
                system("clear");
                printRosterHeader();
                printRoster(current->info);

                char choice = getChoice("1 - Delete\n", "1");
                if (choice == '1') {
                    if (current->prev) current->prev->next = current->next;
                    else *begin = current->next;
                    if (current->next) current->next->prev = current->prev;
                    delete current;
                    system("clear");
                    cout << "Element deleted.\n";
                    break;
                } else if (choice == ESC) {
                    system("clear");
                    cout << "Canceled\n";
                    break;
                }
            }
            fixId(begin);
            return;
        }
    }
    cout << "ID not found\n";
}

void insertionSortIncrease(roster **begin) {
    if (*begin == nullptr) {
        cout << "List is empty.\n";
        return;
    }
    roster *sorted = nullptr;
    roster *current = *begin;

    while (current) {
        roster *next = current->next;

        if (!sorted || sorted->info.salary >= current->info.salary) {
            current->next = sorted;
            if (sorted) sorted->prev = current;
            current->prev = nullptr;
            sorted = current;
        } else {
            roster *temp = sorted;
            while (temp->next && temp->next->info.salary < current->info.salary) { temp = temp->next; }
            current->next = temp->next;
            if (temp->next) temp->next->prev = current;
            temp->next = current;
            current->prev = temp;
        }
        current = next;
    }
    *begin = sorted;
    fixId(begin);
    system("clear");
    cout << "Sorted\n";
}

void insertionSortDecrease(roster **begin) {
    if (*begin == nullptr) {
        cout << "List is empty.\n";
        return;
    }
    roster *sorted = nullptr;
    roster *current = *begin;

    while (current) {
        roster *next = current->next;

        if (!sorted || sorted->info.salary <= current->info.salary) {
            current->next = sorted;
            if (sorted) sorted->prev = current;
            current->prev = nullptr;
            sorted = current;
        } else {
            roster *temp = sorted;
            while (temp->next && temp->next->info.salary > current->info.salary) { temp = temp->next; }
            current->next = temp->next;
            if (temp->next) temp->next->prev = current;
            temp->next = current;
            current->prev = temp;
        }
        current = next;
    }
    *begin = sorted;
    fixId(begin);
    system("clear");
    cout << "Sorted\n";
}

void edit(roster **begin) {
    if (*begin == nullptr) {
        cout << "List is empty.\n";
        return;
    }
    int _id = intInputCheck("Choose ID to edit");

    for (roster *current = *begin; current; current = current->next) {
        if (current->info.id == _id) {
            system("clear");
            printRosterHeader();
            printRoster(current->info);
            char choice =
                getChoice("1 - Department\n2 - Name\n3 - Theme\n4 - Experience\n5 - Position\n6 - Salary\n", "123456");
            system("clear");
            while (true) {
                switch (choice) {
                    system("clear");
                    case '1':
                        current->info.department = intInputCheck("Department");
                        cout << "Edited\n";
                        break;
                    case '2':
                        current->info.name = nameInputCheck("Full name");
                        cout << "Edited\n";
                        break;
                    case '3':
                        current->info.theme = intInputCheck("Theme");
                        cout << "Edited\n";
                        break;
                    case '4':
                        current->info.experience = intInputCheck("Experience");
                        cout << "Edited\n";
                        break;
                    case '5':
                        current->info.position = intInputCheck("Position");
                        cout << "Edited\n";
                        break;
                    case '6':
                        current->info.salary = intInputCheck("Salary");
                        cout << "Edited\n";
                        break;
                    case ESC:
                        cout << "Canceled\n";
                        break;
                    default:
                        cout << "Wrong choice\n";
                        continue;
                }
                break;
            }
            return;
        }
    }
    system("clear");
    cout << "ID not found\n";
}
