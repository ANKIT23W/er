#include <graphics.h>
#include <iostream>
using namespace std;

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

int main() {
    // Initialize the graphics drivers
    int gm, gd = DETECT;
    int x1 = 100, x2 = 100, x3 = 200, y1 = 100;
    int y2 = 200, y3 = 100;

    // Initialize graphics mode
    initgraph(&gd, &gm, (char*)"");

    cleardevice();

    // Draw the graph (X and Y axes)
    line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy()); // Y-axis
    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2); // X-axis

    // Object initially in the 2nd quadrant
    cout << "Before Reflection Object in 2nd Quadrant" << endl;

    // Set the color for the original object (white)
    setcolor(14);
    drawTriangle(x1, y1, x2, y2, x3, y3);

    int choice;
    while (true) {
        // Display menu for the user to select reflection type
        cout << "\nSelect the axis for reflection:\n";
        cout << "1. Reflect along X-axis\n";
        cout << "2. Reflect along Y-axis\n";
        cout << "3. Reflect along Origin\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear the screen for each new drawing
        cleardevice();
        
        // Draw the axes again
        line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy()); // Y-axis
        line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2); // X-axis

        // Draw the original object
        setcolor(14);
        drawTriangle(x1, y1, x2, y2, x3, y3);

        switch (choice) {
            case 1:
                // Reflection along X-axis
                setcolor(4); // Red color for reflection
                drawTriangle(x1, getmaxy() - y1, x2, getmaxy() - y2, x3, getmaxy() - y3);
                cout << "\nReflected along the X-axis\n";
                break;

            case 2:
                // Reflection along Y-axis
                setcolor(3); // Green color for reflection
                drawTriangle(getmaxx() - x1, y1, getmaxx() - x2, y2, getmaxx() - x3, y3);
                cout << "\nReflected along the Y-axis\n";
                break;

            case 3:
                // Reflection along Origin
                setcolor(2); // Blue color for reflection
                drawTriangle(getmaxx() - x1, getmaxy() - y1, getmaxx() - x2, getmaxy() - y2, getmaxx() - x3, getmaxy() - y3);
                cout << "\nReflected along the Origin\n";
                break;

            case 4:
                // Exit the program
                cout << "\nExiting...\n";
                closegraph();
                return 0;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

        // Wait for the user to press a key before showing the next reflection
        getch();
    }

    return 0;
}
