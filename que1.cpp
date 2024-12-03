// Bresenhem line drawing algorithm -> Done

#include <graphics.h>
#include <conio.h>
#include <iostream>
using namespace std;
void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        putpixel(x1, y1, WHITE);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    
    int x1 = 100, y1 = 100, x2 = 200, y2 = 200;
    bresenhamLine(x1, y1, x2, y2);
    getch();
    closegraph();
    return 0;
}