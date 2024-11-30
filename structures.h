#ifndef STRUCTURES_H
#define STRUCTURES_H

using namespace std;

struct NII {
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

#endif //STRUCTURES_H
