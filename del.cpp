#include "iostream"

using namespace std;

int main() {
    string one, two, three;
    int first;

    cout << "one:";
    getline(cin, one);
    cout << "first:";
    cin >> first;
    cout << "two:";
    getline(cin, two);
    cout << "three:";
    getline(cin, three);

    cout << one << endl;
    cout << first << endl;
    cout << two << endl;
    cout << three << endl;
}