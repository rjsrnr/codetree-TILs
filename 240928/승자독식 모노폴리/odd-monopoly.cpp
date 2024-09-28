#include <iostream>
#include <vector>

using namespace std;

struct point {
	int y, x, dir, state;
};
struct info {
	int id, tmp_id, k;
};

point arr[410];
info map[21][21];
int dir[402][5][5], dy[] = { 0,-1,1,0,0 }, dx[] = { 0,0,0,-1,1 };
int N, M, K, ncnt;

void mv(int idx, int tc) {
	point now = { arr[idx].y, arr[idx].x };
 	for (int i = 1; i <= 4; i++) {
		int tmp_dir = dir[idx][arr[idx].dir][i];
		point next = { 0, };
		next.y = now.y + dy[tmp_dir];
		next.x = now.x + dx[tmp_dir];
		if (next.y < 0 || next.x < 0 || next.x >= N || next.y >= N)
			continue;
		if (map[next.y][next.x].id != 0)
			continue;
		if (map[next.y][next.x].tmp_id != 0) {
			arr[idx].state = 0;
			ncnt--;
			arr[idx].y = next.y, arr[idx].x = next.x;
			return;
		}
		map[next.y][next.x].tmp_id = idx;
		arr[idx].y = next.y, arr[idx].x = next.x;
		arr[idx].dir = tmp_dir;
		return;
	}
	for (int i = 1; i <= 4; i++) {
		int tmp_dir = dir[idx][arr[idx].dir][i];
		point next = { 0, };
		next.y = now.y + dy[tmp_dir];
		next.x = now.x + dx[tmp_dir];
		if (next.y < 0 || next.x < 0 || next.x >= N || next.y >= N)
			continue;
		if (map[next.y][next.x].id != idx)
			continue;
		map[next.y][next.x].k = tc + K;
		arr[idx].y = next.y, arr[idx].x = next.x;
		arr[idx].dir = tmp_dir;
		return;
	}
}

void input() {
	cin >> N >> M >> K;
	ncnt = M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j].id;
			if (map[i][j].id == 0)
				continue;
			map[i][j].k = K;
			arr[map[i][j].id].y = i, arr[map[i][j].id].x = j;
			arr[map[i][j].id].state = 1;
		}
	}
	for (int i = 1; i <= M; i++) {
		cin >> arr[i].dir;
	}
	for (int i = 1; i <= M; i++) {
		for (int a = 1; a <= 4; a++) {
			for (int b = 1; b <= 4; b++) {
				cin >> dir[i][a][b];
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	int de = 1;
	for (int tc = 1; tc <= 1001; tc++) {

		for (int i = 1; i <= M; i++) {
			if (arr[i].state == 0)
				continue;
			mv(i, tc);
		}

		if (ncnt == 1) {
			cout << tc;
			return 0;
		}
		else if (tc > 1000) {
			cout << -1;
			return 0;
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j].tmp_id == 0)
					continue;
				map[i][j].id = map[i][j].tmp_id;
				map[i][j].k = tc + K;
				map[i][j].tmp_id = 0;
			}
		}
		int da = 1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j].k != tc)
					continue;
				map[i][j].id = map[i][j].k = 0;
			}
		}
	}


	return 0;
}