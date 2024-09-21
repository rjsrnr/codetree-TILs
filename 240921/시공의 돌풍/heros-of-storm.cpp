#include <iostream>

using namespace std;

struct point {
	int y, x;
};
struct dust {
	int now, add;
};

int N, M, T;
int dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
dust map[51][51];
point th1, th2;

void tornado(point now, int type) {
	int dir = 3;
	point st = now;
	int tmpval_now, tmpval_next = map[now.y][now.x].now;
	while (1) {
		point next = { 0, };
		next.y = now.y + dy[dir];
		next.x = now.x + dx[dir];
		
		if (next.x >= M && type == 1) {
			dir = 0;
			continue;
		}
		else if (next.x >= M && type == 2) {
			dir = 1;
			continue;
		}
		else if (next.x < 0 && type == 1) {
			dir = 1;
			continue;
		}
		else if (next.x < 0 && type == 2) {
			dir = 0;
			continue;
		}
		else if (next.y < 0) {
			dir = 2;
			continue;
		}
		else if (next.y >= N) {
			dir = 2;
			continue;
		}
		else if (next.y == st.y && next.x == st.x)
			break;
		tmpval_now = tmpval_next;
		tmpval_next = map[next.y][next.x].now;

		if (map[now.y][now.x].now == -1)
			map[next.y][next.x].now = 0;
		else
			map[next.y][next.x].now = tmpval_now;

		now = next;
	}
}

void sp_dust() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j].now <= 0)
				continue;
			int tmp_num = 0;
			for(int dir = 0 ; dir < 4 ; dir++){
				int tmp_add = map[i][j].now / 5;
				point next = { 0, };
				next.y = i + dy[dir];
				next.x = j + dx[dir];
				if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= M || map[next.y][next.x].now == -1)
					continue;
				tmp_num += tmp_add;
				map[next.y][next.x].add += tmp_add;
			}
			map[i][j].now -= tmp_num;
 		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j].now == -1)
				continue;
			map[i][j].now += map[i][j].add;
			map[i][j].add = 0;
		}
	}
}

void input() {
	cin >> N >> M >> T;
	int tmp = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j].now;
			if (map[i][j].now == -1 && tmp == 0)
				th1 = { i,j }, tmp++;
			else if (map[i][j].now == -1 && tmp == 1)
				th2 = { i,j };
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	for (int i = 0; i < T; i++) {
		sp_dust();
		tornado(th1, 1);
		tornado(th2, 2);
	}
	int result = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j].now == -1)
				continue;
			result += map[i][j].now;
		}
	}

	cout << result;

	return 0;
}