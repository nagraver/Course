#ifndef COURSE_ADDING_H
#define COURSE_ADDING_H

#include "structures.h"

NII enterContainer();

void addFirst(roster **begin, NII content);

void addLast(roster **begin, NII content);

void addMany(roster **begin, NII content);

void deleteFirst(roster **begin);

void deleteSelected(roster **begin);

void insertionSortIncrease(roster **begin);

void insertionSortDecrease(roster **begin);

void edit(roster **begin);

#endif
