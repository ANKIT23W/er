#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

struct Point3D {
    float x, y, z, w;
};

// Cube vertices
Point3D cube[8] = {
    {100, 100, 100, 1}, {200, 100, 100, 1}, {200, 200, 100, 1}, {100, 200, 100, 1},
    {100, 100, 200, 1}, {200, 100, 200, 1}, {200, 200, 200, 1}, {100, 200, 200, 1}
};

int edges[12][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6}, {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}
};

// Transformation functions
Point3D applyTransformation(Point3D point, float matrix[4][4]) {
    Point3D result;
    result.x = matrix[0][0] * point.x + matrix[0][1] * point.y + matrix[0][2] * point.z + matrix[0][3] * point.w;
    result.y = matrix[1][0] * point.x + matrix[1][1] * point.y + matrix[1][2] * point.z + matrix[1][3] * point.w;
    result.z = matrix[2][0] * point.x + matrix[2][1] * point.y + matrix[2][2] * point.z + matrix[2][3] * point.w;
    result.w = matrix[3][0] * point.x + matrix[3][1] * point.y + matrix[3][2] * point.z + matrix[3][3] * point.w;
    return result;
}

Point3D parallelProjection(Point3D point) {
    point.z = 0; 
    return point;
}

Point3D perspectiveProjection(Point3D point, float d) {
    Point3D result;
    if (point.z != 0) {
        result.x = point.x / (1 + point.z / d);
        result.y = point.y / (1 + point.z / d);
        result.z = 0;
    } else {
        result = point;
    }
    result.w = 1;
    return result;
}

void drawEdge(Point3D p1, Point3D p2) {
    line(p1.x, p1.y, p2.x, p2.y);
}

void render3DObject(Point3D cube[], float transformation[4][4], bool usePerspective, float d = 500) {
    Point3D transformedCube[8];
    for (int i = 0; i < 8; i++) {
        transformedCube[i] = applyTransformation(cube[i], transformation);
        transformedCube[i] = usePerspective ? perspectiveProjection(transformedCube[i], d) : parallelProjection(transformedCube[i]);
    }
    for (int i = 0; i < 12; i++) {
        drawEdge(transformedCube[edges[i][0]], transformedCube[edges[i][1]]);
    }
}

void translate(float tx, float ty, float tz, float matrix[4][4]) {
    matrix[0][3] += tx;
    matrix[1][3] += ty;
    matrix[2][3] += tz;
}

void rotateX(float angle, float matrix[4][4]) {
    float rad = angle * 3.14 / 180.0;
    float c = cos(rad), s = sin(rad);
    matrix[1][1] = c; matrix[1][2] = -s;
    matrix[2][1] = s; matrix[2][2] = c;
}

void rotateY(float angle, float matrix[4][4]) {
    float rad = angle * 3.14 / 180.0;
    float c = cos(rad), s = sin(rad);
    matrix[0][0] = c; matrix[0][2] = s;
    matrix[2][0] = -s; matrix[2][2] = c;
}

void rotateZ(float angle, float matrix[4][4]) {
    float rad = angle * 3.14 / 180.0;
    float c = cos(rad), s = sin(rad);
    matrix[0][0] = c; matrix[0][1] = -s;
    matrix[1][0] = s; matrix[1][1] = c;
}

void scale(float sx, float sy, float sz, float matrix[4][4]) {
    matrix[0][0] *= sx;
    matrix[1][1] *= sy;
    matrix[2][2] *= sz;
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    float transformationMatrix[4][4] = {
        {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}
    };

    int choice;
    bool usePerspective = false;

    do {
        cleardevice();
        cout << "\nMenu:\n";
        cout << "1. Translate\n2. Rotate X\n3. Rotate Y\n4. Rotate Z\n5. Scale\n";
        cout << "6. Toggle Projection (Parallel/Perspective)\n7. Exit\nChoose: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                float tx, ty, tz;
                cout << "Enter translation (tx, ty, tz): ";
                cin >> tx >> ty >> tz;
                translate(tx, ty, tz, transformationMatrix);
                break;
            }
            case 2: {
                float angle;
                cout << "Enter angle for X rotation: ";
                cin >> angle;
                rotateX(angle, transformationMatrix);
                break;
            }
            case 3: {
                float angle;
                cout << "Enter angle for Y rotation: ";
                cin >> angle;
                rotateY(angle, transformationMatrix);
                break;
            }
            case 4: {
                float angle;
                cout << "Enter angle for Z rotation: ";
                cin >> angle;
                rotateZ(angle, transformationMatrix);
                break;
            }
            case 5: {
                float sx, sy, sz;
                cout << "Enter scale factors (sx, sy, sz): ";
                cin >> sx >> sy >> sz;
                scale(sx, sy, sz, transformationMatrix);
                break;
            }
            case 6: {
                usePerspective = !usePerspective;
                cout << (usePerspective ? "Perspective Projection Enabled" : "Parallel Projection Enabled") << endl;
                break;
            }
            case 7:
                break;
            default:
                cout << "Invalid option!" << endl;
        }
        render3DObject(cube, transformationMatrix, usePerspective);
        delay(3000);
    } while (choice != 7);

    closegraph();
}
