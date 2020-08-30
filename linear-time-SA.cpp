//
// Created by Shawn Jin on 20/8/20.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<bool> generate_s_list(const string &input) {
    vector<bool> ans(input.length());
    for (auto it = input.begin(); it != input.end() - 1; it++) {
        if (*it < *(it + 1)) {
            ans[it - input.begin()] = true;
        }
    }
    *(ans.end() - 1) = true;

    return ans;
}

vector<int> generate_distance(const vector<bool> &s_list, unsigned int size) {
    vector<int> distance(size);
    int last_s_index = -1;
    for (int i = 0; i < size; i++) {
        if (last_s_index == -1) {
            distance[i] = 0;
        } else {
            distance[i] = i - last_s_index;
        }
        if (s_list[i]) {
            last_s_index = i;
        }
    }
    return distance;
}

bool cmp_str(pair<char, int> a, pair<char, int> b) {
    return a.first < b.first;
}

vector<vector<int>> generate_sort_order(const string &input) {
    vector<pair<char, int>> in;
    for (int i = 1; i <= input.size(); i++) {
        in.emplace_back(input[i - 1], i);
    }
    sort(in.begin(), in.end(), cmp_str);

    vector<vector<int>> ans;
    vector<int> v;
    v.reserve(in.size());
    for (int i = 0; i < in.size(); i++) {
        v.push_back(in[i].second);
        if (i == in.size() - 1 || in[i].first != in[i + 1].first) {
            ans.push_back(v);
            v.clear();
        }
    }
    return ans;
}

vector<int> sort_substr(const vector<bool> &s_list, const string &input) {
    vector<pair<string, int>> sub;
    for (int i = 0; i < s_list.size(); i++) {
        if (s_list[i]) {
            for (int j = i + 1; j < s_list.size(); j++) {
                if (s_list[j]) {
                    sub.emplace_back(input.substr(i, j - i + 1), i);
                    break;
                }
            }
        }
    }

    sort(sub.begin(), sub.end(),
         [](const pair<string, int> &a, const pair<string, int> &b) { return a.first.compare(b.first) < 0; });

    vector<int> ans;
    ans.reserve(sub.size());
    for (const auto &it: sub) {
        ans.push_back(it.second + 1);
    }
    ans.insert(ans.begin(), input.size());

    return ans;
}

int main(int argc, char *argv[]) {
    string input;
    cin >> input;
    auto S_list = generate_s_list(input);
    auto distance = generate_distance(S_list, input.size());
    auto sort_order = generate_sort_order(input);
    for (auto i1: sort_order){
        for (auto i2: i1){
            cout << i2 << " ";
        }
        cout << endl;
    }
    auto S_sort = sort_substr(S_list, input);


}