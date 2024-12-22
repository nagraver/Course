#ifndef COURSE_ADDING_H
#define COURSE_ADDING_H

#include "structures.h"

NII enter_container();

void add_first(roster **begin, NII content);

void add_last(roster **begin, NII content);

void add_many(roster **begin);

void clear_first(roster **begin);

void clear_roster(roster **begin);

void edit(roster **begin);

#endif  // COURSE_ADDING_H
