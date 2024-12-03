// Q) Apply various 2d transformation in 2d object(using homogeneous coordinates)

#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

// Function to multiply a point matrix by a transformation matrix
void applyTransformation(float point[3], float transMatrix[3][3]) {
    float result[3] = {0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i] += transMatrix[i][j] * point[j];
        }
    }

    // Update the point with transformed coordinates
    point[0] = result[0];
    point[1] = result[1];
    point[2] = result[2];
}

// Function to draw a 2D object (triangle in this example)
void drawObject(float points[3][3], int color) {
    setcolor(color);
    line(points[0][0], points[0][1], points[1][0], points[1][1]);
    line(points[1][0], points[1][1], points[2][0], points[2][1]);
    line(points[2][0], points[2][1], points[0][0], points[0][1]);
}

int main() {
    // Initialize the graphics window
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Original triangle vertices in homogeneous coordinates
    float triangle[3][3] = {
        {100, 100, 1},  // Vertex A
        {200, 100, 1},  // Vertex B
        {150, 200, 1}   // Vertex C
    };

    // Draw the original object
    drawObject(triangle, WHITE);

    // Menu loop for user choice
    int choice;
    while (true) {
        cout << "\nChoose a transformation: \n";
        cout << "1. Translation\n";
        cout << "2. Scaling\n";
        cout << "3. Rotation\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // Translation
            float tx, ty;
            cout << "Enter translation values (tx, ty): ";
            cin >> tx >> ty;

            float translationMatrix[3][3] = {
                {1, 0, tx},
                {0, 1, ty},
                {0, 0, 1}
            };

            for (int i = 0; i < 3; i++) applyTransformation(triangle[i], translationMatrix);
            drawObject(triangle, GREEN);
        } 
        else if (choice == 2) {
            // Scaling
            float sx, sy;
            cout << "Enter scaling factors (sx, sy): ";
            cin >> sx >> sy;

            float scalingMatrix[3][3] = {
                {sx, 0, 0},
                {0, sy, 0},
                {0, 0, 1}
            };

            for (int i = 0; i < 3; i++) applyTransformation(triangle[i], scalingMatrix);
            drawObject(triangle, BLUE);
        } 
        else if (choice == 3) {
            // Rotation
            float angle;
            cout << "Enter rotation angle (in degrees): ";
            cin >> angle;

            float rad = angle * M_PI / 180;  // Convert degrees to radians
            float rotationMatrix[3][3] = {
                {cos(rad), -sin(rad), 0},
                {sin(rad), cos(rad), 0},
                {0, 0, 1}
            };

            for (int i = 0; i < 3; i++) applyTransformation(triangle[i], rotationMatrix);
            drawObject(triangle, RED);
        } 
        else if (choice == 4) {
            // Exit
            break;
        } 
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    // Close graphics window
    delay(5000);
    closegraph();

    return 0;
}
