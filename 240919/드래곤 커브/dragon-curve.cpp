#include <iostream>
#include <vector>

using namespace std;

struct point {
	int y, x;
};
int dy[] = { 0,-1,0,1 }, dx[] = { 1,0,-1,0 };
int map[101][101];
int cnt;

void solve() {
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			if (map[i][j] == 1 && map[i + 1][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1)
				cnt++;
		}
	}
	cout << cnt;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		int y, x, dir, gen;
		cin >> y >> x >> dir >> gen;
		point now = { y,x };
		map[now.y][now.x] = 1;
		now.y += dy[dir], now.x += dx[dir];
		map[now.y][now.x] = 1;
		vector<int> dragon;
		dragon.push_back(dir);
		for (int i = 0; i < gen; i++) {
			for (int j = dragon.size() - 1; j >= 0; j --) {
				int tmp_dir = (dragon[j] + 1) % 4;
				now.y += dy[tmp_dir], now.x += dx[tmp_dir];
				dragon.push_back(tmp_dir);
				map[now.y][now.x] = 1;
			}
		}
		int de = 1;
	}
		solve();

	return 0;
}