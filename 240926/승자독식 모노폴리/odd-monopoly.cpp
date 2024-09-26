#include <iostream>
#include <vector>

using namespace std;

struct point {
    int y, x, dir, state;
};
struct vs {
    int id, k, tmp_id;
};

int dir[401][5][5], dy[] = {0,-1,1,0,0}, dx[] = {0,0,0,-1,1};
point arr[401];
vs map[21][21];
int N, M, K, rcnt;

void mv(int idx, int di) {
    point now = { arr[idx].y, arr[idx].x };
    for (int i = 1; i <= 4; i++) {
        int tmp_dir = dir[idx][di][i];
        point next = { 0, };
        next.y = now.y + dy[tmp_dir];
        next.x = now.x + dx[tmp_dir];
        if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N)
            continue;
        if (map[next.y][next.x].id != 0)
            continue;
        if (map[next.y][next.x].tmp_id == 0) {
            map[next.y][next.x].tmp_id = idx;
            arr[idx].y = next.y, arr[idx].x = next.x;
            map[next.y][next.x].k = K;
            arr[idx].dir = tmp_dir;
            return;
        }
        else {
            arr[idx].state = 0;
            rcnt--;
            return;
        }
    }
    for (int i = 1; i <= 4; i++) {
        int tmp_dir = dir[idx][di][i];
        point next = { 0, };
        next.y = now.y + dy[tmp_dir];
        next.x = now.x + dx[tmp_dir];
        if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N)
            continue;
        if (map[next.y][next.x].id == idx) {
            map[next.y][next.x].k = K;
            arr[idx].y = next.y, arr[idx].x = next.x;
            arr[idx].dir = tmp_dir;
        }

    }
}

void solve() {
    for (int i = 1; i <= M; i++) {
        if (arr[i].state == 0)
            continue;
        mv(i,arr[i].dir);
    }

}
void input() {
    cin >> N >> M >> K;
    rcnt = M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j].id;
            if (map[i][j].id == 0)
                continue;
            arr[map[i][j].id].y = i, arr[map[i][j].id].x = j, arr[map[i][j].id].state = 1;
            map[i][j].k = K;
        }
    }
    for (int i = 1; i <= M; i++) {
        cin >> arr[i].dir;
    }
    for (int i = 1; i <= M; i++) {
        for (int a = 1; a <= 4; a++) {
            for(int b = 1 ; b <= 4 ; b++){
              cin >> dir[i][a][b];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();

    for (int tc = 0; tc <= 1000; tc++) {
        if (tc == 1000) {
            cout << -1;
            return 0;
        }
        if (rcnt == 1) {
            cout << tc;
            return 0;
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (map[i][j].k != 0){
                    map[i][j].k--;
                    if (map[i][j].k == 0)
                        map[i][j].id = 0;
                }
                if (map[i][j].tmp_id != 0)
                    map[i][j].id = map[i][j].tmp_id, map[i][j].tmp_id = 0;
            }
        }
        solve();
    }

    return 0;

}