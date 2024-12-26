#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "./headers/refactoring.h"
#include "./headers/service.h"
#include "./headers/structures.h"

using namespace std;

void save_roster_bin(roster **begin) {
    ofstream file;
    string fileName;
    cout << "Saving to bin file\nEnter name for bin file\nInput: ";
    getline(cin, fileName);
    system("clear");

    file.open("./files/" + fileName, ios_base::binary);
    if (!file) {
        cerr << "Failed to open file\n";
        return;
    }

    for (roster *current = *begin; current; current = current->next) {
        NII content = current->info;
        file.write(reinterpret_cast<char *>(&content), sizeof(content));
    }

    system("clear");
    cout << "Data successfully saved\n";
    file.close();
}

void save_roster_txt(roster **begin) {
    ofstream file;
    string fileName;
    cout << "Saving to txt file\nEnter name for txt file\nInput: ";
    getline(cin, fileName);
    system("clear");

    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".txt") file.open("./files/" + fileName);
    else file.open("./files/" + fileName + ".txt");
    if (!file) {
        cerr << "Failed to open file\n";
        return;
    }

    for (roster *current = *begin; current; current = current->next) {
        file << current->info.id << "|";
        file << current->info.department << "|";
        file << current->info.name << "|";
        file << current->info.theme << "|";
        file << current->info.experience << "|";
        file << current->info.position << "|";
        file << current->info.salary << "|";
        file << endl;
    }

    system("clear");
    cout << "Data successfully saved\n";
    file.close();
}

void load_roster_bin(roster **begin) {
    char choice;
    ifstream file;
    string fileName;
    cout << "Loading from bin file\nEnter name for bin file\nInput: ";
    getline(cin, fileName);
    system("clear");

    file.open("./files/" + fileName, ios_base::binary);
    if (!file) {
        cerr << "Failed to open file\n";
        return;
    }

    choice = getChoice("1 - Override data\n2 - Add data\n", "12");
    if (choice == '1')
        while (*begin) deleteFirst(begin);
    else if (choice == ESC) return;

    NII content;
    while (file.read(reinterpret_cast<char *>(&content), sizeof(content))) addLast(begin, content);

    system("clear");
    if (choice == '1') cout << "Data successfully overrided\n";
    else cout << "Data successfully added\n";
    file.close();
}

void load_roster_txt(roster **begin) {
    char choice;
    ifstream file;
    string fileName;
    cout << "Loading from txt file\nEnter name for txt file\nInput: ";
    getline(cin, fileName);
    system("clear");

    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".txt") file.open("./files/" + fileName);
    else file.open("./files/" + fileName + ".txt");
    if (!file) {
        cerr << "Failed to open file\n";
        return;
    }

    choice = getChoice("1 - Override data\n2 - Add data\n", "12");
    if (choice == '1')
        while (*begin) deleteFirst(begin);
    else if (choice == ESC) return;

    string line;
    while (getline(file, line)) {
        NII content;
        size_t pos = 0;
        string temp;

        pos = line.find('|');
        temp = line.substr(0, pos);
        content.id = stoi(temp);
        line.erase(0, pos + 1);

        pos = line.find('|');
        temp = line.substr(0, pos);
        content.department = stoi(temp);
        line.erase(0, pos + 1);

        pos = line.find('|');
        content.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        temp = line.substr(0, pos);
        content.theme = stoi(temp);
        line.erase(0, pos + 1);

        pos = line.find('|');
        temp = line.substr(0, pos);
        content.experience = stoi(temp);
        line.erase(0, pos + 1);

        pos = line.find('|');
        temp = line.substr(0, pos);
        content.position = stoi(temp);
        line.erase(0, pos + 1);

        pos = line.find('|');
        temp = line.substr(0, pos);
        content.salary = stoi(temp);

        addLast(begin, content);
    }

    system("clear");
    if (choice == '1') cout << "Data successfully overrided\n";
    else cout << "Data successfully added\n";
    file.close();
}
