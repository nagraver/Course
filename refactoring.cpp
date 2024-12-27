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
    cout << "Element added\n";
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
    cout << "Element added\n";
}

void addMany(roster **begin, NII content) {
    char choice;
    addLast(begin, enterContainer());
    choice = getChoice("Organize", "1 - Continue\n", "1");
    while (true) {
        if (choice == ESC) break;
        else if (choice == '1') addLast(begin, enterContainer());
        while (true) {
            addLast(begin, enterContainer());
            choice = getChoice("Organize", "1 - Continue\n", "1");
            if (choice == '1') addLast(begin, enterContainer());
            else if (choice == ESC) break;
        }
        break;
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

                char choice = getChoice("Delete selected", "1 - Delete\n", "1");
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
            while (temp->next && temp->next->info.salary < current->info.salary) {
                temp = temp->next;
            }
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
            while (temp->next && temp->next->info.salary > current->info.salary) {
                temp = temp->next;
            }
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

            while (true) {
                string prompt = "1 - Department\n2 - Name\n3 - Theme\n4 - Experience\n5 - Position\n6 - Salary\n";
                char choice = getChoice("Edit", prompt, "123456");
                system("clear");
                if (choice == ESC) break;
                else if (choice == '1') current->info.department = intInputCheck("Department");
                else if (choice == '2') current->info.name = nameInputCheck("Full name");
                else if (choice == '3') current->info.theme = intInputCheck("Theme");
                else if (choice == '4') current->info.experience = intInputCheck("Experience");
                else if (choice == '5') current->info.position = intInputCheck("Position");
                else if (choice == '6') current->info.salary = intInputCheck("Salary");
                system("clear");
                printRosterHeader();
                printRoster(current->info);
            }
            return;
        }
    }
    system("clear");
    cout << "ID not found\n";
}
