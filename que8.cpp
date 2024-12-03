//Hermite Curve

#include <graphics.h>
#include <cmath>
#include <iostream>

using namespace std;

// Function to calculate a Hermite curve
void drawHermiteCurve(int x0, int y0, int x1, int y1, int tx0, int ty0, int tx1, int ty1) {
    float t; // Parameter for the curve (0 to 1)
    float x, y;

    // Loop through the parameter t to calculate points
    for (t = 0.0; t <= 1.0; t += 0.001) {
        // Hermite basis functions
        float h1 = 2 * t * t * t - 3 * t * t + 1; // Basis for p0
        float h2 = -2 * t * t * t + 3 * t * t;    // Basis for p1
        float h3 = t * t * t - 2 * t * t + t;     // Basis for tangent at p0
        float h4 = t * t * t - t * t;             // Basis for tangent at p1

        // Calculate x and y using the Hermite equations
        x = h1 * x0 + h2 * x1 + h3 * tx0 + h4 * tx1;
        y = h1 * y0 + h2 * y1 + h3 * ty0 + h4 * ty1;

        // Plot the point
        putpixel((int)x, (int)y, WHITE);
    }
}

int main() {
    // Initialize graphics window
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    // Define points and tangents
    int x0 = 100, y0 = 300;  // Start point
    int x1 = 500, y1 = 300;  // End point
    int tx0 = 150, ty0 = -200; // Tangent at start
    int tx1 = 150, ty1 = 200;  // Tangent at end

    // Draw axes for reference
    line(0, 300, 640, 300); // Horizontal axis      drew line from (0,300) to (640,300) 
    line(320, 0, 320, 480); // Vertical axis

    // Draw the Hermite curve
    drawHermiteCurve(x0, y0, x1, y1, tx0, ty0, tx1, ty1);

    // Hold the graphics window
    getch();
    closegraph();
    return 0;
}


// My Notes:
// Width: 640 pixel 
// Height: 320 pixel 