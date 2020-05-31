#include<bangtal.h>

#include<stdio.h>
#include <stdlib.h>
#include <time.h>


SceneID bg;
ObjectID peice[50];
ObjectID start;
TimerID timerMixing;
const Second animationTime = 0.05f;

int x[17] = { 50, 450, 820, 70, 470, 840, 90, 490, 860, 110, 510, 880, 130, 530, 900 };
int y[17] = { 240, 240, 240, 320, 320, 320, 400, 400, 400, 470, 470, 470, 540, 540, 540 };
int from[100];
int to[100];
int i = 1;
int height = 1;
int p1 = 1, p2 = 1, p3 = 1, p4 = 1, p5 = 1;

void hanoi(int n, char a, char b, char c) {
    if (n == 1) {
        from[i] = a;
        to[i] = b;
        i++;
    }
    else {
        hanoi(n - 1, a, c, b);
        from[i] = a;
        to[i] = b;
        i++;
        hanoi(n - 1, c, b, a);
    }
}

void game_start() {
    bg = createScene("하노이의 탑", "배경.png");

    start = createObject("start.png");
    locateObject(start, bg, 590, 70);
    showObject(start);
    char image[100];
    for (int i = 5; i > 0; i--) {
        sprintf_s(image, "%d.png", i);
        peice[i] = createObject(image);
        locateObject(peice[i], bg, x[3 * (5 - i)], y[3 * (5 - i)]);
        showObject(peice[i]);
    }

}
void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
    if (object == start) {
        timerMixing = createTimer();
        setTimer(timerMixing, animationTime);
        startTimer(timerMixing);
        hideObject(start);
    }
}

void timerCallback(TimerID timer)
{
    if (peice[1] == from[i]) {
        if (peice[2] == to[i]) height++;
        if (peice[3] == to[i]) height++;
        if (peice[4] == to[i]) height++;
        if (peice[5] == to[i]) height++;
        locateObject(peice[1], bg, x[height], y[height]);
        peice[1] = to[i];
    }
    else if (peice[1] != from[i] && peice[2] == from[i]) {
        if (peice[3] == to[i]) height++;
        if (peice[4] == to[i]) height++;
        if (peice[5] == to[i]) height++;
        locateObject(peice[1], bg, x[height], y[height]);
        peice[2] = to[i];
    }
    else if (peice[1] != from[i] && peice[2] != from[i] && peice[3] == from[i]) {
        if (peice[4] == to[i]) height++;
        if (peice[5] == to[i]) height++;
        locateObject(peice[1], bg, x[height], y[height]);
        peice[3] = to[i];
    }
    else if (peice[1] != from[i] && peice[2] != from[i] && peice[3] != from[i] && peice[4] == from[i]) {
        if (peice[5] == to[i]) height++;
        locateObject(peice[1], bg, x[height], y[height]);
        peice[4] = to[i];
    }
    else if (peice[1] != from[i] && peice[2] != from[i] && peice[3] != from[i] && peice[4] != from[i] && peice[5] == from[i]) {
        locateObject(peice[1], bg, x[height], y[height]);
        peice[5] = to[i];
    }
    i++;
    setTimer(timerMixing, animationTime);
    startTimer(timerMixing);

}

int main() {
    setMouseCallback(mouseCallback);
    setTimerCallback(timerCallback);
    hanoi(5, 1, 3, 2);
    game_start();

    startGame(bg);
}