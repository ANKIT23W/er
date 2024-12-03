#include <graphics.h>
#include <iostream>
using namespace std;

// Function to apply the shear transformation matrix
void applyShearTransformation(float square[4][3], float shearMatrix[3][3]) {
    float result[4][3] = {0};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = square[i][0] * shearMatrix[0][j] +
                           square[i][1] * shearMatrix[1][j] +
                           square[i][2] * shearMatrix[2][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        square[i][0] = result[i][0];
        square[i][1] = result[i][1];
        square[i][2] = result[i][2];
    }
}

// Function to draw a square based on points
void drawSquare(float square[4][3], int color) {
    setcolor(color);
    for (int i = 0; i < 4; i++) {
        line(square[i][0], square[i][1], square[(i + 1) % 4][0], square[(i + 1) % 4][1]);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Initial square points (homogeneous coordinates)
    float square[4][3] = {
        {100, 100, 1},  // Top-left
        {200, 100, 1},  // Top-right
        {200, 200, 1},  // Bottom-right
        {100, 200, 1}   // Bottom-left
    };

    // Draw the original square
    drawSquare(square, WHITE);

    // Ask the user for shear factors
    float shx = 0, shy = 0;
    int shearChoice;
    cout << "Choose the shearing axis:\n";
    cout << "1. X-axis\n";
    cout << "2. Y-axis\n";
    cout << "Enter your choice: ";
    cin >> shearChoice;

    if (shearChoice == 1) {
        cout << "Enter shear factor along X-axis: ";
        cin >> shx;
    } else if (shearChoice == 2) {
        cout << "Enter shear factor along Y-axis: ";
        cin >> shy;
    } else {
        cout << "Invalid choice.\n";
        closegraph();
        return 0;
    }

    // Shear matrix based on user input
    float shearMatrix[3][3] = {
        {1, shx, 0},
        {shy, 1, 0},
        {0, 0, 1}
    };

    // Apply shear transformation and draw sheared square
    applyShearTransformation(square, shearMatrix);
    drawSquare(square, YELLOW);

    // Hold screen and wait for user input to exit
    cout << "\nPress any key to exit the graphics window...";
    getch();
    closegraph();

    return 0;
}
