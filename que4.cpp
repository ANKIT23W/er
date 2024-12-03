// Polygon clipping algorithm -> Pending


#include <graphics.h>
#include <iostream>

using namespace std;

const int MAX_POINTS = 100;  // Maximum number of points in the polygon

struct Point {
    int x, y;
};

// Function to check if a point is inside the clipping window
bool inside(Point p, Point clipMin, Point clipMax) {
    return (p.x >= clipMin.x && p.x <= clipMax.x && p.y >= clipMin.y && p.y <= clipMax.y);
}

// Function to find the intersection point of two lines
Point computeIntersection(Point p1, Point p2, Point p3, Point p4) {
    Point intersection;
    float denom = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
    if (denom == 0) return {0, 0}; // Avoid division by zero (lines are parallel or collinear)
    intersection.x = (int)((((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x)) - 
                            ((p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x))) / denom);
    intersection.y = (int)((((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y)) - 
                            ((p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x))) / denom);
    return intersection;
}

// Sutherland-Hodgman algorithm for polygon clipping
int sutherlandHodgmanClip(Point* subjectPolygon, int subjectCount, 
                          Point* clipPolygon, int clipCount, 
                          Point* outputPolygon) {
    int outputCount = subjectCount;  // Start with subject polygon
    for (int i = 0; i < clipCount; i++) {
        Point clip1 = clipPolygon[i];
        Point clip2 = clipPolygon[(i + 1) % clipCount];

        Point inputPolygon[MAX_POINTS];
        for (int j = 0; j < outputCount; j++) {
            inputPolygon[j] = outputPolygon[j];
        }

        int inputCount = outputCount;
        outputCount = 0;

        for (int j = 0; j < inputCount; j++) {
            Point p1 = inputPolygon[j];
            Point p2 = inputPolygon[(j + 1) % inputCount];

            if (inside(p2, clip1, clip2)) {
                if (!inside(p1, clip1, clip2)) {
                    outputPolygon[outputCount++] = computeIntersection(p1, p2, clip1, clip2);
                }
                outputPolygon[outputCount++] = p2;
            } else if (inside(p1, clip1, clip2)) {
                outputPolygon[outputCount++] = computeIntersection(p1, p2, clip1, clip2);
            }
        }
    }
    return outputCount;
}

void drawPolygon(Point* polygon, int pointCount, int color) {
    setcolor(color);
    for (int i = 0; i < pointCount; i++) {
        line(polygon[i].x, polygon[i].y, polygon[(i + 1) % pointCount].x, polygon[(i + 1) % pointCount].y);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Define subject polygon points (Pentagon)
    Point subjectPolygon[MAX_POINTS] = {
        {50, 150}, {200, 50}, {300, 150}, {250, 250}, {100, 250}
    };
    int subjectCount = 5; // Number of points in the subject polygon

    // Define clipping polygon points (Rectangle)
    Point clipPolygon[MAX_POINTS] = {
        {100, 100}, {300, 100}, {300, 300}, {100, 300}
    };
    int clipCount = 4; // Number of points in the clip polygon

    // Draw subject polygon (Pentagon)
    drawPolygon(subjectPolygon, subjectCount, WHITE);

    // Draw clipping polygon (Rectangle)
    drawPolygon(clipPolygon, clipCount, YELLOW);

    Point outputPolygon[MAX_POINTS]; // Array to store the clipped polygon
    for (int i = 0; i < subjectCount; i++) outputPolygon[i] = subjectPolygon[i];

    // Clip the polygon using Sutherland-Hodgman algorithm
    int outputCount = sutherlandHodgmanClip(subjectPolygon, subjectCount, clipPolygon, clipCount, outputPolygon);

    // Draw the clipped polygon
    drawPolygon(outputPolygon, outputCount, GREEN);

    getch();
    closegraph();
    return 0;
}

