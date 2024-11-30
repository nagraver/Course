#include "structures.h"

void clear_first(roster **begin) {
    if (!*begin) return;
    roster *temp = *begin;
    *begin = (*begin)->next;
    delete temp;
}