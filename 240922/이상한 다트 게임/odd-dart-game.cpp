#include <iostream>

using namespace std;

struct point {
	int y, x;
};

int map[51][51], dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
int N, M, T;

void result() {
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cnt += map[i][j];
		}
	}

	cout << cnt;
}

void solve() {
	int n, dir, k, tmp_n;
	cin >> n >> dir >> k;
	tmp_n = n;
	while (1) {
		if (tmp_n > N)
			break;
		int tmp_map[51][51] = { 0, };
		for (int i = 1; i <= N; i++)
			tmp_map[tmp_n][i] = map[tmp_n][i];

		int de = 1;
		if (dir == 0) { // 시계
			for (int i = 1; i <= M; i++) {
				int idx = k + i;
				if (idx > M)
					idx -= M;
				map[tmp_n][idx] = tmp_map[tmp_n][i];
			}
		}
		else { // 반시계
			for (int i = 1; i <= M; i++) {
				int idx = k + i;
				if (idx > M)
					idx -= M;
				map[tmp_n][i] = tmp_map[tmp_n][idx];
			}
		}
		tmp_n += n;
	}
	int flag = 0;
	int visited[51][51] = { 0, };
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			point now = { i,j };
			if (map[now.y][now.x] == 0)
				continue;
			for (int a = 0; a < 4; a++) {
				point next = { 0, };
				next.y = now.y + dy[a];
				next.x = now.x + dx[a];

				if (next.y <= 0 || next.y > N)
					continue;
				if (next.x <= 0)
					next.x = N;
				if (next.x > N)
					next.x = 1;
				if (map[next.y][next.x] == map[now.y][now.x])
					visited[now.y][now.x] = visited[now.y][now.x] = 1, flag = 1;
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visited[i][j] == 1)
				map[i][j] = 0;
		}
	}
	if (flag != 0)
		return;
	int tmp_sum = 0, tmp_cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] == 0)
				continue;
			tmp_sum += map[i][j], tmp_cnt++;
		}
	}
	int tmp_avg = tmp_sum / tmp_cnt;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] == 0)
				continue;
			if (map[i][j] > tmp_avg)
				map[i][j] -= 1;
			else if (map[i][j] < tmp_avg)
				map[i][j] += 1;
		}
	}

}

void input() {
	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	for (int tc = 0; tc < T; tc++) {
		solve();
	}

	result();

	return 0;

}