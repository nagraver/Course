#include <termios.h>
#include <unistd.h>

#include <iomanip>
#include <iostream>

#include "structures.h"

using namespace ::std;

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
    roster *current = *begin;
    int _id = 0;
    for (; current; current = current->next) {
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

void printRoster(roster *current) {
    cout << left << setw(4) << current->info.id << " | " << setw(12) << current->info.department << " | " << setw(15)
         << current->info.name << " | " << setw(10) << current->info.position << " | " << setw(10)
         << current->info.salary << " | " << setw(15) << current->info.theme_number << " | " << setw(18)
         << current->info.work_duration << endl;
}
