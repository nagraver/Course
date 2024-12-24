#include <iostream>

using namespace ::std;

void func(int *value) {
    *value += 1;
}

int main() {
    int value = 5;
    func(&value);
    cout << value;
    return 0;
}
