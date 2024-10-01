#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

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

NII enter_container();

void add_first(roster **begin, NII content);

void add_last(roster **begin, NII content);

void add_many(roster **begin);

void print_roster(roster **begin);

void clear_first(roster **begin);

void save_roster(roster **begin);

void load_roster(roster **begin);

int main() {
    char value;
    roster *begin = nullptr;

    while (true) {
        cout << "1) Add to the beginning of the list\n";
        cout << "2) Add to the end of the list\n";
        cout << "3) Organize the list\n";
        cout << "4) Display data\n";
        cout << "5) Delete the first element\n";
        cout << "6) Save data\n";
        cout << "7) Load data\n";
        cout << "0) Exit\n";

        cin >> value;

        switch (value) {
            case '1':
                add_first(&begin, enter_container());
                cout << "Element added to the beginning\n";
                break;
            case '2':
                add_last(&begin, enter_container());
                cout << "Element added to the end\n";
                break;
            case '3':
                add_many(&begin);
                break;
            case '4':
                print_roster(&begin);
                break;
            case '5':
                clear_first(&begin);
                cout << "First element deleted\n";
                break;
            case '6':
                save_roster(&begin);
                break;
            case '7':
                load_roster(&begin);
                break;
            case '0':
                while (begin) clear_first(&begin);
                cout << "List cleared\n";
                return 0;
            default:
                cout << "Error\n";
                break;
        }
    }
}

NII enter_container() {
    NII container;
    cout << "Department: ";
    cin >> container.department;

    cout << "Full Name: ";
    cin.ignore();
    getline(cin, container.name);

    cout << "Position: ";
    cin >> container.position;

    cout << "Salary: ";
    cin >> container.salary;

    cout << "Theme number: ";
    cin >> container.theme_number;

    cout << "Work experience: ";
    cin >> container.work_duration;

    return container;
}

void add_first(roster **begin, NII content) {
    roster *temp = new roster();
    temp->info = content;
    temp->next = *begin;
    *begin = temp;
}

void add_last(roster **begin, NII content) {
    roster *temp = new roster();
    temp->info = content;
    temp->next = nullptr;

    if (!*begin) {
        *begin = temp;
    } else {
        roster *current = *begin;
        while (current->next) current = current->next;
        current->next = temp;
    }
}

void add_many(roster **begin) {
    char value;
    while (true) {
        add_last(begin, enter_container());
        cout << "Continue organizing the list: 1" << endl;
        cout << "Finish organizing the list: Any other key" << endl;
        cin >> value;
        if (value != '1') return;
    }
}

void print_roster(roster **begin) {
    cout << left << setw(12) << "Department" << " | "
         << setw(15) << "Full Name" << " | "
         << setw(10) << "Position" << " | "
         << setw(10) << "Salary" << " | "
         << setw(15) << "Theme Number" << " | "
         << setw(18) << "Work Experience" << endl;

    cout << string(12, '-') << "-+-"
         << string(15, '-') << "-+-"
         << string(10, '-') << "-+-"
         << string(10, '-') << "-+-"
         << string(15, '-') << "-+-"
         << string(18, '-') << endl;

    // Print the data rows
    for (roster *current = *begin; current; current = current->next) {
        cout << setw(12) << current->info.department << " | "
             << setw(15) << current->info.name << " | "
             << setw(10) << current->info.position << " | "
             << setw(10) << current->info.salary << " | "
             << setw(15) << current->info.theme_number << " | "
             << setw(18) << current->info.work_duration << endl;
    }
}


void clear_first(roster **begin) {
    if (!*begin) return;
    roster *temp = *begin;
    *begin = (*begin)->next;
    delete temp;
}

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
        std::cerr << "Failed to open file" << std::endl;
        return;
    }
}

void load_roster(roster **begin) {
    ifstream file("NII", ios_base::binary);
    if (!file) {
        std::cerr << "Failed to open file" << std::endl;
        return;
    }

    NII content;
    file.seekg(0, ios::beg);
    while (*begin) clear_first(begin);
    while (file.read((char *) &content, sizeof(NII))) add_last(begin, content);

    cout << "Data successfully loaded\n";
    file.close();
}
