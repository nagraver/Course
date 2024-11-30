#include <fstream>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <ostream>
#include "structures.h"
#include "files.h"

using namespace std;

void save_roster(roster **begin) {
    ofstream file("NII", ios_base::binary);
    if (file.is_open()) {
        for (roster *current = *begin; current; current = current->next) {
            NII content = current->info;
            file.write((char *) &content, sizeof(NII));
        }
        cout << "Data successfully saved\n";
        file.close();
    } else {
        cerr << "Failed to open file" << std::endl;
        return;
    }
}

void load_roster(roster **begin) {
    ifstream file("NII", ios_base::binary);

    if (file.is_open()) {
        NII content;
        file.seekg(0, ios::beg);
        // while (*begin) clear_first(begin);
        // while (file.read((char *) &content, sizeof(NII))) add_last(begin, content);

        cout << "Data successfully loaded\n";
        file.close();
    } else {
        cerr << "Failed to open file" << std::endl;
        return;
    }
}