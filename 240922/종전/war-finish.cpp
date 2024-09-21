#include <iostream>
#include <algorithm>

using namespace std;

struct point {
	int y, x;
};

int map[21][21], dy[] = { 1,1, -1, -1 }, dx[] = { -1,1, 1, -1 };
int N, result = 21e8;

void check(point a, point b, point c, point d) {
	int n1, n2, n3, n4, n5;
	n1 = n2 = n3 = n4 = n5 = 0;
	int arr[21][21] = { 0, };
	point st;
	st = a;
	if (a.y == 1 && a.x == 2 && b.y == 2 && b.x == 1 && c.y == 3 && c.x == 2 && d.y == 2 && d.x == 3)
		int da = 1;
	while (1) {
		if (st.y == b.y && st.x == b.x)
			break;
		else if(st.y == a.y && st.x == a.x){
			int tmp_y = st.y - 1;
			while (1) {
				if (tmp_y < 0)
					break;
				for (int i = st.x; i >= 0; i--)
					arr[tmp_y][i] = 2;
				tmp_y--;
			}
		}
		for (int i = st.x - 1; i >= 0; i--)
			arr[st.y][i] = 2;
		st.y += dy[0], st.x += dx[0];
	}
	st = b;
	while (1) {
		if (st.y == c.y && st.x == c.x)
			break;
		else if (st.y == b.y && st.x == b.x) {
			int tmp_x = st.x - 1;
			while (1) {
				if (tmp_x < 0)
					break;
				for (int i = st.y; i < N; i++)
					arr[i][tmp_x] = 4;
				tmp_x--;
			}
		}
		for (int i = st.y + 1; i < N; i++)
			arr[i][st.x] = 4;
		st.y += dy[1], st.x += dx[1];
	}
	st = c;
	while (1) {
		if (st.y == d.y && st.x == d.x)
			break;
		else if (st.y == c.y && st.x == c.x) {
			int tmp_y = st.y + 1;
			while (1) {
				if (tmp_y >= N)
					break;
				for (int i = st.x; i < N; i++)
					arr[tmp_y][i] = 5;
				tmp_y++;
			}
		}
		for (int i = st.x + 1; i < N; i++)
			arr[st.y][i] = 5;
		st.y += dy[2], st.x += dx[2];
	}
	st = d;
	while (1) {
		if (st.y == a.y && st.x == a.x)
			break;
		else if (st.y == d.y && st.x == d.x) {
			int tmp_x = st.x + 1;
			while (1) {
				if (tmp_x >= N)
					break;
				for (int i = st.y; i >= 0; i--)
					arr[i][tmp_x] = 3;
				tmp_x++;
			}
		}
		for (int i = st.y - 1; i >= 0; i--)
			arr[i][st.x] = 3;
		st.y += dy[3], st.x += dx[3];
	}
	if (a.y == 1 && a.x == 2 && b.y == 2 && b.x == 1 && c.y == 3 && c.x == 2 && d.y == 2 && d.x == 3)
		int de = 1;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (arr[i][j] == 0)
				n1 += map[i][j];
			else if (arr[i][j] == 2)
				n2 += map[i][j];
			else if (arr[i][j] == 3)
				n3 += map[i][j];
			else if (arr[i][j] == 4)
				n4 += map[i][j];
			else if (arr[i][j] == 5)
				n5 += map[i][j];

		}
	}
	int maxval, minval;
	maxval = max({ n1, n2, n3, n4, n5 });
	minval = min({ n1, n2, n3, n4, n5 });
	result = min(result, maxval - minval);
}

void solve(point st) {
	point a, b, c, d;
	a = b = st;
	while (1) {
		b.y += dy[0], b.x += dx[0];
		if (b.y >= N || b.x < 0)
			break;
		d = a;
		c = b;

		while (1) {
			c.y += dy[1], c.x += dx[1];
			d.y += dy[1], d.x += dx[1];
			if (c.y >= N || c.x >= N || d.y >= N || d.x >= N)
				break;
			check(a, b, c, d);
		}
		
	}
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			solve({ i,j });
		}
	}

	cout << result;

	return 0;
}