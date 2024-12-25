#define SERVICE_H
#ifdef SERVICE_H

#include "structures.h"

using namespace ::std;

string nameInputCheck(string text);

int intInputCheck(string text);

char getch();

char getChoice(const string &prompt, const char *validChoices);

void fixId(roster **begin);

void printRosterHeader();

void printRoster(NII info);

#endif
