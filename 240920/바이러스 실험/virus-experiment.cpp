#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct point {
	int y, x, age;
};
struct cmp {
	bool operator() (point a, point b) {
		return a.age > b.age;
	}
};
priority_queue<point, vector<point>, cmp> pq;

int N, M, T;
int add[11][11], map[11][11], dy[] = { -1,-1,0,1,1,1,0,-1 }, dx[] = { 0,1,1,1,0,-1,-1,-1 };

void solve() {
	vector<point> live, die;
	while (!pq.empty()) {
		point now = pq.top();
		pq.pop();
		if (now.age > map[now.y][now.x]){
			die.push_back(now);
			continue;
		}
		map[now.y][now.x] -= now.age;
		now.age++;
		live.push_back(now);
	}
	for (int i = 0; i < die.size(); i++) {
		point now = die[i];
		map[now.y][now.x] += now.age / 2;
	}
	for (int i = 0; i < live.size(); i++) {
		point now = live[i];
		pq.push(now);
		if (now.age != 5)
			continue;
		for (int j = 0; j < 8; j++) {
			point next = { 0, };
			next.y = now.y + dy[j];
			next.x = now.x + dx[j];
			if (next.y <= 0 || next.x <= 0 || next.y > N || next.x > N)
				continue;
			next.age = 1;
			pq.push(next);
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] += add[i][j];
		}
	}
}

void input() {
	cin >> N >> M >> T;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] = 5;
			cin >> add[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		int tmp_y, tmp_x, tmp_age;
		cin >> tmp_y >> tmp_x >> tmp_age;
		pq.push({ tmp_y,tmp_x,tmp_age });
	}

}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	input();
	for(int i = 0 ; i < T ; i++){
		solve();
	}
	
	cout << pq.size();
	return 0;
	}