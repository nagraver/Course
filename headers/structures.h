#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>

struct NII {
    int id;
    int department;
    std::string name;
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

#endif //STRUCTURES_H
