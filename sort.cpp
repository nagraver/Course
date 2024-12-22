#include "service.h"
#include "structures.h"

using namespace ::std;

void insertionSortIncrease(roster **begin) {
    if (begin == nullptr) {

        cout << "The list is empty.\n";
        return;
    }
    roster *sorted = nullptr;
    roster *current = *begin;

    while (current) {
        roster *next = current->next;

        // Вставляем текущий элемент в отсортированный список
        if (!sorted || sorted->info.salary >= current->info.salary) {
            current->next = sorted;
            if (sorted) sorted->prev = current;
            current->prev = nullptr;
            sorted = current;
        } else {
            roster *temp = sorted;
            // Найти место для вставки
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
}

void insertionSortDecrease(roster **begin) {
    if (begin == nullptr) {

        cout << "The list is empty.\n";
        return;
    }
    roster *sorted = nullptr;
    roster *current = *begin;

    while (current) {
        roster *next = current->next;

        // Вставляем текущий элемент в отсортированный список
        if (!sorted || sorted->info.salary <= current->info.salary) {
            current->next = sorted;
            if (sorted) sorted->prev = current;
            current->prev = nullptr;
            sorted = current;
        } else {
            roster *temp = sorted;
            // Ищем место для вставки
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
}

void insertionSort(roster **begin) {
    char choice = getChoice("Increasing sord - 1\nDecreasing sort - 2\nCancel - q\n", "12q");
    if (choice == '1') insertionSortIncrease(begin);
    else if (choice == '2') insertionSortDecrease(begin);
    else if (choice == 'q') return;
}
