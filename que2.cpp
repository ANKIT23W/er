// Mid point circle drawing algorithm -> Pending
#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

// Function to print coordinates
void printCoord(int x, int y) {
    cout << "(" << x << "," << y << ") ";
}

// Recursive function for the midpoint circle algorithm
void MidpntAlgo(int xk, int yk, int P, int xShift, int yShift, int scale) {
    if (xk > yk) return;

    // Print and draw the current points
    printCoord(xk, yk);
    putpixel(xk * scale + xShift, yk * scale + yShift, WHITE); // First octant
    putpixel(yk * scale + xShift, xk * scale + yShift, WHITE); // Second octant
    putpixel(xk * scale + xShift, -yk * scale + yShift, WHITE); // Third octant
    putpixel(yk * scale + xShift, -xk * scale + yShift, WHITE); // Fourth octant
    putpixel(-xk * scale + xShift, -yk * scale + yShift, WHITE); // Fifth octant
    putpixel(-yk * scale + xShift, -xk * scale + yShift, WHITE); // Sixth octant
    putpixel(-xk * scale + xShift, yk * scale + yShift, WHITE); // Seventh octant
    putpixel(-yk * scale + xShift, xk * scale + yShift, WHITE); // Eighth octant

    // Update the decision parameter and the next points
    if (P < 0) {
        P += 2 * xk + 3;
        MidpntAlgo(xk + 1, yk, P, xShift, yShift, scale);
    } else {
        P += 2 * xk - 2 * yk + 5;
        MidpntAlgo(xk + 1, yk - 1, P, xShift, yShift, scale);
    }
}

int main() {
    int r;
    cout << "Enter radius of the circle: ";
    cin >> r;

    // Center shift and scale factors
    int xShift = 960, yShift = 540, scale = 1;

    // Graphics initialization
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenWidth, screenHeight, "Midpoint Circle Algorithm");

    // Initial points and decision parameter
    int x = 0, y = r;
    int P = 1 - r;

    cout << "Points of the first octant of the circle: ";
    printCoord(x, y);
    putpixel(x * scale + xShift, y * scale + yShift, WHITE);
    MidpntAlgo(x, y, P, xShift, yShift, scale);

    getch(); // Wait for a key press
    closegraph(); // Close graphics window

    return 0;
}
