// Fill a polygon using scan line fill algorithm 

#include <graphics.h>
#include <iostream>
using namespace std;

// Function to draw the polygon
void drawPolygon(int poly[], int n) {
    for (int i = 0; i < n - 2; i += 2) {
        line(poly[i], poly[i + 1], poly[i + 2], poly[i + 3]); // Connect consecutive vertices
    }
    // Connect the last vertex to the first
    line(poly[n - 2], poly[n - 1], poly[0], poly[1]);
}

// Scan Line Fill Algorithm
void scanLineFill(int poly[], int n) {
    int yMin = poly[1], yMax = poly[1]; // Find minimum and maximum y-coordinates
    for (int i = 1; i < n; i += 2) {
        if (poly[i] < yMin) yMin = poly[i];
        if (poly[i] > yMax) yMax = poly[i];
    }

    // For each scan line (horizontal line)
    for (int y = yMin; y <= yMax; y++) {
        int intersections[10] = {0}; // Store x-intersections for edges
        int count = 0;

        for (int i = 0; i < n; i += 2) {
            int x1 = poly[i], y1 = poly[i + 1];
            int x2 = poly[(i + 2) % n], y2 = poly[(i + 3) % n];

            // Check if the edge crosses the scan line
            if (y1 != y2 && y >= min(y1, y2) && y <= max(y1, y2)) {
                // Find the intersection point using the line equation
                int xIntersect = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                intersections[count++] = xIntersect;
            }
        }

        // Sort intersections (simple bubble sort since max intersections is small)
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (intersections[j] > intersections[j + 1]) {
                    int temp = intersections[j];
                    intersections[j] = intersections[j + 1];
                    intersections[j + 1] = temp;
                }
            }
        }

        // Fill pixels between pairs of intersections
        for (int i = 0; i < count; i += 2) {
            line(intersections[i], y, intersections[i + 1], y);
        }
    }
}

int main() {
    // Initialize graphics mode
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    // Define polygon vertices
    int poly[] = {100, 100, 200, 50, 300, 100, 250, 200, 150, 200};
    int n = sizeof(poly) / sizeof(poly[0]);

    // Draw the polygon
    drawPolygon(poly, n);

    // Fill the polygon using the scan line fill algorithm
    scanLineFill(poly, n);

    // Pause to view the output
    getch();
    closegraph();
    return 0;
}
