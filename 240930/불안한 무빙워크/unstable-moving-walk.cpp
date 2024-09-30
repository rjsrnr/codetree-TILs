#include <iostream>
#include <deque>

using namespace std;

struct point {
    int idx, id;
};

deque<point> per;
int N, K, result;
int belt[250], rail[250], visited[250];


void add() {
    if (rail[belt[1]] == 0)
        return;
    per.push_back({ belt[1],1 });
    visited[belt[1]] = 1;
    rail[belt[1]]--;
    if (rail[belt[1]] == 0)
        result++;
}

void mv() {
    for (auto i = per.begin(); i != per.end(); i++) {
        int tmp_idx = i->idx + 1;
        if (tmp_idx > 2 * N)
            tmp_idx = 1;
        if (visited[tmp_idx] == 1 || rail[tmp_idx] == 0)
            continue;
        visited[i->idx] = 0;
        i->idx = tmp_idx;
        i->id += 1;
        visited[tmp_idx] = 1;
        rail[tmp_idx]--;      
        if (rail[tmp_idx] == 0)
            result++;
        if (i->id == N) {
            visited[tmp_idx] = 0;
            per.pop_front();
        }
        if (per.size() == 0)
            break;
    }
}

void mv_belt() {
    int tmp_rail = belt[2 * N];
    int tmp_visit = visited[2 * N];
    for (int i = 2 * N; i >= 2; i--) {
        belt[i] = belt[i - 1];
    }
    for (auto i = per.begin(); i != per.end(); i++) {
        int tmp_id = i->id + 1;
        if (tmp_id > 2 * N)
            tmp_id = 1;
        i->id = tmp_id;

    }
    belt[1] = tmp_rail;
}

void input() {
    cin >> N >> K;
    for (int i = 1; i <= 2 * N; i++) {
        cin >> rail[i];
        belt[i] = i;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    input();
    int tc = 1;
    while (1) {
        mv_belt();
        mv();
        add();
        if (result >= K) {
            cout << tc;
            return 0;
        }
        tc++;
    }

    return 0;
}