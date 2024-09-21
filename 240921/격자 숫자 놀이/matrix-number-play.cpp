#include <iostream>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

struct point {
	int y, x, val;
};
struct num {
	int val, cnt;
};
struct cmp {
	bool operator () (num a, num b) {
		if(a.cnt != b.cnt){
			return a.cnt > b.cnt;
		} else
			return a.val > b.val;
	}
};

point st;
int arr[210][210];
int r, c;

void solve() {
	int tmp_map[210][210] = { 0, };
	if ( r >= c) {
		int mx_c = 0;
	
		for (int i = 0; i < r; i++) {
			map<int, int> tmp;
			for (int j = 0; j < c; j++) {
				if (arr[i][j] == 0)
					continue;
				tmp[arr[i][j]]++;
			}
			priority_queue<num, vector<num>, cmp> pq;
			for (auto a = tmp.begin(); a != tmp.end(); a++) {
				pq.push({ a->first, a->second });
			}
			int tmp_c = 0;
			while (!pq.empty()) {
				num now = pq.top();
				pq.pop();
				tmp_map[i][tmp_c] = now.val;
				tmp_c++;
				if (tmp_c >= 100)
					break;
				tmp_map[i][tmp_c] = now.cnt;
				tmp_c++;
				if (tmp_c >= 100)
					break;
			}
			mx_c = max(tmp_c, mx_c);
		}
		c = mx_c + 1;
	}
	else {
		int mx_r = 0;

		for (int i = 0; i < c; i++) {
			map<int, int> tmp;
			for (int j = 0; j < r; j++) {
				if (arr[j][i] == 0)
					continue;
				tmp[arr[j][i]]++;
			}
			priority_queue<num, vector<num>, cmp> pq;
			for (auto a = tmp.begin(); a != tmp.end(); a++) {
				pq.push({ a->first, a->second });
			}
			int tmp_r = 0;
			while (!pq.empty()) {
				num now = pq.top();
				pq.pop();
				tmp_map[tmp_r][i] = now.val;
				tmp_r++;
				if (tmp_r >= 100)
					break;
				tmp_map[tmp_r][i] = now.cnt;
				tmp_r++;
				if (tmp_r >= 100)
					break;
			}
			mx_r = max(tmp_r, mx_r);
		}
		r = mx_r + 1;
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			arr[i][j] = tmp_map[i][j];
		}
	}
}

void input() {
	cin >> st.y >> st.x >> st.val;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> arr[i][j];
		}
	}
	r = 3, c = 3;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	int flag = 0;
	for (int tc = 1; tc <= 100; tc++) {
		solve();
		if (arr[st.y - 1][st.x - 1] == st.val) {
			flag = tc;
			break;
		}
	}

	if (flag != 0)
		cout << flag;
	else
		cout << -1;

	return 0;
}