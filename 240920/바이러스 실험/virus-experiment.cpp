#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

struct vir {
    int age[1021];
    set<int> se;
};
struct point {
    int y, x;
};
struct state {
    int y, x, age, cnt;
};

int dy[] = { -1,-1,0,1,1,1,0,-1 }, dx[] = { 0,1,1,1,0,-1,-1,-1 }, map[11][11], pl[11][11];
int N, M, T;
vir arr[11][11];
queue<point> q;

void solve() {
    vector<state> live, die;

    while (!q.empty()) {
        point now = q.front();
        q.pop();

        set<int> tmp_set = arr[now.y][now.x].se;
        arr[now.y][now.x].se.clear();
        set<int> tmp;

        for (auto i : tmp_set) {// i는 age이고 arr[now.y][now.x].age[i]는 해당 age의 갯수
            if (i * arr[now.y][now.x].age[i] <= map[now.y][now.x]) {
                map[now.y][now.x] -= i * arr[now.y][now.x].age[i];
                live.push_back({ now.y,now.x,i + 1,arr[now.y][now.x].age[i] });
            }
            else {
                int possi = map[now.y][now.x] / i; // age갯수중 몇개 가능한지
                map[now.y][now.x] -= possi * i;
                die.push_back({ now.y,now.x,i,arr[now.y][now.x].age[i] - possi });
                if (possi != 0)
                    live.push_back({ now.y,now.x, i + 1 ,possi });
            }
            arr[now.y][now.x].age[i] = 0;
        }
    }
    for (int i = 0; i < live.size(); i++) {
        point now = { live[i].y,live[i].x };
        arr[now.y][now.x].age[live[i].age] += live[i].cnt;
        if (arr[now.y][now.x].se.size() == 0)
            q.push(now);
        arr[now.y][now.x].se.insert(live[i].age);
        for(int tc = 0 ; tc < live[i].cnt ; tc++){
            if (live[i].age % 5 == 0) {
                for (int j = 0; j < 8; j++) {
                    point next = { 0, };
                    next.y = now.y + dy[j];
                    next.x = now.x + dx[j];
                    if (next.y <= 0 || next.x <= 0 || next.y > N || next.x > N)
                        continue;
                    arr[next.y][next.x].age[1]++;
                    if (arr[next.y][next.x].se.size() == 0)
                        q.push(next);
                    arr[next.y][next.x].se.insert(1);
                    M += 1;
                }
            }
        }
    }
    for (int i = 0; i < die.size(); i++) {
        point now = { die[i].y,die[i].x };
        int num = die[i].age / 2;
        map[now.y][now.x] += num * die[i].cnt;
        M -= die[i].cnt;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            map[i][j] += pl[i][j];
        }
    }
}

void input() {
    cin >> N >> M >> T;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            map[i][j] = 5;
            cin >> pl[i][j];
        }
    }
    for (int i = 0; i < M; i++) {
        int tmp_y, tmp_x, tmp_age;
        cin >> tmp_y >> tmp_x >> tmp_age;
        q.push({ tmp_y,tmp_x });
        arr[tmp_y][tmp_x].se.insert(tmp_age);
        arr[tmp_y][tmp_x].age[tmp_age]++;
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
    cout << M;


    return 0;
}