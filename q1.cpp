//
// Created by Shawn Jin on 25/8/20.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string pop_and_insert(string input) {
    char last = *(input.end() - 1);
    input.pop_back();
    input.insert(input.begin(), last);
    return input;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }
    string input = argv[1];
    vector<string> vs;
    vs.push_back(input);

    for (int i = 0; i < input.size() - 1; i++) {
        input = pop_and_insert(input);
        vs.push_back(input);
    }

    sort(vs.begin(), vs.end());

    string ans;

    for (auto it: vs) {
        ans.push_back(*(it.end() - 1));
    }

    cout << ans << endl;

}

