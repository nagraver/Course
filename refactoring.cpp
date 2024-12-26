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
    container.theme_number = intInputCheck("Theme number");
    system("clear");
    container.work_duration = intInputCheck("Work experience");
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
                cout << "Delete this (y/n)\n";
                char choice = getch();
                if (choice == 'y') {
                    if (current->prev) current->prev->next = current->next;
                    else *begin = current->next;
                    if (current->next) current->next->prev = current->prev;
                    delete current;
                    system("clear");
                    cout << "Element deleted.\n";
                    break;
                } else if (choice == 'n') {
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
    cout << "List been sorted\n";
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
    cout << "List been sorted\n";
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
            cout << "Choose column (d/n/p/s/t/w)\n";
            char choice = getch();
            system("clear");
            switch (choice) {
                case 'd':
                    current->info.department = intInputCheck("Department");
                    break;
                case 'n':
                    current->info.name = nameInputCheck("Full name");
                    break;
                case 'p':
                    current->info.position = intInputCheck("Position");
                    break;
                case 's':
                    current->info.salary = intInputCheck("Salary");
                    break;
                case 't':
                    current->info.theme_number = intInputCheck("Theme number");
                    break;
                case 'w':
                    current->info.work_duration = intInputCheck("Work experience");
                    break;
                default:
                    cout << "Wrong choice\n";
                    break;
            }
            system("clear");
            printRosterHeader();
            printRoster(current->info);
            return;
        }
    }
    system("clear");
    cout << "ID not found\n";
}
