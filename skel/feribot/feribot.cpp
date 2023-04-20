#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

vector<long long> ReadVector(istream& is, long long size) {
    vector<long long> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

// Function that gets the minimum number in array
long long return_min(vector<long long> a) {
    long long min = a[0];
    for (auto num : a) {
        if (num < min) {
            min = num;
        }
    }
    return min;
}

// Function that gets the sum of the numbers in array
long long return_sum(vector<long long> a) {
    long long sum = 0;
    for (auto num : a) {
        sum += num;
    }
    return sum;
}

// Function that gets the minimum weight using binary search
long long binary_search(vector<long long> a, int n, int k) {
    // Get left and right
    long long l = return_min(a);
    long long r = return_sum(a);

    // Apply binary search
    while (l < r) {
        long long mid = (l + r) / 2;
        int ok = 0;
        int cnt = 0;
        long long sum = 0;

        // Iterate through all the elements inside the array
        for (auto num : a) {
            // If the current element's weight is larger than mid
            // search to the right.
            if (num > mid) {
                ok = 1;
                break;
            }

            // Restart the sum if the current sum is larger than mid
            // and increment the counter
            if (sum + num > mid) {
                cnt++;
                sum = num;
            } else {
                sum += num;
            }
        }

        // Increment the counter for the final ferry
        cnt++;

        if (ok == 1) {
            l = mid + 1;
        } else {
            if (cnt <= k) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
    }

    return l;
}

int main() {
    ifstream fin("feribot.in");
    ofstream fout("feribot.out");
    int n, k;
    fin >> n >> k;

    auto a = ReadVector(fin, n);

    fout << binary_search(a, n, k);

    return 0;
}
