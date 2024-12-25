#ifndef COURSE_ADDING_H
#define COURSE_ADDING_H

#include "structures.h"

NII enter_container();

void addFirst(roster **begin, NII content);

void addLast(roster **begin, NII content);

void clearFirst(roster **begin);

void clearSelected(roster **begin);

void insertionSort(roster **begin);

void edit(roster **begin);

#endif
