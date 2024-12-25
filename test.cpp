#include <iostream>

using namespace std;

void func(int *value) { *value += 1; }

int main() {
    int z ,v;
    cout << "Department: ";
    cin >> z;
    // cin >> v;
    string zov;
    cout << "Full Name: ";
    getline(cin, zov);
    cout << zov << " " << z;
}
