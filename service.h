#define SERVICE_H
#ifdef SERVICE_H

#include "structures.h"

using namespace ::std;

char getch();

char getChoice(const string &prompt, const char *validChoices);

void fixId(roster **begin);

void printRosterHeader();

void printRoster(roster *current);

#endif
