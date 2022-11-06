#include <iostream>
#include <iterator>
#include <cstring>
#include <vector>
using namespace std;

void print(vector<int> &);

int main(int argc, char *argv[]) {
    vector<int> v = {1, 2, 3};
    print(v);
    return 0;
}

int sum(initializer_list<int> li) {
    int sum = 0;
    for (auto elem: li) {
        sum += elem;
    }
    return sum;
}

void print(vector<int> &a) {
    for (auto &i: a) {
        i = 0;
    }

    for (auto i: a) {
        cout << i << endl;
    }
}