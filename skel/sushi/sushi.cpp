#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int task1(int n, int m, int x, vector <int>& p, vector <vector <int> >& g) {
	// Taken from dp lab, knapsack problem adapted
	vector< vector<int> > dp(m + 1, vector<int>(n * x + 1, 0));

    for (int cap = 0; cap <= n * x; ++cap) {
        dp[0][cap] = 0;
    }

	vector<int> sum;
	sum.assign(m, 0);
	for(int j = 0; j < m; ++j) {
		for(int i = 0; i < n; ++i) {
			sum[j] += g[i][j];
		}
	}

    for (int i = 1; i <= m; ++i) {
        for (int cap = 0; cap <= n * x; ++cap) {
            dp[i][cap] = dp[i-1][cap];

            if (cap - p[i - 1] >= 0) {
                int sol_aux = dp[i-1][cap - p[i - 1]] + sum[i - 1];
                dp[i][cap] = max(dp[i][cap], sol_aux);
            }
        }
    }

    return dp[m][n * x];
}

// Same as task1, just check if we can take 2 sushis
int task2(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	vector< vector<int> > dp(m + 1, vector<int>(n * x + 1, 0));
    for (int cap = 0; cap <= n * x; ++cap) {
        dp[0][cap] = 0;
    }

	vector<int> sum;
	sum.assign(m, 0);
	for(int j = 0; j < m; ++j) {
		for(int i = 0; i < n; ++i) {
			sum[j] += g[i][j];
		}
	}
    for (int i = 1; i <= m; ++i) {
        for (int cap = 0; cap <= n * x; ++cap) {
            dp[i][cap] = dp[i-1][cap];

            if (cap - p[i - 1] >= 0) {
                int sol_aux = dp[i-1][cap - p[i - 1]] + sum[i - 1];

                dp[i][cap] = max(dp[i][cap], sol_aux);
            }
			if (cap - 2 * p[i - 1] >= 0) {
                int sol_aux = dp[i-1][cap - 2 * p[i - 1]] + 2 * sum[i - 1];

                dp[i][cap] = max(dp[i][cap], sol_aux);
            }
        }
    }

    return dp[m][n * x];
}

// Same as before, just adding a new dimension to see how many times
// the sushi has been purchased
int task3(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	vector<vector<vector <int>> > dp(m + 1, vector<vector<int>>
	(n * x + 1, vector<int>(n + 1, 0)));

	vector<int> sum;
	sum.assign(m, 0);
	for(int j = 0; j < m; ++j) {
		for(int i = 0; i < n; ++i) {
			sum[j] += g[i][j];
		}
	}

    for (int i = 1; i <= m; ++i) {
        for (int cap = 0; cap <= n * x; ++cap) {
			for (int j = 1; j <= n; j++) {
				dp[i][cap][j] = dp[i-1][cap][j];

				if (cap - p[i - 1] >= 0) {
					int sol_aux = dp[i-1][cap - p[i - 1]][j - 1] + sum[i - 1];

					dp[i][cap][j] = max(dp[i][cap][j], sol_aux);
				}
				if (cap - 2 * p[i - 1] >= 0 && j - 2 >= 0) {
					int sol_aux = dp[i-1][cap - 2 * p[i - 1]][j - 2] + 2 * sum[i - 1];

					dp[i][cap][j] = max(dp[i][cap][j], sol_aux);
				}
			}
        }
    }

    return dp[m][n * x][n];
}

int main() {
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);

	int task;  // task number

	int n;  // number of friends
	int m;  // number of sushi types
	int x;  // how much each of you is willing to spend

	vector <int> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <int> > grades;

	cin >> task;
	cin >> n >> m >> x;

	prices.assign(m, 0);
	grades.assign(n, vector <int> (m, 0));

	// price of each sushi
	for(int i = 0; i < m; ++i) {
		cin >> prices[i];
	}

	// each friends rankings of sushi types
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cin >> grades[i][j];
		}
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	cout << ans << endl;

	return 0;
}
