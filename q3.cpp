//
// Created by Shawn Jin on 25/8/20.
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
            sort(v.begin(), v.end());
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

void output(const vector<vector<int>> &ans) {
    for (auto it = ans.begin(); it != ans.end(); it++) {
        if (it == ans.begin()) printf("[");
        else printf(" [");
        for (int i = 0; i < (*it).size(); i++) {
            printf("%i", (*it)[i]);
            if (i != (*it).size() - 1) {
                printf(" ");
            }
        }
        printf("]");
    }
    printf("\n");
}

vector<vector<int>> get_list(int d, const vector<int> &distances, const vector<vector<int>> &sort_order) {
    vector<vector<int>> ans(sort_order);
    vector<int> idxs;
    for (int i = 0; i < distances.size(); i++) {
        if (distances[i] == d) idxs.push_back(i + 1);
    }
    for (auto &it:ans) {
        it.erase(remove_if(it.begin(), it.end(),
                           [idxs](int k) { return find(idxs.begin(), idxs.end(), k) == idxs.end(); }), it.end());

        transform(it.begin(), it.end(), it.begin(), [d](int k) { return k - d; });
    }
    ans.erase(remove_if(ans.begin(), ans.end(), [](auto k) { return k.size() == 0; }), ans.end());

    return ans;

}

vector<vector<int>> split_s(const vector<vector<int>> &raw, const vector<vector<int>> &slist) {
    vector<vector<int>> ans;
    for (const auto &it_raw: raw) {
        if (it_raw.size() == 1) {
            vector<int> r(it_raw);
            ans.push_back(r);
            continue;
        }
        vector<int> it_raw_copy(it_raw);
        for (const auto &s:slist) {
            vector<int> tmp;
            set_intersection(it_raw.begin(), it_raw.end(), s.begin(), s.end(), back_inserter(tmp));
            if (!tmp.empty()) ans.push_back(tmp);

            it_raw_copy.erase(remove_if(it_raw_copy.begin(), it_raw_copy.end(),
                                        [tmp](int k) { return find(tmp.begin(), tmp.end(), k) != tmp.end(); }),
                              it_raw_copy.end());

//            set_difference(it_raw.begin(),it_raw.end(), s.begin(),s.end(), back_inserter(tmp2));
//            ans.push_back(tmp2);
        }
        if (!it_raw_copy.empty())ans.push_back(it_raw_copy);
    }
    return ans;
}

int main(int argc, char *argv[]) {
    string input = argv[1];
    auto S_list = generate_s_list(input);
    auto distance = generate_distance(S_list, input.size());
    auto sort_order = generate_sort_order(input);
//    for (auto i1: sort_order){
//        for (auto i2: i1){
//            cout << i2 << " ";
//        }
//        cout << endl;
//    }
    auto S_sort = sort_substr(S_list, input);

    vector<vector<int>> ans;
    for (const auto &it: sort_order) {
        vector<int> tmp;
        for (auto c: it) {
            auto idx = find(S_sort.begin(), S_sort.end(), c);
            if (idx != S_sort.end()) {
                tmp.push_back(c);
            }
        }
        if (!tmp.empty()) {
//            sort(tmp.begin(), tmp.end());
            ans.push_back(tmp);
        }
    }

    int max_distance = *max_element(distance.begin(), distance.end());
    output(ans);
    for (int i = 1; i <= max_distance; i++) {
        auto list = get_list(i, distance, sort_order);
        ans = split_s(ans, list);
        output(ans);
    }
}