#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES	1

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
    srand((unsigned int)time(NULL));
    timerMixing = createTimer();

}
void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
    if (object == start) {
        setTimer(timerMixing, animationTime);
        startTimer(timerMixing);
    }

}

void timerCallback(TimerID timer)
{
    
    setTimer(timerMixing, animationTime);
    startTimer(timerMixing);
}

int main() {
    setMouseCallback(mouseCallback);
    setTimerCallback(timerCallback);

    game_start();
        ;
    startGame(bg);
}