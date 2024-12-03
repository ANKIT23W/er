#include <graphics.h>
#include <cmath>
#include <iostream>
using namespace std;

void drawHermiteCurve(int p1x, int p1y, int p2x, int p2y, int r1x, int r1y, int r2x, int r2y) {
    float t;
    for (t = 0; t <= 1; t += 0.001) {
        // Hermite basis functions
        float h1 = 2 * t * t * t - 3 * t * t + 1; 
        float h2 = -2 * t * t * t + 3 * t * t; 
        float h3 = t * t * t - 2 * t * t + t;  
        float h4 = t * t * t - t * t;  

        float x = h1 * p1x + h2 * p2x + h3 * r1x + h4 * r2x;
        float y = h1 * p1y + h2 * p2y + h3 * r1y + h4 * r2y;

        putpixel(round(x), round(y), GREEN);
    }
}

void drawBezierCurve(int p0x, int p0y, int p1x, int p1y, int p2x, int p2y, int p3x, int p3y) {
    float t;
    for (t = 0; t <= 1; t += 0.001) {
        // Bézier basis functions
        float b0 = pow(1 - t, 3);
        float b1 = 3 * t * pow(1 - t, 2);
        float b2 = 3 * t * t * (1 - t);
        float b3 = t * t * t;

        float x = b0 * p0x + b1 * p1x + b2 * p2x + b3 * p3x;
        float y = b0 * p0y + b1 * p1y + b2 * p2y + b3 * p3y;

        putpixel(round(x), round(y), RED);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    // Hermite Curve
    // int p1x = 100, p1y = 300;
    // int p2x = 400, p2y = 100;

    // int r1x = 400, r1y = 200;
    // int r2x = 200, r2y = 50;

    // setcolor(GREEN);
    // drawHermiteCurve(p1x, p1y, p2x, p2y, r1x, r1y, r2x, r2y);

    // setcolor(WHITE);
    // circle(p1x, p1y, 5);
    // circle(p2x, p2y, 5);

    // getch();

    // Bézier Curve
    int b0x = 100, b0y = 400;
    int b1x = 150, b1y = 200;
    int b2x = 350, b2y = 200;
    int b3x = 400, b3y = 400;

    setcolor(RED);
    drawBezierCurve(b0x, b0y, b1x, b1y, b2x, b2y, b3x, b3y);

    setcolor(WHITE);
    circle(b0x, b0y, 5);
    circle(b1x, b1y, 5);
    circle(b2x, b2y, 5);
    circle(b3x, b3y, 5);

    getch();
    closegraph();
    return 0;
}
