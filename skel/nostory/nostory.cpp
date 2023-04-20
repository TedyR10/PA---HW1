#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

ifstream fin("nostory.in");
ofstream fout("nostory.out");

int64_t SolveTask1(vector<int>& a, vector<int>& b) {
    // Sort both arrays
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long sum = 0;
    int last = a.size() - 1;

    // Iterate through the arrays and pick the best number
    // comparing the front of one array with the back of the other
    for (int i = 0; i < a.size(); i++) {
        if (a[i] > b[last]) {
            sum += a[i];
            last--;
        } else {
            sum += b[last];
            last--;
        }
    }

    return sum;
}

int64_t SolveTask2(vector<int>& a, vector<int>& b, int moves) {
    // The idea is similar to task 1, but here we will initially
    // swap positions only (not making any moves)
    // based on the larger of the two numbers on each position
    for (long long i = 0; i < a.size(); i++) {
        if (a[i] > b[i])
            swap(a[i], b[i]);
    }

    // Sort the arrays
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long last = a.size() - 1;
    long long i = 0;

    // We check if the last number from a is larger than the
    // first number of b (b array being the array with larger
    // overall numbers due to the swapping above) and we swap
    // them
    while (moves && last) {
        if (a[last] >= b[i]) {
            swap(a[last], b[i]);
            moves--;
        }
        last--;
        i++;
    }

    // Lastly, get the score by getting the max between the arrays
    long long score = 0;
    for (long long i = 0; i < a.size(); i++) {
        score += max(a[i], b[i]);
    }

    return score;
}

vector<int> ReadVector(istream& is, int size) {
    vector<int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    int task;
    fin >> task;

    int n, moves;
    if (task == 1) {
        fin >> n;
    } else {
        fin >> n >> moves;
    }

    auto a = ReadVector(fin, n);
    auto b = ReadVector(fin, n);

    auto res = task == 1 ? SolveTask1(a, b) : SolveTask2(a, b, moves);
    fout << res << "\n";

    return 0;
}
