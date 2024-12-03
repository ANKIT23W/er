// Apply various 3d transformation in 3d object(and then apply parallel and perspective projection in it)

#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

// Homogeneous coordinates representation of a 3D point
struct Point3D {
    float x, y, z, w;
};

// Function to apply a transformation matrix to a 3D point
Point3D applyTransformation(Point3D point, float matrix[4][4]) {
    Point3D result;
    result.x = matrix[0][0] * point.x + matrix[0][1] * point.y + matrix[0][2] * point.z + matrix[0][3] * point.w;
    result.y = matrix[1][0] * point.x + matrix[1][1] * point.y + matrix[1][2] * point.z + matrix[1][3] * point.w;
    result.z = matrix[2][0] * point.x + matrix[2][1] * point.y + matrix[2][2] * point.z + matrix[2][3] * point.w;
    result.w = matrix[3][0] * point.x + matrix[3][1] * point.y + matrix[3][2] * point.z + matrix[3][3] * point.w;
    return result;
}

// Function to apply parallel projection
Point3D parallelProjection(Point3D point) {
    // For parallel projection, ignore the z-coordinate (set z = 0)
    point.z = 0;
    return point;
}

// Function to apply perspective projection
Point3D perspectiveProjection(Point3D point, float d) {
    Point3D result;
    if (point.z != 0) {  // Prevent division by zero
        result.x = point.x / (1 + point.z / d);
        result.y = point.y / (1 + point.z / d);
        result.z = 0; // Z-coordinate is projected to 2D
    } else {
        result = point; // If z == 0, no change
    }
    result.w = 1; // Set w to 1 for homogeneous coordinates
    return result;
}

// Function to draw edges between points
void drawEdge(Point3D p1, Point3D p2) {
    line(p1.x, p1.y, p2.x, p2.y);
}

// Function to apply transformations and render the object
void render3DObject(Point3D cube[], int edges[][2], int edgeCount, float transformation[4][4], bool usePerspective, float d = 500) {
    Point3D transformedCube[8];
    
    // Apply transformations
    for (int i = 0; i < 8; i++) {
        transformedCube[i] = applyTransformation(cube[i], transformation);
        if (usePerspective) {
            transformedCube[i] = perspectiveProjection(transformedCube[i], d);
        } else {
            transformedCube[i] = parallelProjection(transformedCube[i]);
        }
    }

    // Draw edges
    for (int i = 0; i < edgeCount; i++) {
        drawEdge(transformedCube[edges[i][0]], transformedCube[edges[i][1]]);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    // Define a cube with 8 points
    Point3D cube[8] = {
        {100, 100, 100, 1}, {200, 100, 100, 1}, {200, 200, 100, 1}, {100, 200, 100, 1}, // Front face
        {100, 100, 200, 1}, {200, 100, 200, 1}, {200, 200, 200, 1}, {100, 200, 200, 1}  // Back face
    };

    // Define edges of the cube
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Front face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Back face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
    };

    // Identity matrix (no transformation)
    float identity[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    // Rotation around Z-axis
    float angle = M_PI / 6; // 30 degrees
    float rotationZ[4][4] = {
        {cos(angle), -sin(angle), 0, 0},
        {sin(angle), cos(angle),  0, 0},
        {0,          0,           1, 0},
        {0,          0,           0, 1}
    };

    // Translation matrix
    float translation[4][4] = {
        {1, 0, 0, 50},
        {0, 1, 0, 50},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    // Scaling matrix
    float scaling[4][4] = {
        {1.5, 0,   0, 0},
        {0,   1.5, 0, 0},
        {0,   0,   1.5, 0},
        {0,   0,   0, 1}
    };

    // User choice for projection
    int projectionChoice;
    cout << "Choose the projection method:\n";
    cout << "1. Parallel Projection\n";
    cout << "2. Perspective Projection\n";
    cout << "Enter your choice (1/2): ";
    cin >> projectionChoice;

    bool usePerspective = (projectionChoice == 2);

    // Draw original cube with chosen projection
    cleardevice();
    setcolor(WHITE);
    render3DObject(cube, edges, 12, identity, usePerspective);
    outtextxy(10, 10, "Original Cube (Projection Choice)");
    getch();

    // Apply rotation with chosen projection
    cleardevice();
    render3DObject(cube, edges, 12, rotationZ, usePerspective);
    outtextxy(10, 10, "Rotated Cube (Projection Choice)");
    getch();

    // Apply scaling with chosen projection
    cleardevice();
    render3DObject(cube, edges, 12, scaling, usePerspective);
    outtextxy(10, 10, "Scaled Cube (Projection Choice)");
    getch();

    // Apply translation with chosen projection
    cleardevice();
    render3DObject(cube, edges, 12, translation, usePerspective);
    outtextxy(10, 10, "Translated Cube (Projection Choice)");
    getch();

    closegraph();
    return 0;
}
