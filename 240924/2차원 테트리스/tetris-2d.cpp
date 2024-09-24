#include <iostream>
#include <vector>

using namespace std;

struct point {
    int y, x;
};
int red[4][4], yel[4][4];
int T, result;
int map[4][4];

void check_yel() {
    int idx = 3;
    while (1) {
        if (idx < 0)
            break;
        if (yel[idx][0] == 0 || yel[idx][1] == 0 || yel[idx][2] == 0 || yel[idx][3] == 0) {
            idx--;
            continue;
        }
        result++;
        for (int i = idx; i >= 1; i--) {
            for (int j = 0; j < 4; j++) {
                yel[i][j] = yel[i - 1][j];
            }
        }
        for (int i = 0; i < 4; i++) {
            yel[0][i] = 0;
        }
    }
}

void check_red() {
    int idx = 3;
    while (1) {
        if (idx < 0)
            break;
        if (red[0][idx] == 0 || red[1][idx] == 0 || red[2][idx] == 0 || red[3][idx] == 0) {
            idx--;
            continue;
        }
        result++;
        for (int i = idx; i >= 1; i--) {
            for (int j = 0; j < 4; j++) {
                red[j][i] = red[j][i - 1];
            }
        }
        for (int i = 0; i < 4; i++) {
            red[i][0] = 0;
        }
    }
}

void mv_ye() {
    for (int i = 3; i >= 1; i--) {
        for (int j = 0; j < 4; j++) {
            yel[i][j] = yel[i - 1][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        yel[0][i] = 0;
    }
}

void mv_re() {
    for (int i = 3; i >= 1; i--) {
        for (int j = 0; j < 4; j++) {
            red[j][i] = red[j][i - 1];
        }
    }
    for (int i = 0; i < 4; i++) {
        red[i][0] = 0;
    }
}

void ye(point input, int type) {
    if (type == 1){
        point now = { 0,input.x };
        if (yel[now.y][now.x] == 1)
            mv_ye();
        while (1) {
            point next = now;
            next.y = now.y + 1, next.x = now.x;

            if (next.y >= 4 || yel[next.y][next.x] == 1)
                break;
            now = next;
        }
        yel[now.y][now.x] = 1;
    }
    else if (type == 2) {
        point now1 = { 0,input.x };
        point now2 = { now1.y, now1.x + 1 };
        while (1) {
            int flag = 0;
            if (yel[now1.y][now1.x] == 1 || yel[now2.y][now2.x] == 1)
                mv_ye(), flag = 1;
            if (flag == 0)
                break;
        }
        while (1) {
            point next1 = now1, next2 = now2;
            next1.y = now1.y + 1, next2.y = now2.y + 1;
            if (next1.y >= 4 || next2.y >= 4 || yel[next1.y][next1.x] == 1 || yel[next2.y][next2.x] == 1)
                break;
            now1 = next1, now2 = next2;
        }
        yel[now1.y][now1.x] = yel[now2.y][now2.x] = 1;

    }
    else if (type == 3) {
        point now1 = { 0,input.x };
        point now2 = { 0,input.x };
        while (1) {
            int flag = 0;
            if (yel[now2.y][now2.x] == 1)
                mv_ye(), flag = 1;
            if (flag == 0)
                break;
        }
        while (1) {
            point next2 = now2;
             next2.y = now2.y + 1;
            if (next2.y >= 4 || yel[next2.y][next2.x] == 1 )
                break;
            now2 = next2;
        }
        yel[now2.y][now2.x] = 1;
        check_yel();
        while (1) {
            int flag = 0;
            if (yel[now1.y][now1.x] == 1)
                mv_ye(), flag = 1;
            if (flag == 0)
                break;
        }
        while (1) {
            point next1 = now1;
            next1.y = now1.y + 1;
            if (next1.y >= 4 || yel[next1.y][next1.x] == 1 )
                break;
            now1 = next1;
        }
        yel[now1.y][now1.x] = 1;
    }
    check_yel();
    int de = 1;
}

void re(point input, int type) {
    
    if (type == 1) {
        point now = { input.y, 0 };
        if (red[now.y][now.x] == 1)
            mv_re();
        while (1) {
            point next = now;
            next.y = now.y, next.x = now.x + 1;
            if (next.x >= 4 || red[next.y][next.x] == 1)
                break;
            now = next;
        }
        red[now.y][now.x] = 1;
    }
    else if (type == 2) {
        point now1 = { input.y ,0 };
        point now2 = { input.y ,0 };
        while (1) {
            int flag = 0;
            if (red[now2.y][now2.x] == 1)
                mv_re(), flag = 1;
            if (flag == 0)
                break;
        }
        while (1) {
            point next2 = now2;
            next2.x = now2.x + 1;
            if (next2.x >= 4 || red[next2.y][next2.x] == 1)
                break;
            now2 = next2;
        }
        red[now2.y][now2.x] = 1;
        check_red();
        while (1) {
            int flag = 0;
            if (red[now1.y][now1.x] == 1)
                mv_re(), flag = 1;
            if (flag == 0)
                break;
        }
        while (1) {
            point next1 = now1;
            next1.x = now1.x + 1;
            if (next1.x >= 4 || red[next1.y][next1.x] == 1)
                break;
            now1 = next1;
        }
        red[now1.y][now1.x] = 1;
    }
    else if (type == 3) {
        point now1 = { input.y, 0 };
        point now2 = { now1.y + 1 , now1.x };
        while (1) {
            int flag = 0;
            if (red[now1.y][now1.x] == 1 || red[now2.y][now2.x] == 1)
                mv_re(), flag = 1;
            if (flag == 0)
                break;
        }
        while (1) {
            point next1 = now1, next2 = now2;
            next1.x = now1.x + 1, next2.x = now2.x + 1;
            if (next1.x >= 4 || next2.x >= 4 || red[next1.y][next1.x] == 1 || red[next2.y][next2.x] == 1)
                break;
            now1 = next1, now2 = next2;
        }
        red[now1.y][now1.x] = red[now2.y][now2.x] = 1;
    }
    check_red();
    int de = 1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;
    for (int tc = 0; tc < T; tc++) {
        point now;
        int type;
        cin >> type >> now.y >> now.x;


        map[now.y][now.x] = 1;
        if (type == 2)
            map[now.y][now.x + 1] = 1;
        else if (type == 3)
            map[now.y + 1][now.x] = 1;

        int de = 1;

        ye(now, type);
        re(now, type);


        map[now.y][now.x] = 0;
        if (type == 2)
            map[now.y][now.x + 1] = 0;
        else if (type == 3)
            map[now.y + 1][now.x] = 0;


    }
    int result2 = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (yel[i][j] == 1)
                result2++;
            if (red[i][j] == 1)
                result2++;
        }
    }

    cout << result << '\n' << result2;

    return 0;
}