#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <cctype>
#include <string>
#include <chrono>
#include <future>


using namespace std;

const int maxDepth = 16;
std::unordered_set<std::string> dictionary;

std::unordered_map<string, pair<int, int> > order;

/*absorptivenesses
a b s o
e s s r
n s e p
e v i t
*/

char chars[4][4];
ofstream fout("/Users/hanyuzhang/CLionProjects/Sketch/correct");

bool isEnglishWord(const std::string &word, const std::unordered_set<std::string> &dictionary) {
    return dictionary.find(word) != dictionary.end();
}

bool valid(int x, int y, int depth, bool vis[4][4]) {
    return x >= 0 && x < 4 && y >= 0 && y < 4 && !vis[x][y] && depth <= maxDepth;
}

bool compareByLength(const std::string &a, const std::string &b) {
    return a.length() > b.length();
}

void dfs(int x, int y, int depth, string word, pair<int, int> currOrder[], bool vis[4][4]) {
    if (!valid(x, y, depth, vis)) {
        return;
    }
    vis[x][y] = true;
    ++depth;
    word.push_back(chars[x][y]);
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
    dfs(x + 1, y, depth, word, currOrder, vis);
    dfs(x, y + 1, depth, word, currOrder, vis);
    dfs(x - 1, y, depth, word, currOrder, vis);
    dfs(x, y - 1, depth, word, currOrder, vis);
    dfs(x + 1, y + 1, depth, word, currOrder, vis);
    dfs(x + 1, y - 1, depth, word, currOrder, vis);
    dfs(x - 1, y + 1, depth, word, currOrder, vis);
    dfs(x - 1, y - 1, depth, word, currOrder, vis);
    vis[x][y] = false;
    currOrder[0] = {depth - 1, -1};
}

void parallelDFS(int x, int y) {
    pair<int, int> order[maxDepth + 1];
    bool vis[4][4];
    for (auto &vi: vis) {
        for (bool &j: vi) {
            j = false;
        }
    }
    dfs(x, y, 0, "", order, vis);
}

std::string toLowerCase(const std::string &str) {
    std::string result;
    for (char c: str) {
        result += std::tolower(c);
    }
    return result;
}

int main() {
    std::vector<std::future<void> > futures;

    std::cout << "opening didct" << std::endl;
    std::ifstream dictionaryFile("/Users/hanyuzhang/CLionProjects/Sketch/englishdict.txt");
    std::cout << "dict open" << std::endl;
    if (!dictionaryFile.is_open()) {
        std::cout << "dict not open" << std::endl;
        return 1;
    }


    std::string word;
    std::cout << "loading dict" << std::endl;
    while (std::getline(dictionaryFile, word)) {
        dictionary.insert(toLowerCase(word));
    }
    std::cout << std::endl << "dict loaded" << std::endl;
    dictionaryFile.close();
    std::cout << "taking input" << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> chars[i][j];
        }
    }
    std::cout << "input taken" << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << "pushing future (" << i << ", " << j << ")" << std::endl;
            futures.push_back(std::async(std::launch::async, parallelDFS, i, j));
        }
    }
    std::cout << "waiting" << std::endl;
    for (auto &fut: futures) {
        fut.get();
    }
    std::cout << "done" << std::endl;

    // for (int i = 0; i < 4; ++i) {
    //     for (int j = 0; j < 4; ++j) {
    //         dfs(i, j, 0, "");
    //     }
    // }
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
    unduplicate.reserve(words.size());
    for (const auto &i: words) {
        unduplicate.push_back(i);
    }
    sort(unduplicate.begin(), unduplicate.end(), compareByLength);
    fin.close();
    ofstream fout("/Users/hanyuzhang/CLionProjects/Sketch/SOLUTIONS");
    for (const auto &i: unduplicate) {
        fout << i << endl;
    }
    for (const string &i: unduplicate) {
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << i
                << endl;
        char field[4][4];

        for (auto &x: field) {
            for (char &y: x) {
                y = '.';
            }
        }
        for (int j = 1; j <= i.length(); ++j) {

            int x = order[i + to_string(j)].first;
            int y = order[i + to_string(j)].second;
            field[x][y] = to_string(j)[0];
        }
        for (auto &x: field) {
            for (char y: x) {
                cout << y << ' ';
            }
            cout << endl;
        }
        string a;
        cin >> a;
    }
}
