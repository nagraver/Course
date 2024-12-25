#include <termios.h>
#include <unistd.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include "./headers/structures.h"

using namespace std;

string nameInputCheck(string text) {
    string value;
    while (true) {
        cout << text + ": ";
        getline(cin, value);
        bool flag = false;
        for (int i = 0; i < value.length(); i++) {
            if (isdigit(value[i])) {
                flag = true;
                break;
            }
        }
        if (flag) {
            system("clear");
            cout << "Name can not contains digits\n";
        } else break;
    }
    return value;
}

int intInputCheck(string text) {
    int value;
    while (true) {
        cout << text + ": ";
        cin >> value;
        if (cin.fail()) {
            system("clear");
            cout << "Input must be integer\n";
            cin.clear();
            cin.ignore();
            continue;
        }
        break;
    }
    cin.ignore();
    return value;
}

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0) { perror("tcsetattr()"); }
    old.c_lflag &= ~ICANON;  // Отключить канонический режим
    old.c_lflag &= ~ECHO;    // Отключить эхо
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) { perror("tcsetattr ICANON"); }
    if (read(0, &buf, 1) < 0) { perror("read()"); }
    old.c_lflag |= ICANON;  // Включить канонический режим обратно
    old.c_lflag |= ECHO;    // Включить эхо обратно
    if (tcsetattr(0, TCSADRAIN, &old) < 0) { perror("tcsetattr ~ICANON"); }
    return buf;
}

char getChoice(const string &prompt, const char *validChoices) {
    char choice;
    while (true) {
        cout << prompt;
        choice = getch();

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

void fixId(roster **begin) {
    int _id = 0;
    for (roster *current = *begin; current; current = current->next) {
        current->info.id = _id;
        _id++;
    }
}

string center(const string &text, int width) {
    if (width <= text.length()) return text;

    int left_padding = (width - text.length()) / 2;
    int right_padding = width - text.length() - left_padding;

    return string(left_padding, ' ') + text + string(right_padding, ' ');
}

void printRosterHeader() {
    cout << center("id", 4) << " | " << setw(12) << center("Department", 12) << " | " << setw(15)
         << center("Full Name", 15) << " | " << setw(10) << center("Position", 10) << " | " << setw(10)
         << center("Salary", 10) << " | " << setw(15) << center("Theme Number", 15) << " | " << setw(18)
         << center("Work Experience", 18) << endl;

    cout << string(4, '-') << "-+-" << string(12, '-') << "-+-" << string(15, '-') << "-+-" << string(10, '-') << "-+-"
         << string(10, '-') << "-+-" << string(15, '-') << "-+-" << string(18, '-') << endl;
}

void printRoster(NII info) {
    cout << left << setw(4) << info.id << " | " << setw(12) << info.department << " | " << setw(15) << info.name
         << " | " << setw(10) << info.position << " | " << setw(10) << info.salary << " | " << setw(15)
         << info.theme_number << " | " << setw(18) << info.work_duration << endl;
}
