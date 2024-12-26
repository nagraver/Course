#ifndef FILES_H
#define FILES_H

#include "structures.h"

using namespace ::std;

void load_roster_txt(roster **begin);

void load_roster_bin(roster **begin);

void save_roster_txt(roster **begin);

void save_roster_bin(roster **begin);

#endif  // FILES_H
