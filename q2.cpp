//
// Created by Shawn Jin on 25/8/20.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int startsWith(const string& a, const string& b) {
    if (a.find(b)==0){
        return b.size();
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    string input = argv[1];
    vector<int> g_rule(input.size());

    g_rule[input.size() - 1] = input.size() - 2;

    unsigned int start_index = input.size();

    for (int i = input.size() - 2; i >= 0; i--) {
        auto sub = input.substr(i+1, input.size() - i);
        auto start_index_size = startsWith(input, sub);
        if (start_index_size){
            start_index = input.size() - start_index_size;
        }
        g_rule[i] = i - start_index;
    }

    cout << g_rule[0];
    for (int i=1;i<input.size();i++){
        cout << " " << g_rule[i];
    }
    cout << endl;

}
