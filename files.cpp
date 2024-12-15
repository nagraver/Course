#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>

#include "refactoring.h"
#include "structures.h"

using namespace std;

char getChoice(const string &prompt, const char *validChoices) {
    char choice;
    while (true) {
        cout << endl;
        cout << prompt << "Input: ";
        cin >> choice;

        bool isValid = false;
        for (int i = 0; i < sizeof(validChoices); i++) {
            if (choice == validChoices[i]) {
                isValid = true;
                break;
            }
        }

        if (isValid) break;
        cout << "Wrong choice, please try again.\n";
    }

    return choice;
}

void save_roster_bin(roster **begin) {
    ofstream file;
    file.open("NII", ios_base::binary);
    if (!file) {
        cerr << "Failed to open file" << endl;
        return;
    }

    for (roster *current = *begin; current; current = current->next) {
        NII content = current->info;
        file.write(reinterpret_cast<char *>(&content), sizeof(content));
    }

    cout << "Data successfully saved\n";
    file.close();
}

void save_roster_txt(roster **begin) {
    ofstream file;
    file.open("NII.txt");
    if (!file) {
        cerr << "Failed to open file" << endl;
        return;
    }

    for (roster *current = *begin; current; current = current->next) {
        file << current->info.department << "|";
        file << current->info.name << "|";
        file << current->info.theme_number << "|";
        file << current->info.work_duration << "|";
        file << current->info.position << "|";
        file << current->info.salary << "|";
        file << endl;
    }

    cout << "Data successfully saved\n";
    file.close();
}

void save_roster(roster **begin) {
    char choice = getChoice("Save to bin file - 1\nSave to txt file - 2\nCancel - q\n", "12q");
    if (choice == '1') save_roster_bin(begin);
    else if (choice == '2') save_roster_txt(begin);
    else if (choice == 'q') return;
}

void load_roster_bin(roster **begin) {
    char choice;
    ifstream file;
    file.open("NII", ios_base::binary);
    if (!file) {
        cerr << "Failed to open file" << endl;
        return;
    }

    choice = getChoice("Override data - 1\nAdd data - 2\nCancel - q\n", "12q");
    if (choice == '1')
        while (*begin) clear_first(begin);
    else if (choice == 'q') return;

    NII content;
    while (file.read(reinterpret_cast<char *>(&content), sizeof(content))) add_last(begin, content);

    cout << "Data successfully loaded\n";
    file.close();
}

void load_roster_txt(roster **begin) {
    char choice;
    ifstream file;
    file.open("NII.txt");
    if (!file) {
        cerr << "Failed to open file" << endl;
        return;
    }

    choice = getChoice("Override data - 1\nAdd data - 2\nCancel - q\n", "12q");
    if (choice == '1')
        while (*begin) clear_first(begin);
    else if (choice == 'q') return;

    string line;
    while (getline(file, line)) {
        NII content;
        size_t pos = 0;
        string temp;

        pos = line.find('|');
        temp = line.substr(0, pos);
        content.department = stoi(temp);
        line.erase(0, pos + 1);

        pos = line.find('|');
        content.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        temp = line.substr(0, pos);
        content.theme_number = stoi(temp);
        line.erase(0, pos + 1);

        pos = line.find('|');
        temp = line.substr(0, pos);
        content.work_duration = stoi(temp);
        line.erase(0, pos + 1);

        pos = line.find('|');
        temp = line.substr(0, pos);
        content.position = stoi(temp);
        line.erase(0, pos + 1);

        pos = line.find('|');
        temp = line.substr(0, pos);
        content.salary = stoi(temp);

        add_last(begin, content);
    }

    cout << "Data successfully loaded\n";
    file.close();
}

void load_roster(roster **begin) {
    char choice = getChoice("Load from bin file - 1\nLoad from txt file - 2\nCancel - q\n", "12q");
    if (choice == '1') load_roster_bin(begin);
    else if (choice == '2') load_roster_txt(begin);
    else if (choice == 'q') return;
}
