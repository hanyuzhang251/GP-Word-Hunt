#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <cctype>
#include <string>
#include <chrono>

using namespace std;

const int maxDepth = 13;
std::unordered_set<std::string> dictionary;

std::unordered_map<string, pair<int, int>> order;


char chars[4][4];
bool vis[4][4];
ofstream fout("/Users/hanyuzhang/CLionProjects/Sketch/correct");

bool isEnglishWord(const std::string &word, const std::unordered_set<std::string> &dictionary) {
    return dictionary.find(word) != dictionary.end();
}

bool valid(int x, int y, int depth) {
    return x >= 0 && x < 4 && y >= 0 && y < 4 && !vis[x][y] && depth <= maxDepth;
}

bool compareByLength(const std::string &a, const std::string &b) {
    return a.length() > b.length();
}

pair<int, int> currOrder[maxDepth + 1];


void dfs(int x, int y, int depth, string word) {
    if (!valid(x, y, depth)) {
        return;
    }
    ++depth;
    word += chars[x][y];
    currOrder[0] = {depth, -1};
    currOrder[depth] = {x, y};
    if (depth >= 3) {
        if (isEnglishWord(word, dictionary)) {
            fout << word << endl;
            for (int i = 0; i <= currOrder[0].first; ++i) {
                string key = word + to_string(i);
                order[key] = currOrder[i];
            }
        }
    }
    vis[x][y] = true;
    dfs(x + 1, y, depth, word);
    dfs(x, y + 1, depth, word);
    dfs(x - 1, y, depth, word);
    dfs(x, y - 1, depth, word);
    dfs(x + 1, y + 1, depth, word);
    dfs(x + 1, y - 1, depth, word);
    dfs(x - 1, y + 1, depth, word);
    dfs(x - 1, y - 1, depth, word);
    vis[x][y] = false;
    currOrder[0] = {depth - 1, -1};
}

std::string toLowerCase(const std::string &str) {
    std::string result;
    for (char c: str) {
        result += std::tolower(c);
    }
    return result;
}

int main() {
    std::ifstream dictionaryFile("/Users/hanyuzhang/CLionProjects/Sketch/englishdict.txt");
    if (!dictionaryFile.is_open()) {
        return 1;
    }


    std::string word;
    while (std::getline(dictionaryFile, word)) {
        dictionary.insert(toLowerCase(word));
    }
    dictionaryFile.close();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> chars[i][j];
            vis[i][j] = false;
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            dfs(i, j, 0, "");
        }
    }
    fout.close();
    ifstream fin("/Users/hanyuzhang/CLionProjects/Sketch/correct");
    unordered_set<string> words;
    if (!fin.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    string line;
    while (getline(fin, line)) {
        words.insert(line);
    }
    vector<string> unduplicate;
    for (auto i: words) {
        unduplicate.push_back(i);
    }
    sort(unduplicate.begin(), unduplicate.end(), compareByLength);
    fin.close();
    ofstream fout("/Users/hanyuzhang/CLionProjects/Sketch/SOLUTIONS");
    for (const auto &i: unduplicate) {
        fout << i << endl;
    }
    for (string i: unduplicate) {
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << i
             << endl;
        char field[4][4];

        for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                field[x][y] = '.';
            }
        }
        for (int j = 1; j <= i.length(); ++j) {
            int x = order[i + to_string(j)].first;
            int y = order[i + to_string(j)].second;
            field[x][y] = to_string(j)[0];
        }
        for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                cout << field[x][y] << ' ';
            }
            cout << endl;
        }
        string a;
        cin >> a;
    }
}