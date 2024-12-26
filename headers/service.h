#define SERVICE_H
#ifdef SERVICE_H

#include "structures.h"

using namespace ::std;

string nameInputCheck(string text);

int intInputCheck(string text);

char getch();

char getChoice(string prompt, string validChoices);

void fixId(roster **begin);

string center(string text, int width);

void printRosterHeader();

void printRoster(NII info);

#endif
