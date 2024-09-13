#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct data {
    string name;
    float cost;
    float rating;
};

struct roster {
    data info;
    struct roster *next;
};

data enter_container();

void add_first(roster **begin, data content);

void add_last(roster **begin, data content);

void add_many(roster **begin);

void print_roster(roster **begin);

void clear_first(roster **begin);

void save_roster(roster **begin);

void load_roster(roster **begin);

void clear() {
    system("clear");
}

int main() {
    char value;
    roster *begin = nullptr;

    while (true) {

        cout << "1) Занести в начало списка\n";
        cout << "2) Занести в конец списка\n";
        cout << "3) Организовать список\n";
        cout << "4) Вывести данные\n";
        cout << "5) Удалить первый элемент\n";
        cout << "6) Сохранить данные\n";
        cout << "7) Загрузить данные\n";
        cout << "0) Завершить работу\n";

        cin >> value;

        switch (value) {
            case '1':
                add_first(&begin, enter_container());
                cout << "Элемент добавлен в начало\n";
                break;
            case '2':
                add_last(&begin, enter_container());
                cout << "Элемент добавлен в конец\n";
                break;
            case '3':
                add_many(&begin);
                break;
            case '4':
                clear();
                print_roster(&begin);
                break;
            case '5':
                clear_first(&begin);
                cout << "Первый элемент удален\n";
                break;
            case '6':
                save_roster(&begin);
                break;
            case '7':
                load_roster(&begin);
                break;
            case '0':
                while (begin) clear_first(&begin);
                cout << "Список очищен\n";
                return 0;
            default:
                cout << "Ошибка\n";
                break;
        }
    }
}


data enter_container() {
    data container;
    cout << "Введите наименование (не более 16 символов): ";
    cin >> setw(17) >> container.name;
    cout << "Введите цену: ";
    cin >> container.cost;
    cout << "Введите рейтинг: ";
    cin >> container.rating;
    return container;
}


void add_first(roster **begin, data content) {
    roster *temp = new roster();
    temp->info = content;
    temp->next = *begin;
    *begin = temp;
}


void add_last(roster **begin, data content) {
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
        cout << "Продолжить организацию списка: 1" << endl;
        cout << "Закончить организацию списка: Любая кнопка" << endl;
        cin >> value;
        if (value != '1') return;
    }
}

void print_roster(roster **begin) {
    cout << "|       Name       |       Price      |      Rating      |" << endl;
    for (roster *current = *begin; current; current = current->next) {
        cout << "| " << setw(16) << current->info.name
             << " | " << setw(16) << fixed << setprecision(2) << current->info.cost
             << " | " << setw(16) << fixed << setprecision(2) << current->info.rating << " |" << endl;
    }
}


void clear_first(roster **begin) {
    if (!*begin) return;
    roster *temp = *begin;
    *begin = (*begin)->next;
    delete temp;
}

void save_roster(roster **begin) {
    ofstream file("data", ios_base::binary);
    if (!file) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }

    for (roster *current = *begin; current; current = current->next) {
        data content = current->info;
        file.write((char *) &content, sizeof(data));
    }

    cout << "Данные успешно сохранены\n";
    file.close();
}

void load_roster(roster **begin) {
    ifstream file("data", ios_base::binary);
    if (!file) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }

    file.seekg(0, std::ios::beg);

    data content;
    while (*begin) clear_first(begin);
    while (file.read((char *) &content, sizeof(data))) add_last(begin, content);

    cout << "Данные успешно загружены\n";
    file.close();
}



