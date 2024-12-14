#include <iostream>
#include <fstream>
#include <string>

struct MyStruct {
    std::string name;
    std::string address;
    int age;

    // Метод для записи структуры в файл
    void writeToFile(std::ofstream &ofs) const {
        ofs << name << '\n' << address << '\n' << age << '\n';
    }

    // Метод для чтения структуры из файла
    void readFromFile(std::ifstream &ifs) {
        std::getline(ifs, name);
        std::getline(ifs, address);
        ifs >> age;
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Пропуск оставшихся данных в строке
    }
};
int main() {
    MyStruct person = {"John Doe", "123 Main St", 30};

    std::ofstream ofs("data.txt");
    if (!ofs) {
        std::cerr << "Could not open file for writing.\n";
        return 1;
    }

    person.writeToFile(ofs);
    ofs.close();
    return 0;
}