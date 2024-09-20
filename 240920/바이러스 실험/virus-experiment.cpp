#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct st {
	int val;
	map<int, int> info;
};
struct point {
	int y, x, age, cnt;
};

int N, M, T;
int pl[11][11], dy[] = { -1,-1,0,1,1,1,0,-1 }, dx[] = { 0,1,1,1,0,-1,-1,-1 };
st arr[11][11];

void solve() {
	vector<point> live, die;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (auto a = arr[i][j].info.begin(); a != arr[i][j].info.end(); a++) {
				if (a->first * a->second <= arr[i][j].val) {
					arr[i][j].val -= a->first * a->second;
					live.push_back({ i,j,a->first + 1 , a->second });
				}
				else {
					int poss = arr[i][j].val / a->first;
					arr[i][j].val -= a->first * poss;
					die.push_back({ i,j,a->first, a->second - poss });
					if (poss != 0)
						live.push_back({ i,j,a->first + 1 , poss });
				}
			}
			arr[i][j].info.clear();
		}
	}
	for (int i = 0; i < die.size(); i++) {
		point now = { die[i].y,die[i].x };
		arr[now.y][now.x].val += (die[i].age / 2) * die[i].cnt;
	}
	for (int i = 0; i < live.size(); i++) {
		point now = { live[i].y,live[i].x };
		arr[now.y][now.x].info[live[i].age] += live[i].cnt;
		if (live[i].age % 5 != 0)
			continue;
		for (int tc = 0; tc < live[i].cnt; tc++){
			for (int j = 0; j < 8; j++) {
				point next = { 0, };
				next.y = now.y + dy[j];
				next.x = now.x + dx[j];
				if (next.y > N || next.x > N || next.y <= 0 || next.x <= 0)
					continue;
				arr[next.y][next.x].info[1]++;
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			arr[i][j].val += pl[i][j];
		}
	}
}

void input() {
	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> pl[i][j];
			arr[i][j].val = 5;
		}
	}
	for (int i = 0; i < M; i++) {
		int y, x, val;
		cin >> y >> x >> val;
		arr[y][x].info[val]++;
	}

}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	for (int i = 0; i < T; i++) {
		solve();
	}
	int result = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (auto a = arr[i][j].info.begin(); a != arr[i][j].info.end(); a++)
				result += a->second;
		}
	}

	cout << result;

	return 0;

}