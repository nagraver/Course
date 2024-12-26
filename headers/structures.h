#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>

using namespace std;

const char ESC = 27;
const char ENTER = 10;

struct NII {
    int id;
    int department;
    string name;
    int theme_number;
    int work_duration;
    int position;
    int salary;
};

struct roster {
    NII info;
    struct roster *next;
    struct roster *prev;
};

#endif
